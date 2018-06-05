#ifndef _AGENT_H
#define _AGENT_H

#include "Memory.h"
#include "History.h"

class Agent {
public: 
    Agent(int initCapital, int len, int numofStategy, int _threshold);

    bool isAuto;
    int capital;

    Memory mem;
    History hist;
    Record curState;

    int threshold;

    //outcome should be g(t)
    void receiveReward(int outcome);
    int decide();

};

#endif //_AGENT_H
