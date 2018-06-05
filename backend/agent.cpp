#include "Agent.h"

#include <QtGlobal>
#include <algorithm>
/**
 * Agent implementation
 */
Agent::Agent(int initCapital, int len, int numofStategy, int _threshold):
    isAuto(true),
    capital(initCapital),
    mem(len, numofStategy),
    threshold(_threshold)
{

}

void Agent::receiveReward(int outcome) {
    Q_ASSERT(curState.action != NOT_EXISTS);
    Q_ASSERT(curState.actionNo != NOT_EXISTS);
    int delta = outcome * ((curState.action > 0)? 1:-1);
    mem.update(delta > 0);
    capital += delta;
    curState.capital = capital;
    hist.addRecord(curState);
}

int Agent::decide()
{
    int idx = hist.size() - 1;
    int lastChoice = hist.getRecord(idx).actionNo;
    int curChoice = NOT_EXISTS;
    int maxscore = (lastChoice == NOT_EXISTS )? NOT_EXISTS : mem.score[lastChoice];

    auto max_it = std::max_element(mem.score.begin(), mem.score.end());

    if(maxscore == NOT_EXISTS || *max_it - maxscore > threshold) {
        curChoice = max_it - mem.score.begin();
    }
    else {
        curChoice = lastChoice;
    }

    curState.action = (mem.choices[curChoice][mem.shortmem]) ? 1 : 0;
    curState.actionNo = curChoice;
    return curState.action;
}
