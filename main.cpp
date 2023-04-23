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

void doTask(vector<int>& controlSample,accarr<int>& tesztTarget,int task,int value,int value2)
    {
    switch(task)
        {
        case 0:{
            controlSample[value]=value2;
            tesztTarget[value]=value2;
        }break;//setat
        case 1:{
                controlSample.insert(controlSample.begin()+value,value2);
                tesztTarget.insert(value,value2);
        }break;//insert
        case 2:{
                if(controlSample.size()>0&&controlSample.size()>=value)
                    {
                    controlSample.erase(controlSample.begin()+value);
                    tesztTarget.erase(value);
                    }
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
            {
            cout<<endl<<"at:"<<i<<" "<< controlSample[i]<<"!="<<tesztTarget.getAt(i)<<endl;
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
    for(int i=0;i<200;i++)
        {doTask(a,b,rand()%3,rand()%max(1,(int)a.size()),rand()%1000);}
    if(isSame(a,b))
        {
        cout<<endl<<endl<<"test:good"<<endl;
        }
    else{cout<<"!!!";}
    }
int main()
    {   
    vector<int> x;
    accarr<int> y;
    y.metaData.logMe();
    y.insert(0,0);

    return 0;
    }

