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

class bigData
{
    double content[1024];

public:
    bigData(double x = 0)
    {
        content[0] = x;
    }
};
int main()
{
    accarrC<bigData> alap;
    for (int asd = 0; asd < 5; asd++)
    {
        tombC<bigData> b;
        // compare<float>(alap, 2000, 1000, 3); // OWN
        for (int i = 5; i < 10000; i *= 2)
        {
            for (int j = 1; j < 257; j *= 2)
            {
                compare<bigData>(b, i * 2, i, j);
                cout << " ";
            } // vector
            cout << endl;
        }
        cout << endl
             << endl;
    }
    /*
    measure:

    100 400 1000 etc
    single/multithreaded(inRAM data) measure
    measure deque and list and try to debug
    meausre under highly demanding other work( Monero Miner)
    */
}
