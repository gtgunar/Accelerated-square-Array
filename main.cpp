//Márton Attila, 2023
//implementation is in "accarr.h" 
//this file:primarily for testing
#include<iostream>
#include<cstdlib>
#include<time.h>
#include"accarr.h"
#include<thread>
#include"SQ.h"
using namespace std;
/*
void doTask(vector<int>& controlSample,accarr<int>& tesztTarget,int task,int value,int value2)
    {
    switch(task)
        {
        case 0:{
            controlSample[value]=value2;
            tesztTarget.setAt(value,value2);
        }break;//setat
        case 1:{
                controlSample.insert(controlSample.begin()+value,value2);
                tesztTarget.insert(value,value2);
        }break;//insert
        /*case 2:{

        }break;//getat*//*
        case 2:{
                if(controlSample.size()>0&&controlSample.size()>=value){
                controlSample.erase(controlSample.begin()+value);
                tesztTarget.erase(value);
        }else cout<<"!!!";
        }break;//delete
        }
    }
bool isSame(vector<int>& controlSample,accarr<int>& tesztTarget)
    {
    if(controlSample.size()!=tesztTarget.getPop())
    {cout<<"hossz: "<<controlSample.size()<<", "<<tesztTarget.getPop();return false;}
    bool toret=true;
    int a;
    for(int i=0;i<controlSample.size();i++)
        {
        toret =toret&&( controlSample[i]==tesztTarget.getAt(i));
            if(!toret)
        {cout<<endl<<"at:"<<i<<" "<< controlSample[i]<<"!="<<tesztTarget.getAt(i)<<endl;
        cin>>a;
        }
        }

    return toret;
    }
void colog(vector<int>& controlSample,accarr<int>& tesztTarget)
    {
    for(int i=0;i<controlSample.size();i++)
        {cout<< controlSample[i]<<"---"<<tesztTarget.getAt(i)<<endl;}
    cout<<endl;
    }
void bruteTest(vector<int>& a,accarr<int>& b){
    for(int i=0;i<200000;i++)
        {doTask(a,b,rand()%3,rand()%max(1,(int)a.size()),rand()%1000);}
    if(isSame(a,b))
        {
        cout<<endl<<endl<<"test:good"<<endl;
        }
    else{cout<<"!!!";}
    }*/
int main()
{   
    teszting();
    /*vector<thread*>szalak;
    szalak.resize(24);
    for(int n=0;n<24;n++)
        {
        szalak[n]=new thread([](){StationaryQueue::test_speed(10000,0);}); 
        }
    
    auto sqstart =chrono::steady_clock::now();
    thread vecthread([](){
    auto vecstart=chrono::steady_clock::now();
    for(int i=0;i<20;i++)
        {
        for(int j=0;j<10000;j++)
            {
            StationaryQueue::test_speed(10000,1);
            }
        cout<<endl<<"A:"<<(chrono::steady_clock::now()-vecstart).count()/1000000<<endl;
        vecstart=chrono::steady_clock::now();
        }
    });
    thread sqthread([](){
    auto sqstart=chrono::steady_clock::now();
    
    for(int i=0;i<20;i++)
        {
        for(int j=0;j<10000;j++)
            {
            StationaryQueue::test_speed(10000,0);
            }
        cout<<endl<<"B:"<<(chrono::steady_clock::now()-sqstart).count()/1000000<<endl;
        sqstart=chrono::steady_clock::now();
        }
    });
    StationaryQueue::SQ<int> a(100);
    a.access(10)= a.access(20);
    a.revplace(17);
    vecthread.join();
    sqthread.join();
*/

    return 0;
}

/*for(int i=1000;i<1100;i++){
    cout<<i<<" : "<<SQRT(i)<<endl;}*/
