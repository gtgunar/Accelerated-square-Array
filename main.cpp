// Márton Attila, 2023
// this file:primarily for testing
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <thread>
#include <fstream>
#include "accarr.h"
#include "SQ.h"
#include "tests.h"
#include "speedcomparison.h"
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
using namespace std::chrono;
using namespace StationaryQueue;

int main()
{
    accarrC<float> alap;
    tombC<float> b;

    compare<float>(alap, 2000, 1000, 3); // OWN
    compare<float>(b, 2000, 1000, 3);    // vector
    /*
    measure:
    100 400 1000 etc
    multithreaded measure

    inRAM data measure
    */
}
