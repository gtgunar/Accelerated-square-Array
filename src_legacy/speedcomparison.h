#ifndef SPEEDCOMPARISON_H
#define SPEEDCOMPARISON_H
#include <chrono>
#include <vector>
#include <list>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include "accarr.h"
#include "comparee.h"
using namespace std;
// template <typename T>

template <typename T>
void compare(compareeInterFace<T> &other, int length, int loadlength, int writeRatio = 10)
{
    srand(27);
    vector<T> values;
    int valuei = 0;
    vector<int> tasks;
    vector<int> indexes;
    int currentSize = 0;

    for (int i = 0; i < length - loadlength; i++) // generating task
    {
        int job;
        if (currentSize)
            if (((rand() % writeRatio)))
                job = (rand() % 2) * 3;
            else
                job = 1;
        else
            job = 0;
        indexes.push_back(rand() % (currentSize + (job == 0)));
        tasks.push_back(job);
        switch (job)
        {
        case 0:
        {
            currentSize++;
            values.push_back((rand() % 10000) / 100);
        }
        break;
        case 1:
        {
            values.push_back((rand() % 10000) / 100);
        }
        case 3:
        {
            currentSize--;
        }
        break;
        }
    }
    vector<T> accarrReads;
    auto start = chrono::steady_clock::now().time_since_epoch().count();
    accarr<float> alany;
    for (int i = 0; i < loadlength; i++)
    {
        other.addAt(indexes[i], 0);
    }
    for (int i = 0; i < length - loadlength; i++) // doing task on Accelerated Array
    {
        switch (tasks[i])
        {
        case 0: // insert
        {
            other.addAt(indexes[i], values[valuei++]);
        }
        break;
        case 1: // set
        {
            other.setAt(indexes[i], values[valuei++]);
        }
        break;
        case 2: // get
        {
            accarrReads.push_back(other.getAt(indexes[i]));
        }
        break;
        case 3: // erase
        {
            other.removeAt(indexes[i]);
        }
        break;
        }
    }
    cout << (chrono::steady_clock::now().time_since_epoch().count() - start) / 1000000.0;

    //  cout << "length: " << length << "ratio: " << writeRatio << "\t\t" << (chrono::steady_clock::now().time_since_epoch().count() - start) / 1000000.0 << " ms" << endl;
}
template <typename T>
void compareLocal(int length, int loadlength, int writeRatio = 10)
{
    accarrC<T> other;
    srand(27);
    vector<T> values;
    int valuei = 0;
    vector<int> tasks;
    vector<int> indexes;
    int currentSize = 0;

    for (int i = 0; i < length - loadlength; i++) // generating task
    {
        int job;
        if (currentSize)
            if (((rand() % writeRatio)))
                job = (rand() % 2) * 3;
            else
                job = 1;
        else
            job = 0;
        indexes.push_back(rand() % (currentSize + (job == 0)));
        tasks.push_back(job);
        switch (job)
        {
        case 0:
        {
            currentSize++;
            values.push_back((rand() % 10000) / 100);
        }
        break;
        case 1:
        {
            values.push_back((rand() % 10000) / 100);
        }
        case 3:
        {
            currentSize--;
        }
        break;
        }
    }
    vector<T> accarrReads;
    auto start = chrono::steady_clock::now().time_since_epoch().count();
    accarr<float> alany;
    for (int i = 0; i < loadlength; i++)
    {
        other.addAt(indexes[i], 0);
    }
    for (int i = 0; i < length - loadlength; i++) // doing task on Accelerated Array
    {
        switch (tasks[i])
        {
        case 0: // insert
        {
            other.addAt(indexes[i], values[valuei++]);
        }
        break;
        case 1: // set
        {
            other.setAt(indexes[i], values[valuei++]);
        }
        break;
        case 2: // get
        {
            accarrReads.push_back(other.getAt(indexes[i]));
        }
        break;
        case 3: // erase
        {
            other.removeAt(indexes[i]);
        }
        break;
        }
    }
    cout << (chrono::steady_clock::now().time_since_epoch().count() - start) / 1000000.0;

    //  cout << "length: " << length << "ratio: " << writeRatio << "\t\t" << (chrono::steady_clock::now().time_since_epoch().count() - start) / 1000000.0 << " ms" << endl;
}

/*testfunc:
    takes taskvector and valuevector(or seed for rng)
        checks if job is valid while running
    makes ACCARR and target alternative
        run jobs sequentially with wait time
        run jobs parallel to themselves x times
    check final validness
    log results
*/
#endif