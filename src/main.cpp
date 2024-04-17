// Márton Attila, 2023
// this file:primarily for testing
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <thread>
#include<chrono>
#include <fstream>
#include "accarr.h"
#include "SQ.h"
#include "tests.h"
#include "comparee.h"
using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::max;
using std::ofstream;
using std::pair;
using std::string;
using std::vector;
using std::this_thread::sleep_for;
using namespace std::chrono;
using namespace StationaryQueue;

struct bigData
{
    double content[1024];

    bigData(double x = 0)
    {
        content[0] = x;
    }
bool operator==(const bigData&other)
{
    return content[0] == other.content[0];
}
};
ostream &operator<<(ostream &s,bigData a)
{
    s << a.content[0];
    return s;
}
int main()
{
    speedlog<double>();
}
