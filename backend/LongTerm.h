#ifndef _LONGTERM_H
#define _LONGTERM_H

#include <QVector>
#include <random>
#include <utility>

class LongTerm {
public: 
    QVector<QVector<bool>> choices;
    QVector<int> score;
    
    LongTerm(int size, int len);

    /**
     * get each actions and their scores
     */
    QVector<std::pair<int, int>> getAction(int idx);
    
    /**
     * use current win/lose to update
     */
    void updateScore(bool outcome, int row);

private:
    static std::default_random_engine engine;
    static std::uniform_int_distribution<int> g;
};

#endif //_LONGTERM_H
