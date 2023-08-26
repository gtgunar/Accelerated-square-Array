#ifndef COMPAREE_H
#define COMPAREE_H
#include <vector>
#include <list>
#include <chrono>

using namespace std;
template <typename T>
class compareeInterFace
{
private:
    // content;
public:
    virtual void addAt(int index, T content) = 0;
    virtual void removeAt(int index) = 0;
    virtual void setAt(int index, T content) = 0;
    virtual T getAt(int index) const = 0;
    compareeInterFace() {}
    ~compareeInterFace() {}
};
template <typename T>
class tombC : public compareeInterFace<T>
{
    vector<T> tartalom;

public:
    void addAt(int index, T content) { tartalom.insert(tartalom.begin() + index, content); }
    void removeAt(int index) { tartalom.erase(tartalom.begin() + index); }
    void setAt(int index, T content) { tartalom[index] = content; }
    T getAt(int index) const { return tartalom[index]; }
    tombC() {}
};
template <typename T>
class listC : public compareeInterFace<T>
{
    list<T> tartalom;

public:
    void addAt(int index, T content)
    {
        auto target = tartalom.begin();
        for (int i = 0; i < index; i++)
            target++;
        tartalom.insert(target, content);
    }
    void removeAt(int index)
    {
        auto target = tartalom.begin();
        for (int i = 0; i < index; i++)
            target++;
        tartalom.erase(target);
    }
    void setAt(int index, T content)
    {
        auto target = tartalom.begin();
        for (int i = 0; i < index; i++)
            target++;
        *target = content;
    }
    T getAt(int index) const
    {
        auto target = tartalom.begin();
        for (int i = 0; i < index; i++)
            target++;
        return *target;
    }
    listC() {}
};
#endif