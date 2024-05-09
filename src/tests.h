// Márton Attila, 2023
#include"utility.h"
#include"comparee.h"
#include"SQ.h"
#include"accarr_innerData.h"
template<int size>
struct bigData
{
    double content[size];

    bigData(double x = 0)
    {
        content[0] = x;
    }
    bool operator==(const bigData &other)
    {
        return content[0] == other.content[0];
    }
};
template <int size>
ostream &operator<<(ostream &s, bigData<size> a)
{
    s << a.content[0];
    return s;
}
template <typename T>
struct task
{
    int job;
    int place;
    T value;
    task(int _job,int _place,T _value):job(_job),place(_place),value(_value){}
    void log() { cout << "TASK: "<<" "<<job << " "
                      << " " << place << " " << value << endl; }
};
template <typename T>
pair<vector<task<T>>*, vector<task<T>>*> generateTest(int baseSize, int testSize, int ratio = 8192)//how many in 16384 is mut.
{
    pair<vector<task<T>> *, vector<task<T>> *> toret = {new vector<task<T>>, new vector<task<T>>};
    srand(std::chrono::steady_clock::now().time_since_epoch().count()); // todo change to proper seeding
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
    auto start = std::chrono::steady_clock::now().time_since_epoch().count();
    //cout <<"T "<< testTasks->size()<<endl;
    for (auto i : *testTasks)
        doTask(tesztTarget, i);
    auto stop = std::chrono::steady_clock::now().time_since_epoch().count();
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
        // init testsubjects and test itself
        accarrC<T> *accarrTarget = new accarrC<T>;
        tombC<T> *vectorTarget = new tombC<T>;
        auto testTape = generateTest<T>(baseSize, testSize, ratio);
        cout << "." << flush;
        //fill up testsubject to starting size
        doTest<T>(accarrTarget, testTape.first);
        doTest<T>(vectorTarget, testTape.first);
        
        doTest(accarrTarget, testTape.second,1);
        doTest(vectorTarget, testTape.second, 1);
       if (!isSame(accarrTarget, vectorTarget))
            {
            colog(accarrTarget, vectorTarget);
            }
            // cleanup
            
            delete accarrTarget;
            delete vectorTarget;
        
    }
template<typename T>
void speedlog()
{
    for (int i = 0; i < 10;i++)
        for (int size = 10; size < 50000;size*=2){
            for (int rat = 1; rat < 20000;rat*=2)
            {
            testAccarrAndVector<T>(size, size/5, rat);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
void teszting()
{
    accarr_innerData alany;
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

template <typename T>
class accarr;
template <typename T>
void log(const accarr<T> &target)
{
    target.metaData.logMe();
    for (int i = 0; i < target.content->size(); i++)
    {
        cout << "offset: " << target.content[i]->offset << endl;
        for (int j = 0; j < target.content[i]->data->size(); j++)
        {
            cout << target.content[i]->data->at(j) << ", ";
        }
        cout << endl;
    }
    cout << endl;
}
template<typename T>
void log(const SQ<T> &target, ofstream &x = std::cout)
{
    if (target.data->size())
    {
        x << "////////////////////.-.-////--/////////" << endl;
        x << " vectorsize: " << target.data->size() << " offset: " << target.offset << endl;
        x << "raw elements:" << endl;
        for (int i = 0; i < target.data->size(); i++)
        {
            x << (*target.data)[i] << ", ";
        }
        x << endl;
        x << "read elements:" << endl;
        for (int i = 0; i < target.data->size(); i++)
        {
            x << "access attempt at " << i << target.access(i) << ", ";
        }
        x << endl
          << "|////////////.-.///////-////////////|" << endl;
    }
}