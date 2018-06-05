#ifndef _MEMORY_H
#define _MEMORY_H

#include "LongTerm.h"

class Memory: public LongTerm {
public: 
    Memory(int len, int numofStrategy);

    const int length;
    const int mask;
    const int numStrategy;

    int shortmem = 0;

    void updateShort(bool outcome);
    void update(bool outcome);
};

#endif //_MEMORY_H
