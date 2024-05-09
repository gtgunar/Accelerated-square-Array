// Márton Attila, 2023
#ifndef ACCARR_H
#define ACCARR_H
#include "accarr_innerData.h"
#include "SQ.h"

template <typename T> // depth=2
class accarr
{
private:
    accarr_innerData metaData;
    deque<SQ<T> *> *content;
    void balanceShift(int from, int to)
    {

        if (from < to)
        {
            T temp = ((*content)[from])->pop_back();
            for (int i = from + 1; i < to; i++)
            {
                temp = ((*content)[i])->revplace(temp);
            }
            ((*content)[to])->push_front(temp);
        }
        else if (from > to)
        {
            T temp = ((*content)[from])->pop_front();
            for (int i = from - 1; i > to; i--)
            {
                temp = ((*content)[i])->placing(temp);
            }
            ((*content)[to])->push_back(temp);
        }
    }
    

public:
    accarr() 
    {
        content = new deque<SQ<T> *>();
        content->push_back(new SQ<T>());
        content->push_back(new SQ<T>());
    }
    int getPop() const { return metaData.getPop(); }

    T &refAt(int index) const
    {
        auto pos = metaData.getRelPos(index);
        return ((*content)[pos.upper])->access(pos.lower);
    }

    void insert(int index, const T &value)
    {
        auto to = metaData.getRelPos(index);
        ((*content)[to.upper])->addTo(to.lower, value);

        balanceShift(to.upper, metaData.getHotPlace().upper);

        auto todo = metaData.incPop();
        if (todo)
            content->push_back(new SQ<T>());
    }

    void erase(int index)
    {
        auto to = metaData.getRelPos(index);
        ((*content)[to.upper])->deleteFrom(to.lower);
        balanceShift(metaData.getColdPlace().upper, to.upper);
        auto todo = metaData.decPop();
        if (todo && (content->size()) > 2)
            content->pop_back();
    }

    T &operator[](int index)
    {
        return refAt(index);
    }
    T &operator[](int index) const
    {
        return refAt(index);
    }
    void setAt(int index, const T &value) const
    {
        refAt(index) = value;
    }

    T getAt(int index) const
    {
        return refAt(index);
    }

    ~accarr()
    {
        for (auto i : *content)
            delete i;
        delete content;
    }
};

#endif