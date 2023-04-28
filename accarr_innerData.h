#ifndef ACCAR_INNERDATA_H
#define ACCAR_INNERDATA_H
#include<tuple>
#include<iostream>
using  std::vector;
using  std::cout;
using  std::endl;
using  std::deque;
using  std::pair;
using  namespace std::chrono;

pair<int,int> divmod(int a,int b)
    {
    cout<<"DIVMOD called with "<<a<<", "<<b<<endl;    
    if(!a)return pair<int,int>(0,0) ;
    else if(b) 
        return pair<int,int>(a/b,a%b); 
    else 
        return pair<int,int>(0,0) ;
    }
        
unsigned SQRT(unsigned x)//integer square root
    {
    unsigned toret=1;
    unsigned mask=0x80000000;
    while(mask)
        {
        mask/=2;
        if(((toret+mask)*(toret+mask))<=x)
            {toret=toret+mask;}
        }
    return toret*(x>0);
    }

class accarr_innerData
    {
    public:////////////////TODO:DELETE
    int population;//actual population, NOT TO BECHANGED DIRECTLY, the setter will handle each here
    int popsqrt;//floor(sqrt(population)) <=> sqrt(popsn)
    int popextra;//current value of extra population, population-popsn
    int extraCapacity;//2*n
    pair<int,int> hotPlace;
    pair<int,int> coldPlace;
    bool endLoad;//is the end the loadingplace

    public:

    int getPop()const
        {return population;}

    pair <int,int> getHotPlace()const
        {return hotPlace;}
    
    pair <int,int> getColdPlace()const
        {return coldPlace;}

    pair<int,int>getRelPos(int index)const//the pair of block-index and the within block index for a given index value
        {
        cout<<"////////////////////////////////"<<endl;
        cout<<"getRelPos called with "<<index<<" pop: "<<population<<endl;
        logMe();
        if(endLoad)
            {cout<<"getrelpos:branch1"<<endl;return divmod(index,popsqrt);}//-1
        else
            {
            if((popextra-popsqrt)>=index/(popsqrt+1))//within the incremented block
                {cout<<"getrelpos:branch2"<<endl;return divmod(index,popsqrt+1);}
            else
                {
                int uninced=index-(popextra-popsqrt)*(popsqrt+1);//remaining population stored in nonincremented zone
                cout<<"getrelpos:branch3"<<endl;
                cout<<"popextra "<<popextra<<" popsqrt "<<popsqrt<<" index "<<index<<" uninced "<<uninced<<endl;
                return pair<int,int>(popextra-popsqrt + uninced/popsqrt , uninced%popsqrt);//inc-ed length+rest
                }
            }
        }

    bool recalculate()
        {//////////////////////////////////////////////////////////////////////
        bool toret=false;
        auto oldSQRT=popsqrt;
        popsqrt=SQRT(population);
        if(oldSQRT!=popsqrt)
            {toret= true;}
        popextra=population-popsqrt*popsqrt;
        extraCapacity=2*popsqrt;
        endLoad=popextra<popsqrt;//might be strict
        if(endLoad)
            {hotPlace=pair<int,int>(popsqrt,popextra);}///////+(population>0)
        else
            {hotPlace=pair<int,int>(popextra-popsqrt,popsqrt+1);}   
        return toret;   
        }

    accarr_innerData(int pop)
        {
        population=pop;
        recalculate();
        coldPlace=hotPlace;
        }

    bool incPop()//assumed to be called from insert
        {
        coldPlace=hotPlace;
        population++;
        return recalculate();
        }

    bool decPop()//assumed to be called from delete
        {
        if(population>1)///////////////////////////////////////////////////////////////////////////////////////////////////////////////////might be 1
            {
            population--;
            population--;
            recalculate();
            coldPlace=hotPlace;
            population++;
            }
        else if(population==1)
            {
            coldPlace=pair<int,int>(0,0);
            population--;
            }
        return recalculate();
        }

    void logMe()const
        {
        cout<<"population: "<<population<<endl<<
        "popsqrt: "<<popsqrt<<endl<<
        "popextra: "<<popextra<<endl<<
        "extraCapacity: "<<extraCapacity<<endl<<
        "hotPlaceBlock: "<<hotPlace.first<<endl<<
        "hotPlaceInner: "<<hotPlace.second<<endl<<
        "coldPlaceBlock: "<<coldPlace.first<<endl<<
        "coldPlaceInner: "<<coldPlace.second<<endl<<
        "endload?:"<<endLoad<<endl;
        }

    };





    void teszting()
        {
        accarr_innerData alany(0);
        alany.logMe();
        for(int i=0;i<18;i++)
            {
            cout<<"/////////////"<<endl;
            alany.incPop();
            alany.logMe();
            //alany.decPop();
            cout<<"/////////////"<<endl;
            }
        for(int i=0;i<18;i++)
            {
            cout<<"/////////////"<<endl;
            //alany.incPop();
            alany.logMe();
            alany.decPop();
            cout<<"/////////////"<<endl;
            }
        }
    
#endif