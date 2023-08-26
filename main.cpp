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
    listC<float> a;
    tombC<float> b;
    // need:btree
    // b+/*tree
    // maybe skiplist
    controlMeres<float>(27, 400000);
    compare<float>(a, 27, 400000);
    compare<float>(b, 27, 400000);
    /*
    measure:
    100 400 1000 etc
    */
}
