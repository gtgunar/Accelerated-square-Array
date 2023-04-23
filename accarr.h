//Márton Attila, 2023
#ifndef ACCARR_H
#define ACCARR_H

#include<iostream>
#include<vector>
#include<cmath>
#include<deque>
#include"SQ.h"
#include"accarr_innerData.h"
using namespace std;
using namespace StationaryQueue;

template<typename T>//depth=2
class accarr
    {
    public:
    accarr():metaData(0)
        {
        content.push_back(new SQ<T>());
        content.push_back(new SQ<T>());
        }
    int getPop()const{return metaData.getPop();}

    T& refAt(int index)const
        {
        auto pos=metaData.getRelPos(index);
        return content[pos.first]->access(pos.second);
        }

    void insert(int index,const T& value)
        { 
        auto to=metaData.getRelPos(index);
        content[to.first]->addTo(to.second,value);   
        balanceShift(to.first , metaData.getHotPlace().first);
        }

    void erase(int index)
        {
        auto to=metaData.getRelPos(index);
        content[to.first]->deleteFrom(to.second);   
        balanceShift(metaData.getColdPlace().first , to.first);
        }

    T& operator[](int index)
        {return refAt(index);}

    void setAt(int index, const T& value)const
        {refAt(index)=value;}

    T getAt(int index)const
        {return refAt(index);}

    
    ~accarr(){for(auto i: content)delete i;}
    //private:
    accarr_innerData metaData;
    deque<SQ<T>*> content;
    void balanceShift(int from,int to)/////////////////////////////////////////////
        {
        if(from<to)
            {
            T temp=content[from]->pop_back();
            for(int i=from+1;i<to;i++)
                {temp=content[i]->placing(temp);}
            content[to]->push_front(temp);
            }
        else if(from>to)
            {
            T temp=content[from]->pop_front();
            for(int i=from-1;i>to;i--)
                {temp=content[i]->revplace(temp);}
            content[to]->push_back(temp);
            }
        //else means there is no job to be done as the disturbance
        //happened where it should be concentrated to anyway
        }
    

    };


#endif