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
using namespace std;/////////////////////////
using namespace StationaryQueue;
using  std::begin;
using  std::end;
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
        //content.push_back(new SQ<T>());
        auto to=metaData.getRelPos(index);   ////////////////////////////////////////////////////////////////////////////////////////
     //   cout<<"insertion to: "<<to.first<<", "<<to.second<<endl;
     //   cout<<"hotplace to: "<<metaData.getHotPlace().first<<", "<<metaData.getHotPlace().second<<endl;
        content[to.first]->addTo(to.second,value); 

        balanceShift(to.first , metaData.getHotPlace().first);
        auto todo=metaData.incPop();
        if (todo)
            content.push_back(new SQ<T>());
        }

    void erase(int index)
        {
        auto to=metaData.getRelPos(index);//cout<<"\terase 1"<<endl;
        content[to.first]->deleteFrom(to.second); //  cout<<"\terase 2"<<endl;
        balanceShift(metaData.getColdPlace().first , to.first);//cout<<"erase 3"<<endl;
        auto todo=metaData.decPop();//cout<<"erase 4"<<endl;
        if (todo&&(content.size())>2)////////////////////////////////////////////////////////////////////////////////////////
            content.pop_back();
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
      //  cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx"<<endl;
     //   logRaw();cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx"<<endl;
        if(from<to)
            {
            T temp=content[from]->pop_back();           
            for(int i=from+1;i<to;i++)
                {temp=content[i]->revplace(temp);}//revplace
            content[to]->push_front(temp);
            }
        else if(from>to)
            {
            T temp=content[from]->pop_front();
            for(int i=from-1;i>to;i--)
                {temp=content[i]->placing(temp);}
            content[to]->push_back(temp);
            }
        }
    void logRaw()const
        {
        for(int i=0;i<content.size();i++)
            {
            cout<<"offset: "<<content[i]->offset<<endl;
            for(int j=0;j<content[i]->data->size();j++)
                {cout<<content[i]->data->at(j)<<", ";}
            cout<<endl;
            }
            cout<<endl;
        }
    };


#endif