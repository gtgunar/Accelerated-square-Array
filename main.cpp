//Márton Attila, 2023
//implementation is in "accarr.h" 
//this file:primarily for testing
#include<iostream>
#include<cstdlib>
#include<time.h>
#include"accarr.h"
using namespace std;

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

        }break;//getat*/
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
    if(controlSample.size()!=tesztTarget.population)
    {cout<<"hossz: "<<controlSample.size()<<", "<<tesztTarget.population;return false;}
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
    }
int main()
{
    accarr<int> teszted;

    for(int i=0;i<20;i++)
        {
        cout<<"\t"<<i<<endl<<endl;
        teszted.population=i;
        for(int j=0;j<i;j++)
            {cout<<"j:"<<j<<" got: "<<teszted.getRelPos(j).first<<"/"<<teszted.getRelPos(j).second<<endl;}

        }
    srand(time(0));
    cout<<rand()%7<<","<<rand()%7<<endl;
    vector<int> a;
    accarr<int> b;
    a.insert(a.begin(),77);
    b.insert(0,77);
    for(int i=0;i<100;i++)
        {doTask(a,b,1,0,rand()%1000);}
    for(int i=0;i<100;i++)
        {doTask(a,b,0,i,i);}
    colog(a,b);
    for(int i=92;i<94;i++)
        {doTask(a,b,0,i,i);doTask(a,b,2,i,i);}
    colog(a,b);
    b[27]=222;
    cout<<b[27]<<endl;
    ///
    bruteTest(a,b);
    return 0;
}
