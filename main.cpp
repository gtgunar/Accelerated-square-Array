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
template<typename T>
void doTask(vector<T>& controlSample,accarr<T>& tesztTarget,int task,int value,T value2)
    {
    cout<<"task:"<<task<<":"<<value<<", "<<value2<<endl;
    cout<<"meret"<<controlSample.size()<<endl;
    if((controlSample.size()>value)||((value==0)&&(task==1)))
        {
        cout<<"task started"<<endl;
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
        
        cout<<"task finished------------------------------------------------------------------------------------"<<endl;
        }
    colog(controlSample,tesztTarget);
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
        toret =toret&&( controlSample[i]==tesztTarget.getAt(i));
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
    cout<<"COLOG:"<<controlSample.size()<<tesztTarget.getPop()<<endl;
    for(int i=0;i<tesztTarget.getPop();i++)
        {cout<< controlSample[i]<<"---"<<tesztTarget[i]<<endl;}
    cout<<endl;
    }
template<typename T>
void bruteTest(vector<T>& a,accarr<T>& b,ofstream& logFile){
    vector<string> szavak={"asd","qwe","asd2","qwasde","asqwed","qwqwre","ashd","qwfgk","astzud","qw4567e","adfgd","qwfffe","asdwer","qw4z8e","asfgfbd","qwse","artxthsd","qwcxvbne",};
    for(int i=0;i<40;i++)
        {doTask(a,b,rand()%3,rand()%max(1,(int)a.size()),rand()%20);}
    cout<<"isSame chjecked"<<endl;
    if(isSame(a,b))
        {
        logFile<<"test:good,size="<<a.size()<<endl;
        }
    else{logFile<<"!!!"<<endl;}
    }
int main()
    {   
    ofstream errorlog("log.txt");
    srand(system_clock::now().time_since_epoch().count());
    vector<int>x;
    accarr<int>y;
    for(int i=0;i<2000000000;i++)
    bruteTest(x,y,errorlog);
    errorlog.close();
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