// Márton Attila, 2023
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <fstream>
#include "accarr.h"
#include "SQ.h"
#include"comparee.h"

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
struct task
{
    int job;
    int place;
    T value;
    task(int _job,int _place,T _value):job(_job),place(_place),value(_value){}
};
template <typename T>
pair<vector<task<T>>*, vector<task<T>>*> generateTest(int baseSize, int testSize, int ratio = 8192)//how many in 16384 is mut.
{
    pair<vector<task<T>> *, vector<task<T>> *> toret = {new vector<task<T>>, new vector<task<T>>};
    srand(chrono::steady_clock::now().time_since_epoch().count()); // todo change to proper seeding
    for (int i = 0; i < baseSize;i++)
        toret.first->push_back(task(1, i, (T)i));
    for (int i = 0; i < testSize; i++)
    {
        int runningSize = baseSize; // supposed size at any given moment of testing
       
        if (runningSize)
        {
            if (rand() % 16384 < ratio)
            {
                switch(rand()%2)
                    {
                    case 0:
                        toret.second->push_back(task(1, rand() % (runningSize++), (T)i));
                        break;
                    case 1:
                        toret.second->push_back(task(2, rand() % runningSize--, (T)0));
                        break;
                    }
                }
            else
                toret.second->push_back(task(0, rand() % runningSize, (T)i));
        }
            else
                toret.second->push_back(task(1, runningSize++, (T)i)); // runningSize=0
        }
    return toret;
}
template <typename T>
void doTest(compareeInterFace<T> *tesztTarget, vector<task<T>> *testTasks, bool display = false)
{
    auto start = chrono::steady_clock::now().time_since_epoch().count() ;
    //cout <<"T "<< testTasks->size()<<endl;
    for (auto i : *testTasks)
        doTask(tesztTarget, i);
    auto stop = chrono::steady_clock::now().time_since_epoch().count() ;
    if(display)
        cout << (stop - start)/1000000.0 <<" ";
}
template <typename T>
void doTask(compareeInterFace<T> *tesztTarget, task<T> currentTask)
{
    //cout << "TASK: "<<tesztTarget->getSize()<<" " << currentTask.job << " " << currentTask.place << " " << currentTask.value << endl;
    int place;
    if (tesztTarget->getSize())
        place = currentTask.place % tesztTarget->getSize();
    else
         place = 0;
    switch (currentTask.job)
    {
    case 0:
        tesztTarget->setAt(place, currentTask.value);
        break; // setat*/
    case 1:
        tesztTarget->addAt(place, currentTask.value);
        break;
    case 2:
        tesztTarget->removeAt(place);
        break;
    }
    }
    template <typename T>
    bool isSame(compareeInterFace<T> *controlSample, compareeInterFace<T> *tesztTarget)
    {
        if (controlSample->getSize() != tesztTarget->getSize())
        {
            cout << "hossz: " << controlSample->getSize() << ", " << tesztTarget->getSize();
            return false;
        }
        bool toret = true;
        for (int i = 0; i < controlSample->getSize(); i++)
        {
            toret = toret && (controlSample->getAt(i) == tesztTarget->getAt(i));
            if (!toret)
            {
                cout << endl
                     << "at:" << i << " " << controlSample->getAt(i) << "!=" << tesztTarget->getAt(i) << endl;
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
            }
        } 
        return toret;
    }

    template <typename T>
    void testAccarrAndVector( int baseSize, int testSize, float ratio = 1)
    {
       // cout << "--" << endl;
        // init testsubjects and test itself
        accarrC<T> *accarrTarget = new accarrC<T>;
        tombC<T> *vectorTarget = new tombC<T>;
        auto testTape = generateTest<T>(baseSize, testSize, ratio);

        //fillup testsubject to starting size
        doTest<T>(accarrTarget, testTape.first);
        doTest<T>(vectorTarget, testTape.first);
      
        //do speedtest
     //   cout << "Accarr: ";
        doTest(accarrTarget, testTape.second,1);
       // cout << endl
        //     << "vector: ";
     /*  doTest(vectorTarget, testTape.second,1);
       // cout << endl;
        //verify after speedtest is done
        if (isSame(accarrTarget, vectorTarget))
        {
            cout << "test passed" << endl;
            }
        else{
            colog(accarrTarget, vectorTarget);
        }*/
        //cleanup
        delete accarrTarget;
        delete vectorTarget;
    }
template<typename T>
void speedlog()
{
    for (int i = 0; i < 10;i++)
        for (int size = 10; size < 130000;size*=2){
            for (int rat = 1; rat < 20000;rat*=2)
            {
            testAccarrAndVector<T>(size, size/5, rat);
            sleep_for(chrono::milliseconds(100));
            }
            cout << endl;
        }
}
template <typename T>
void colog(compareeInterFace<T> *controlSample, compareeInterFace<T> *tesztTarget)
{
    cout << "COLOG:" << controlSample->getSize() << ":" << tesztTarget->getSize() << endl;
    for (int i = 0; i < tesztTarget->getSize(); i++)
    {
        cout << controlSample->getAt(i) << "---" << tesztTarget->getAt(i)<< endl;
    }
    cout << endl;
}
