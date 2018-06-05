#include "LongTerm.h"
#include <stdlib.h>
#include <time.h>

/**
 * LongTerm implementation
 */

std::default_random_engine LongTerm::engine;
std::uniform_int_distribution<int> LongTerm::g(0,1);

LongTerm::LongTerm(int size, int len):
    score(size, 0),
    choices(size, QVector<bool>(len))
{
    for(int i=0; i<size;++i){
        for(int j=0;j<len;++j){
            choices[i][j] = g(engine);
        }
    }
}

/**
 * get each actions and their scores
 */
QVector<std::pair<int, int> > LongTerm::getAction(int idx) {
    QVector<std::pair<int,int>> ans(choices.size());
    for(int i=0; i < choices.size();++i){
        ans[i] = {choices[i][idx], score[i]};
    }
    return ans;
}

/**
 * use current win/lose to update
 */
void LongTerm::updateScore(bool outcome, int row) {
    for(int i=0; i < choices.size(); ++i) {
        if(choices.at(i).at(row) == outcome) {
            score[i] += 1;
        }
    }
}
