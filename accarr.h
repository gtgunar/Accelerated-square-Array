//Márton Attila, 2023
#ifndef ACCARR_H
#define ACCARR_H

#include<iostream>
#include<vector>
#include<cmath>
#include<deque>
#include"SQ.h"
#include"accarr_innerData.h"

using  std::vector;
using  std::cout;
using  std::endl;
using  std::deque;
using  namespace std::chrono;

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
        cout<<"refat started"<<endl;
        auto pos=metaData.getRelPos(index);
        cout<<"index: "<<index<<" Hely: "<<pos.first<<", "<<pos.second<<endl;
        content[pos.first]->log();
        return content[pos.first]->access(pos.second);
        }

    void insert(int index,const T& value)
        {
        auto to=metaData.getRelPos(index);   
        //cout<<"insert0"<<endl;
        cout<<endl<<to.first<<endl;
        content[to.first]->addTo(to.second,value); 
        cout<<"insert1"<<endl;
        balanceShift(to.first , metaData.getHotPlace().first);
        auto todo=metaData.incPop();
        if (todo)
            content.push_back(new SQ<T>());
        cout<<"insert done"<<endl;
        metaData.logMe();
        }

    void erase(int index)
        {
        if(content.size()==0){cout<<"DEL FROM EMPTY"<<endl;}
        cout<<"\terase 0"<<endl;
        auto to=metaData.getRelPos(index);cout<<"\terase 1"<<endl;
        content[to.first]->deleteFrom(to.second);   cout<<"\terase 2"<<endl;
        balanceShift(metaData.getColdPlace().first , to.first);cout<<"erase 3"<<endl;
        auto todo=metaData.decPop();cout<<"erase 4"<<endl;
        if (todo&&(content.size())>1)
            content.pop_back();
        metaData.logMe();
        cout<<"ERASEDONE---------------------------------"<<endl;
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
        cout<<"from&to:"<<from<<", "<<to<<endl;
        cout<<"--1"<<endl;
        if(from<to)
            {cout<<"--2"<<endl;
            T temp=content[from]->pop_back();
            cout<<"--3"<<endl;
            for(int i=from+1;i<to;i++)
                {temp=content[i]->placing(temp);}
                cout<<"--4"<<endl;
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