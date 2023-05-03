//Márton Attila, 2023
//implementation is in "accarr.h" 
//this file:primarily for testing
#include<iostream>
#include<cstdlib>
#include<time.h>
#include"accarr.h"
#include<thread>
#include"SQ.h"
#include<fstream>

using  std::ofstream;
using  std::vector;
using  std::cout;
using  std::cin;
using  std::endl;
using  std::deque;
using  std::pair;
using  std::max;
using  std::string;
using  namespace std::chrono;
using namespace StationaryQueue;//////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
void doTask(vector<T>& controlSample,accarr<T>& tesztTarget,int task,int value,T value2)
    {
    if((controlSample.size()>value)||((value==0)&&(task==1)))//invalid jobs skipped
        {
      //  cout<<"task:"<<task<<":"<<value<<", "<<value2<<endl;
      //  cout<<"meret"<<tesztTarget.getPop()<<endl;
      //  cout<<"task started"<<endl;
        switch(1)
            {
            case 0:{  
                controlSample[value]=value2;
                tesztTarget[value]=value2;
            }break;//setat*/
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
       // cout<<"outcome checked------------------------                         --------------------------------"<<endl;
        isSame(controlSample,tesztTarget);
       // cout<<"task finished------------------------------------------------------------------------------------"<<endl;
       // colog(controlSample,tesztTarget);
      //  tesztTarget.logRaw();
       // for(auto i: controlSample){cout<<i<<", ";}
       // cout<<endl;
        string a;
        //cin>>a;

        }
    
    }
template<typename T>
bool isSame(vector<T>& controlSample,accarr<T>& tesztTarget)
    {
    if(controlSample.size()!=tesztTarget.getPop())
    {cout<<"hossz: "<<controlSample.size()<<", "<<tesztTarget.getPop();return false;}
    bool toret=true;
    int a;
    for(int i=0;i<controlSample.size();i++)
        {
        toret =toret&&( controlSample[i]==tesztTarget[i]);
        if(!toret)
            {
            cout<<endl<<"at:"<<i<<" "<< controlSample[i]<<"!="<<tesztTarget.getAt(i)<<endl;
            cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
            }
        }

    return toret;
    }
template<typename T>
void colog(vector<T>& controlSample,accarr<T>& tesztTarget)
    {
    cout<<"COLOG:"<<controlSample.size()<<":"<<tesztTarget.getPop()<<endl;
    for(int i=0;i<tesztTarget.getPop();i++)
        {cout<< controlSample[i]<<"---"<<tesztTarget[i]<<endl;}
    cout<<endl;
    }
template<typename T>
void bruteTest(vector<T>& a,accarr<T>& b,ofstream& logFile){
    vector<string> szavak={"asd","qwe","asd2","qwasde","asqwed","qwqwre","ashd","qwfgk","astzud","qw4567e","adfgd","qwfffe","asdwer","qw4z8e","asfgfbd","qwse","artxthsd","qwcxvbne",};
    for(int i=0;i<100;i++)
        {doTask(a,b,rand()%3,rand()%max(1,(int)a.size()),0.5f+(float)(rand()%20));}/////////////////////////////////
    //cout<<"isSame chjecked"<<endl;
    if(isSame(a,b))
        {
        cout<<".";
        }
    else{cout<<"\n!!!\n"<<endl;}
    }
int main()
    {   /*
   SQ<float> a;
    a.addTo(0,7.3);
    //a.log();
    a.addTo(0,1.3);
    //a.log();
    a.addTo(1,10.3);
    //a.log();
    //1.3, 10.3, 7.3
    a.push_back(0.1);
   
    a.push_front(44.4);
    a.log();
    cout<<a.placing(0.001)<<endl;a.log();
    //cout<<a.revplace(0.1001)<<endl;a.log();
cout<<a.placing(0.201)<<endl;a.log();
cout<<a.placing(0.301)<<endl;a.log();
cout<<a.placing(0.4001)<<endl;a.log();
cout<<a.placing(0.501)<<endl;
a.log();
a.addTo(5,3.3);
a.log();
a.addTo(0,30.3);
a.log();
a.deleteFrom(1);
a.log();
cout<<endl<<a.data->size()<<","<<a.offset<<endl;
    for(int i=0;i<=a.data->size();i++)
        {
        //cout<<i<<":"<<a.getShiftedPos(i)<<", "<<endl;
        }
    */
    ofstream x("rawout.txt");
    vector<float>a;
    accarr<float>b;
    for(int i=0;i<100;i++)
    bruteTest(a,b,x);
    cout<<"DONE"<<endl;
    return 0;
    }

/*crashes:
értékadás számból stringbe convertálásnál
shifted place=actual place
todo:getshiftedPos
balanceshift to empty SQ
1 0 0 task
erase
memleak from never dleteing empty SQs
*/