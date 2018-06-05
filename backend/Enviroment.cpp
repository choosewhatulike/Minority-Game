#include "enviroment.h"
#include <QEventLoop>
#include <algorithm>

Enviroment::Enviroment(QObject *parent) :QObject(parent)
{
    m_agents.reserve(12345);
}

void Enviroment::init(int num)
{
    if(num % 2 == 0) {
        emit initFinished(false);
        return;
    }

    m_agentNum = num;
    m_iteration = 0;
    m_timestamp = 0;

    if(!m_agents.empty()) {
        for(Agent *ap : m_agents) {
            delete ap;
        }
    }
    m_agents.clear();
    m_pastDecisions.clear();
    m_agents.resize(m_agentNum);
    Agent *p;
    for(int i=0; i < m_agentNum; ++i){
        p = new Agent(m_initCapital, m_memLen, m_numStrategy, m_threshold);
        m_agents[i] = p;
    }
    m_decisions = QVector<bool>(m_agentNum);
    m_pastDecisions.reserve(1000);

    emit initFinished(true);
}

void Enviroment::step()
{
//    qDebug("curThread = %d\n", QThread::currentThread());
//    if(iteration % 99 == 0) qDebug("cur iteration = %d\n",iteration);
    Q_ASSERT(m_agentNum == m_agents.size());
    Q_ASSERT(m_agentNum == m_decisions.size());
    decisonTime();
    countTime();
    rewardTime();
    ++m_iteration;
    emit stepFinished();
}

void Enviroment::manDecided(const std::map<Agent*, int>& manAg)
{
    Q_ASSERT(manAg.size() == m_manAgents.size());

    for(const auto& ap : manAg){
        if(ap.second == 0) {
            ap.first->decide();
        }
        else{
            ap.first->curState.action = (ap.second > 0) ? 1:0;
            ap.first->curState.actionNo = MAN_ACTOIN_NO;
        }
    }

    emit manDecideFinished();
}

void Enviroment::decisonTime()
{
    //emit some signals for waiting man act as agents
    //wait until man made done
    if(!m_manAgents.empty()) {
        QEventLoop loop;
        connect(this, SIGNAL(manDecideFinished()), &loop, SLOT(quit()));
        emit needmanDecide();
        loop.exec();
    }

    int i = 0;
    for (Agent *ap : m_agents) {
        if(ap->isAuto) ap->decide();
        m_decisions[i++] = ap->curState.action;
    }
    Q_ASSERT(i == m_agentNum);

    ++m_timestamp;
}

void Enviroment::countTime()
{
    int bar = std::count(m_decisions.begin(), m_decisions.end(), true);
    int home = m_agentNum - bar;
    m_pastDecisions.push_back(bar - home);
    ++m_timestamp;
}

void Enviroment::rewardTime()
{
    int outcome = m_pastDecisions.back();
    for(Agent* ap : m_agents) {
        ap->receiveReward(outcome);
    }
    ++m_timestamp;
}

bool Enviroment::switchControl(Agent *ap, bool manControl)
{
    if(ap == NULL) return false;
    if(manControl != ap->isAuto) {
        return true;
    }
    else if (manControl){
        m_manAgents.append(ap);
        ap->isAuto = false;
    }
    else {
        int c = m_manAgents.removeAll(ap);
        Q_ASSERT(c == 1);
        ap->isAuto = true;
    }

    return true;
}


EnvControl::EnvControl() {
    m_env = new Enviroment();
    m_env->moveToThread(this);
    connect(m_env, SIGNAL(stepFinished()), this, SIGNAL(steped()));
    connect(m_env, SIGNAL(initFinished(bool)), this, SIGNAL(inited(bool)));
    start();
}

EnvControl::~EnvControl()
{
    if(runningLoop()) stopLoop();
    quit();
    wait();
    delete m_env;
}

int EnvControl::interval() const
{
    return m_interval;
}

void EnvControl::setInterval(int value)
{
    Q_ASSERT(value >= 0);
    m_interval = value;
}

void EnvControl::init(int agentNum)
{
    if(runningLoop()) stopLoop();
    m_env->m_agentNum = agentNum;
    bool res;
    QMetaObject::invokeMethod(m_env, "init", Q_ARG(int, agentNum));
}

void EnvControl::step()
{
    if(runningLoop()) stopLoop();
    QMetaObject::invokeMethod(m_env, "step", Qt::QueuedConnection);
}

void EnvControl::startLoop()
{
    if(runningLoop()) return;
    m_stopFlag = false;
    connect(this, SIGNAL(steped()), this, SLOT(stepLoop()));
    QMetaObject::invokeMethod(m_env, "step", Qt::QueuedConnection);
    emit loopStarted();
}

void EnvControl::switchControl(Agent *ap, bool manControl)
{
    bool res = m_env->switchControl(ap, manControl);
    emit switchedControl(ap, res);
}

void EnvControl::stopLoop()
{
    if(!runningLoop()) return;
    m_stopFlag = true;
    disconnect(this, SIGNAL(steped()), this, SLOT(stepLoop()));
    emit loopStopped();
}

bool EnvControl::runningLoop() const
{
    return !m_stopFlag;
}

Enviroment *EnvControl::getEnv() const
{
    return m_env;
}

QVector<Agent *> EnvControl::getAgents() const
{
    return m_env->m_agents;
}

void EnvControl::stepLoop()
{
    if(m_interval > 0) QThread::msleep(m_interval);
    QMetaObject::invokeMethod(m_env, "step", Qt::QueuedConnection);
}
