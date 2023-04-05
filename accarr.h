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
    accarr_innerData metaData;
    public://TODO delete debug-public
    deque<SQ<T>*> content;

    

    void balanceShift(int newat,bool reverse=false)/////////////////////////////////////////////
        {}//hotplace could be calced
    
    public:
    accarr();
    int getPop()const{return metaData.getPop();}
    T& refAt(int index)const;

    void insert(int index,const T& value);
    void erase(int index);

    T& operator[](int index);
    void setAt(int index, const T& value)const;
    T getAt(int index)const;
    
    ~accarr();
    };


#endif