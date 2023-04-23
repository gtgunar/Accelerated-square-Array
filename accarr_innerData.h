#ifndef ACCAR_INNERDATA_H
#define ACCAR_INNERDATA_H
#include<tuple>
#include<iostream>
using namespace std;

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
        if(endLoad)
            {return pair<int,int>(index/popsqrt,index%popsqrt);}
        else
            {
            if((popextra-popsqrt)<=index/(popsqrt+1))//within the incremented block
                {return pair<int,int>(index/(popsqrt+1),index%(popsqrt+1));}
            else
                {
                int uninced=index-(popextra-popsqrt)*(popsqrt+1);//remaining population stored in nonincremented zone
                return pair<int,int>(popextra-popsqrt + uninced/popsqrt , uninced%popsqrt);//inc-ed length+rest
                }
            }
        
        
        }

    void recalculate()
        {
        popsqrt=SQRT(population);
        popextra=population-popsqrt*popsqrt;
        extraCapacity=2*popsqrt;
        endLoad=popextra<=popsqrt;
        if(endLoad)
            {hotPlace=pair<int,int>(popsqrt+1,popextra);}
        else
            {hotPlace=pair<int,int>(popextra-popsqrt,popsqrt+1);}      
        }

    accarr_innerData(int pop)
        {
        population=pop-1;
        recalculate();
        coldPlace=hotPlace;
        population=pop;
        recalculate();
        }

    void incPop()//assumed to be called from insert
        {
        coldPlace=hotPlace;
        population++;
        recalculate();
        }

    void decPop()//assumed to be called from delete
        {
        if(population>1)
            {
            population--;
            population--;
            recalculate();
            coldPlace=hotPlace;
            population++;
            recalculate();
            }
        else
            {
            coldPlace=pair<int,int>(0,0);
            population--;
            recalculate();
            }
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