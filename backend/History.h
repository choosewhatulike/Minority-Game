#ifndef _HISTORY_H
#define _HISTORY_H

#include <QVector>

#define MAN_ACTOIN_NO -2
#define NOT_EXISTS -1

class Record {
public:
    int capital = NOT_EXISTS;
    int8_t action = NOT_EXISTS;
    int actionNo = NOT_EXISTS;
};

class History {
public: 
    QVector<Record> m_records;

    void addRecord(const Record& r);
    Record getRecord(int idx) const;
    int size() const;
};

#endif //_HISTORY_H
