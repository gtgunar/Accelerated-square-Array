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
#include "speedcoparison.h"
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
    ofstream x("rawout.txt");
    vector<float> a;
    accarr<float> b;
    for (int i = 0; i < 100; i++)
        bruteTest(a, b, x);
    cout << "DONE" << endl;
    return 0;
}
