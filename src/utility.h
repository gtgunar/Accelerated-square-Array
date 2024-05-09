#ifndef UTILITY_H
#define UTILITY_H
#include <vector>
#include <deque>    //only for debugging
#include <iostream> //only for debugging
#include <cstdlib>  //only for debugging
#include <chrono>   //only for debugging
#include <fstream>  //only for debugging
#include <cmath>
#include<thread>
#include <list>
#include <tuple>
#include <functional>

using std::begin;
using std::cin;
using std::cout;
using std::deque;
using std::end;
using std::endl;
using std::flush;
using std::list;
using std::max;
using std::ofstream;
using std::ostream;
using std::pair;
using std::string;
using std::vector;
// and std::chrono in place;

struct accarr_innerData;
struct alignas(sizeof(int) * 2) fplace
{
    int upper, lower;
    fplace(int a = 0, int b = 0) : upper(a), lower(b) {}
    void operator=(const fplace &other)
    {
        upper = other.upper;

        lower = other.lower;
    }
    fplace operator+(const int other)
    {
        fplace toret = *this;
        toret.upper += other;
        return toret;
    }
};

fplace divmod(int a, int b)
{
    if (a && b) // 0 DIV 0 and 0 MOD 0 returns "0 0"
        return fplace(a / b, a % b);
    else
        return fplace(0, 0);
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

#endif