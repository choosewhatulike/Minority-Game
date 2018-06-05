#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include <QObject>
#include <vector>
#include <unordered_set>
#include <map>
#include "agent.h"
#include <QThread>
#include <QTimer>
#include <QLineSeries>

using namespace QtCharts;

class Enviroment : public QObject
{
    Q_OBJECT
public:
    explicit Enviroment(QObject *parent = nullptr);

    int m_iteration = 0;
    int m_timestamp = 0;
    int m_agentNum = 0;

    int m_initCapital = 100;
    int m_memLen = 3;
    int m_numStrategy = 5;
    int m_threshold = 3;

    QVector<Agent*> m_agents;
    QList<Agent*> m_manAgents;
    QVector<bool> m_decisions;
    QVector<int> m_pastDecisions;

    void decisonTime();
    void countTime();
    void rewardTime();

signals:
    void needmanDecide();
    void manDecideFinished();
    void stepFinished();
    void initFinished(bool);

public slots:
    void init(int num);
    void manDecided(const std::map<Agent*, int>& manAg);
    bool switchControl(Agent *ap, bool manControl);
    void step();
//    void undo();
};

class EnvControl : public QThread
{
    Q_OBJECT

    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)
    Q_PROPERTY(bool isRunning READ runningLoop)
//    Q_PROPERTY(QList<Agent*> agents READ getAgents)

public:
    EnvControl();
    virtual ~EnvControl();

    int m_interval = 0;

    Enviroment *m_env;

public:
    int interval() const;
    void setInterval(int value);
    bool runningLoop() const;
    Enviroment *getEnv() const;
    QVector<Agent *> getAgents() const;
    Q_INVOKABLE void init(int agentNum);
    Q_INVOKABLE void step();
    Q_INVOKABLE void startLoop();
    Q_INVOKABLE void switchControl(Agent *ap, bool manControl);
    Q_INVOKABLE void stopLoop();



private:
    bool m_stopFlag = true;

signals:
    void inited(bool result);
    void steped();
    void intervalChanged();
    void loopStarted();
    void loopStopped();
    void switchedControl(Agent *ap, bool result);

private slots:
    void stepLoop();
};

#endif // ENVIROMENT_H
