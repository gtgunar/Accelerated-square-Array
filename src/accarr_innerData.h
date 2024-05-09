#ifndef ACCAR_INNERDATA_H
#define ACCAR_INNERDATA_H
#include "utility.h"

struct accarr_innerData;
struct fplace; 
// these fuiunctions are external becaulse function pointers to members are a mess
fplace ret0Pos(int a, const accarr_innerData *target);
fplace posNoEndload (int a, const accarr_innerData *target);
fplace posEndload   (int a, const accarr_innerData *target);

struct accarr_innerData
{
    int population;    // actual population, NOT TO BECHANGED DIRECTLY, the setter will handle each here
    int popsqrt;       // floor(sqrt(population)) <=> sqrt(popsn)
    int popextra;      // current value of extra population, population-popsn
    int extraCapacity; // 2*n

    fplace hotPlace;
    fplace coldPlace;

    fplace (*activeGetPos)(int a, const accarr_innerData *target); // handle on create and insert/delete
    bool endLoad;                                                  // is the end the loadingplace

public:
    int getPop() const                  {return population  ;}
    fplace getHotPlace() const          {return hotPlace    ;}
    fplace getColdPlace() const         {return coldPlace   ;}
    fplace getRelPos(int index) const   {return (*activeGetPos)(index,this);}


    fplace calcHotPlace()          
    {
        if (popextra >extraCapacity)
            return fplace(popsqrt + 1, 0);
        else if (endLoad)
            return fplace(popsqrt, popextra);
        else
            return fplace(popextra - popsqrt, popsqrt);
    }

    bool recalculate()
    {
        int oldSQRT = popsqrt;
        popsqrt = SQRT(population);
        auto incSQRT = SQRT(population + 1);
        bool changedSquare = (oldSQRT != incSQRT);

        popextra = population - popsqrt * popsqrt;
        extraCapacity = 2 * popsqrt;
        endLoad = popextra < popsqrt;
        coldPlace = hotPlace;

        if (population >= 1)
            hotPlace = calcHotPlace();
        else
            hotPlace = fplace(0, 0);

        if (population == 0)
            activeGetPos = &ret0Pos;
        else if (endLoad) // is? the loading happen at the end
            activeGetPos = &posNoEndload;
        else
            activeGetPos = &posEndload;

        return changedSquare;
    }

    accarr_innerData()
    {
        population = 0;
        recalculate();
        coldPlace = fplace(0,0);
        activeGetPos = &ret0Pos;
    }

    bool incPop() // assumed to be called from insert
    {
        coldPlace = hotPlace;
        population++;
        bool sizeChanged = recalculate();
        return sizeChanged;
    }

    bool decPop() // assumed to be called from delete
    {
        population-=2;
        recalculate();
        coldPlace = hotPlace;
        population++;
        bool sizeChanged = recalculate();
        return sizeChanged && population;
    }

    void logMe() const
    {
        cout << "population: " << population << endl
             << "popsqrt: " << popsqrt << endl
             << "popextra: " << popextra << endl
             << "extraCapacity: " << extraCapacity << endl
             << "hotPlaceBlock: " << hotPlace.upper << endl
             << "hotPlaceInner: " << hotPlace.lower << endl
             << "coldPlaceBlock: " << coldPlace.upper << endl
             << "coldPlaceInner: " << coldPlace.lower << endl
             << "endload?:" << endLoad << endl;
        for (int i = 0; i < population; i++)
        {
            cout << i << ":" << getRelPos(i).upper << "," << getRelPos(i).lower << ";" << endl;
        }
    }
};

fplace ret0Pos(int a, const accarr_innerData *target)
{
    return fplace(0, 0);
}
fplace posNoEndload(int a, const accarr_innerData *target)
{
    return divmod(a, target->popsqrt);
}
fplace posEndload(int a, const accarr_innerData *target)
{
    if ((target->popextra - target->popsqrt) > a / (target->popsqrt + 1)) // is? loading within the incremented block
    {
        return divmod(a,  target->popsqrt + 1);
    }
    else
    {
        int uninced = a - (target->popextra - target->popsqrt) * (target->popsqrt + 1);                                   // remaining population stored in nonincremented zone
        return divmod(uninced, target->popsqrt) + (target->popextra - target->popsqrt);               // inc-ed length+rest
    }
}


#endif
