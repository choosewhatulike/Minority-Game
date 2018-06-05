#include "History.h"
#include <QtGlobal>
/**
 * History implementation
 */

void History::addRecord(const Record &r)
{
    m_records.append(r);
}

Record History::getRecord(int idx) const
{
    return m_records.value(idx);
}

int History::size() const
{
    return m_records.size();
}


