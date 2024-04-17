// Márton Attila, 2023
// this file:primarily for testing
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <thread>
#include <fstream>
#include "accarr.h"
#include "SQ.h"

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

template <typename T>
void doTask(vector<T> &controlSample, accarr<T> &tesztTarget, int task, int value, T value2)
{
    if ((controlSample.size() > value) || ((value == 0) && (task == 1))) // invalid jobs skipped
    {
        switch (task)
        {
        case 0:
        {
            controlSample[value] = value2;
            tesztTarget[value] = value2;
        }
        break; // setat*/
        case 1:
        {
            controlSample.insert(controlSample.begin() + value, value2);
            tesztTarget.insert(value, value2);
        }
        break; // insert
        case 2:
        {
            if (controlSample.size() > 0 && controlSample.size() >= value)
            {
                controlSample.erase(controlSample.begin() + value);
                tesztTarget.erase(value);
            }
        }
        break; // delete
        }
        isSame(controlSample, tesztTarget);
        string a;
    }
}
template <typename T>
bool isSame(vector<T> &controlSample, accarr<T> &tesztTarget)
{
    if (controlSample.size() != tesztTarget.getPop())
    {
        cout << "hossz: " << controlSample.size() << ", " << tesztTarget.getPop();
        return false;
    }
    bool toret = true;
    int a;
    for (int i = 0; i < controlSample.size(); i++)
    {
        toret = toret && (controlSample[i] == tesztTarget[i]);
        if (!toret)
        {
            cout << endl
                 << "at:" << i << " " << controlSample[i] << "!=" << tesztTarget.getAt(i) << endl;
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        }
    }

    return toret;
}
template <typename T>
void colog(vector<T> &controlSample, accarr<T> &tesztTarget)
{
    cout << "COLOG:" << controlSample.size() << ":" << tesztTarget.getPop() << endl;
    for (int i = 0; i < tesztTarget.getPop(); i++)
    {
        cout << controlSample[i] << "---" << tesztTarget[i] << endl;
    }
    cout << endl;
}
template <typename T>
void bruteTest(vector<T> &a, accarr<T> &b, ofstream &logFile)
{
    vector<string> szavak = {
        "asd",
        "qwe",
        "asd2",
        "qwasde",
        "asqwed",
        "qwqwre",
        "ashd",
        "qwfgk",
        "astzud",
        "qw4567e",
        "adfgd",
        "qwfffe",
        "asdwer",
        "qw4z8e",
        "asfgfbd",
        "qwse",
        "artxthsd",
        "qwcxvbne",
    };
    for (int i = 0; i < 100; i++)
    {
        doTask(a, b, rand() % 3, rand() % max(1, (int)a.size()), 0.5f + (float)(rand() % 20));
    }
    if (isSame(a, b))
    {
        cout << ".";
    }
    else
    {
        cout << "\n!!!\n"
             << endl;
    }
}
