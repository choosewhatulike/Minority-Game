#include "Memory.h"

/**
 * Memory implementation
 * 
 * store the short term and long term memory
 */
Memory::Memory(int len, int numofStrategy):
    length(len),
    mask((1 << len) - 1),
    numStrategy(numofStrategy),
    LongTerm(numofStrategy, 1 << len)
{

}


/**
 * update short term by current state
 */

void Memory::updateShort(bool outcome) {
    shortmem = (shortmem << 1) + (outcome ? 1 : 0);
    shortmem = shortmem  & mask;
}

void Memory::update(bool outcome)
{
    int row = shortmem;
    updateScore(outcome, row);
    updateShort(outcome);
}
