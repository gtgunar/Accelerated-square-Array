#ifndef ACCAR_INNERDATA_H
#define ACCAR_INNERDATA_H
#include <tuple>
#include<functional>
#include <iostream>
using std::cout;
using std::deque;
using std::endl;
using std::pair;
using std::vector;
using namespace std::chrono;
struct accarr_innerData;
pair<int, int>
divmod(int a, int b) // 519-584 before rework
{
    if (a && b)
        return pair<int, int>(a / b, a % b);
    else
        return pair<int, int>(0, 0);
}

unsigned SQRT(unsigned x) // integer square root
{
    unsigned toret = 1;
    unsigned mask = 0x80000000;
    while (mask)
    {
        mask /= 2;
        if (((toret + mask) * (toret + mask)) <= x)
        {
            toret = toret + mask;
        }
    }
    return toret * (x > 0);
}
pair<int, int> ret0Pos      (int a, const accarr_innerData *target);
pair<int, int> posNoEndload (int a, const accarr_innerData *target);
pair<int, int> posEndload   (int a, const accarr_innerData *target);

struct accarr_innerData
{
    int population;    // actual population, NOT TO BECHANGED DIRECTLY, the setter will handle each here
    int popsqrt;       // floor(sqrt(population)) <=> sqrt(popsn)
    int popextra;      // current value of extra population, population-popsn
    int extraCapacity; // 2*n
	uint64_t reciprocOfpopsqrt;
	uint64_t reciprocOfpopsqrtp1;
    pair<int, int> (*activeGetPos)(int a, const accarr_innerData *target); // handle on create and insert/delete

    pair<int, int> hotPlace;
    pair<int, int> coldPlace;
    bool endLoad; // is the end the loadingplace

    

public:
    int getPop() const                          {return population  ;}
    pair<int, int> getHotPlace() const          {return hotPlace    ;}
    pair<int, int> getColdPlace() const         {return coldPlace   ;}
    pair<int, int> getRelPos(int index) const   {return (*activeGetPos)(index,this);}
    pair<int, int> legacy_getRelPos(int index) const
    {
        if (population == 0)
            return ret0Pos(index,this);
        else if (endLoad) // is? the loading happen at the end
            return posNoEndload(index, this);
        else
            return posEndload(index, this);
    }

    pair<int, int> calcHotPlace() const         {
        if (popextra == 2 * popsqrt + 1)
        {
            return pair<int, int>(popsqrt + 1, 0);
        }
        else if (popextra < popsqrt)
        {
            return pair<int, int>(popsqrt, popextra);
        }
        else
        {
            return pair<int, int>(popextra - popsqrt, popsqrt);
        }
    }

    bool recalculate()
    {
        bool toret = false;
        auto oldSQRT = popsqrt;
        popsqrt = SQRT(population);
        auto incSQRT = SQRT(population + 1);
        if (oldSQRT != incSQRT)
        {
            toret = true;
        }
        popextra = population - popsqrt * popsqrt;
        extraCapacity = 2 * popsqrt;
        endLoad = popextra < popsqrt;
        coldPlace = hotPlace;
        if (population >= 1)
        {

            hotPlace = calcHotPlace();
        }
        else
        {
            hotPlace = pair<int, int>(0, 0);
        }
        if (population == 0)
            activeGetPos = &ret0Pos;
        else if (endLoad) // is? the loading happen at the end
            activeGetPos = &posNoEndload;
        else
            activeGetPos = &posEndload;

        return toret;
    }

    accarr_innerData(int pop)
    {
        population = pop;
        recalculate();
        coldPlace = hotPlace;
        activeGetPos = &ret0Pos;
    }

    bool incPop() // assumed to be called from insert
    {
        coldPlace = hotPlace;
        population++;
        return recalculate();
    }

    bool decPop() // assumed to be called from delete
    {
        population--;
        population--;
        recalculate();
        coldPlace = hotPlace;
        population++;
        return recalculate() && population;
    }

    void logMe() const
    {
        cout << "population: " << population << endl
             << "popsqrt: " << popsqrt << endl
             << "popextra: " << popextra << endl
             << "extraCapacity: " << extraCapacity << endl
             << "hotPlaceBlock: " << hotPlace.first << endl
             << "hotPlaceInner: " << hotPlace.second << endl
             << "coldPlaceBlock: " << coldPlace.first << endl
             << "coldPlaceInner: " << coldPlace.second << endl
             << "endload?:" << endLoad << endl;
        for (int i = 0; i < population; i++)
        {
            cout << i << ":" << getRelPos(i).first << "," << getRelPos(i).second << ";" << endl;
        }
    }
};
pair<int, int> ret0Pos(int a, const accarr_innerData *target)
{
    return pair<int, int>(0, 0);
}
pair<int, int> posNoEndload(int a, const accarr_innerData *target)
{
    return divmod(a, target->popsqrt);
}
pair<int, int> posEndload(int a, const accarr_innerData *target)
{
    if ((target->popextra - target->popsqrt) > a / (target->popsqrt + 1)) // is? loading within the incremented block
    {
        return divmod(a, target->popsqrt + 1);
    }
    else
    {
        int uninced = a - (target->popextra - target->popsqrt) * (target->popsqrt + 1);                                   // remaining population stored in nonincremented zone
        return pair<int, int>(target->popextra - target->popsqrt + uninced / target->popsqrt, uninced % target->popsqrt); // inc-ed length+rest
    }
}

void teszting()
{
    accarr_innerData alany(0);
    alany.logMe();
    for (int i = 0; i < 18; i++)
    {
        cout << "/////////////" << endl;
        alany.incPop();
        alany.logMe();
        cout << "/////////////" << endl;
    }
    for (int i = 0; i < 18; i++)
    {
        cout << "/////////////" << endl;
        alany.logMe();
        alany.decPop();
        cout << "/////////////" << endl;
    }
}

#endif
