#ifndef ACCAR_INNERDATA_H
#define ACCAR_INNERDATA_H
#include<tuple>
using namespace std;

unsigned SQRT(unsigned x)
    {
    unsigned toret=1;
    unsigned mask=0x80000000;
    while(mask)
        {
        mask/=2;
        if(((toret+mask)*(toret+mask))<=x)
            {toret=toret+mask;}
        
        }
    return toret;
    }

class accarr_innerData
    {
    int population;//actual population, NOT TO BECHANGED DIRECTLY, the setter will handle each here
    int popsqrt;//floor(sqrt(population)) <=> sqrt(popsn)
    int popextra;//current value of extra population, population-popsn
    int extraCapacity;//2*n
    pair<int,int> hotPlace;
    bool endLoad;//is the end the loadingplace

    public:
    int getPop()const{return population;}
    accarr_innerData(int pop)
        {
        population=pop;
        popsqrt=SQRT(pop);
        popextra=pop-popsqrt*popsqrt;
        extraCapacity=population-popsqrt*popsqrt;
        
        endLoad=popextra<popsqrt;
        }
    pair <int,int> getHotPlace()const{return hotPlace;}
    pair<int,int>getRelPos(int index)const//the pair of block-index and the within block index for a given index value
        {
        return pair<int,int>(0,0);
        }
    void incPop()//assumed to be called from insert
        {
        population++;
        if(popextra!=extraCapacity)//still has room
            {
            popextra++;
            if(endLoad)
                {hotPlace.second++;}
            else
                {hotPlace.first++;}
            if(popextra==popsqrt)
                {
                hotPlace.first=0;
                hotPlace.second++;
                }
            endLoad=popextra<popsqrt;
            }
        else//new square reached
            {
            popsqrt++;
            popextra=0;
            extraCapacity+=2;
            }
        
        }
    void decPop()//assumed to be called from delete
        {
        
        }
    };

#endif