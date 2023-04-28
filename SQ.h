#ifndef STATIONARY_QUEUE_H
#define STATIONARY_QUEUE_H
#include<vector>
#include<deque>//only for debugging
#include<iostream>//only for debugging
#include<cstdlib>//only for debugging
#include<chrono>//only for debugging
#include<fstream>//only for debugging
using  std::ofstream;
using  std::vector;
using  std::cout;
using  std::endl;
using  std::deque;
using  namespace std::chrono;

namespace StationaryQueue
    {
    template<typename T>
    void swapAround(T*a,T*b)
        {
        T temp=*a;
        *a=*b;
        *b=temp;
        }
    template<typename T>
    class SQ// stationary queue, with fix size, single memory access on combined en-/dequeue, both ways
        {
        //private:
        public:
            short int offset;
            deque<T>* data;

        public:
            SQ():offset(0)//offset:arbitrary, might find better
                {data=new deque<T>(0);}
            SQ(int _size):offset(_size/2)//offset:arbitrary, might find better
                {data=new deque<T>(_size);}
            SQ(const SQ& x, int _size):offset(_size/2)//might end up using resize instead
                {
                data=new deque<T>(_size);
                for(int i=0;i<x.size();i++)
                    {access(i)=x.access(i);}
                }
            int getShiftedPos(int index)const
                {
                if(!data->size())
                    {cout<<"nonexistent data is read"<<endl;return 0;}
                 cout<<"getShiftedPos 0"<<endl;
                cout<<"index: "<<index<<" offset: "<<offset<<endl;
                cout<<"getShiftedPos 1"<<endl;
                int ShiftedPlace=index+offset;
                cout<<"getShiftedPos 2"<<endl;
                int actualPlace;
                cout<<"rawsize: "<<data->size()<<" offset: "<<offset<<endl;
                if(ShiftedPlace >= data->size())
                    {actualPlace=ShiftedPlace-data->size();}
                else
                    {actualPlace=ShiftedPlace;}
                cout<<" ShiftedPlace: "<<ShiftedPlace<<" actualPlace: "<<actualPlace<<" data->size(): "<<data->size()<<endl;
                cout<<"read data:"<<data->at(actualPlace)<<endl;
                return actualPlace;
                }
            T& access(int index)//random access
                {return data->at(getShiftedPos(index)) ;}

            void addTo(int index,const T&x)
                {
                cout<<"addTo called with :"<<index<<endl;
                data->insert(data->begin()+getShiftedPos(index),x) ;
                // cout<<"addto4"<<endl;
                if( getShiftedPos(index) < data->size())
                    {offset++;}
                offset%=data->size();
                cout<<"newState: offset: "<<offset<<" size "<<data->size()<<endl;
                }
            
            void deleteFrom(int index)
                {if(!data->size()){cout<<"DELETE FROM EMPTY"<<endl;;}
                int ShiftedPlace=index+offset;
                data->erase(data->begin()+(ShiftedPlace-( ShiftedPlace >= data->size() )*data->size())) ;
                cout<<"delmid"<<endl;
                if( ShiftedPlace < data->size())
                    {offset--;}
                if(data->size())
                    offset%=data->size();
                else
                    {offset=0;}
                }

            T placing(const T&x)//combied popfront,pushback
                {
                cout<<"plac1"<<endl;
                T temp=x;
                swapAround(&temp, &access(0));//temp holds the old value now
cout<<"plac2"<<endl;
                offset++;
                offset%=data->size();

                return temp;
                }
            
            T revplace(const T&x)//combied popback,pushfront
                {
                T temp=x;
                swapAround(&temp, &access(data->size()-1));//temp holds the old value now

                offset+=data->size()-1;//+=szie, and then decrement
                offset%=data->size();

                return temp;
                }

            void push_front(const T&x)
                {cout<<"push_front"<<endl;addTo(0,x);}

            void push_back(const T&x)
                {cout<<"push_back "<<endl;addTo(data->size(),x);}//-1
            
            T pop_back()
                {cout<<"pop_back "<<endl;T temp=access(data->size()-1);deleteFrom(data->size()-1);return temp;}

            T pop_front()
                {cout<<"pop_front "<<endl;T temp=access(0);deleteFrom(0);return temp;}

            ~SQ()
                {delete data;}
            //debug:
            void log()
                {
                cout<<"/////////////////////////////////"<<endl;
                cout<<" vectorsize: "<<data->size()<<" offset: "<<offset<<endl;
                cout<<"raw elements:"<<endl;
                for(int i=0;i<data->size();i++)
                    {cout<<(*data)[i]<<", ";}
                cout<<endl;
                cout<<"read elements:"<<endl;   
                for(int i=0;i<data->size();i++)
                    {cout<<access(i)<<", ";}
                cout<<endl<<"|///////////////////////////////|"<<endl;
                }
            void log(ofstream&x)
                {
                if(data->size())
                    {
                    x<<"/////////////////////////////////"<<endl;
                    x<<" vectorsize: "<<data->size()<<" offset: "<<offset<<endl;
                    x<<"raw elements:"<<endl;
                    for(int i=0;i<data->size();i++)
                        {x<<(*data)[i]<<", ";}
                    x<<endl;
                    x<<"read elements:"<<endl;   
                    for(int i=0;i<data->size();i++)
                        {x<<access(i)<<", ";}
                    x<<endl<<"|///////////////////////////////|"<<endl;
                    }
                }
        };
    
    //Testing utilities
    void neqWarn(float a,float b)
        {
        if(a!=b)
            cout<<a<<"!="<<b<<endl;
        }
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    void test(int meret)//test of validity, supposedly only prints on problems
            {
            srand((system_clock::now()).time_since_epoch().count());
            deque<float> comparee;
            comparee.resize(meret);
            SQ<float> alany(meret);
            for(int i=0;i<meret;i++)
                {
                alany.access(i)=i;
                comparee[i]=i;
                }
            for(int i=0;i<10000;i++)
                {
                int randomJob=rand();
                int randVal=randomJob%100;
                int hely=randomJob%meret;
                switch(randomJob%3)//syncronously do things to testsubject and comparee
                    {
                    case 0://write access
                        {
                        neqWarn( alany.access(hely) , comparee[hely] );
                        alany.access(hely)=randVal;
                        comparee    [hely]=randVal;
                        }break;
                    case 1://placing
                        {
                        float temp1=alany.placing(randVal);
                        float temp2=comparee.front();
                        comparee.pop_front();
                        comparee.push_back(randVal);
                        neqWarn( temp1 ,temp2 );
                        
                        }break;
                    case 2://revplace
                        {
                        float temp1=alany.revplace(randVal);
                        float temp2=comparee.back();
                        comparee.pop_back();
                        comparee.push_front(randVal);
                        neqWarn( temp1 ,temp2 );
                        }break;
                    
                    }
                
                }
            //alany.log();
            for(int i=0;i<meret;i++)
                {neqWarn(comparee[i],alany.access(i));}
            //cout<<endl<<"Testing done"<<endl;
            }
        
void test_speed(int meret,bool which)//test of validity, supposedly only prints on problems
            {
                deque<float> comparee;
                comparee.resize(meret);
                SQ<float> alany(meret);
            srand((system_clock::now()).time_since_epoch().count());
            
            
            for(int i=0;i<meret;i++)
                {
            if(which)
                {
                comparee[i]=i;
                }
            else
                {
                alany.access(i)=i;
                }
                
                
                }
            for(int i=0;i<10000;i++)
                {
                int randomJob=rand();
                int randVal=randomJob%100;
                int hely=randomJob%meret;
                switch(0)//syncronously do things to testsubject and comparee
                    {
                    case 0://write access
                        {
                        if(which)
                            {
                            comparee    [hely]=randVal;
                            }
                        else
                            {
                            alany.access(hely)=randVal;
                            }                                               
                        }break;
                    case 1://placing
                        {
                        if(which)
                            {
                            comparee.pop_front();
                            comparee.push_back(randVal);
                            }
                        else
                            {
                            alany.placing(randVal);
                            }
                        
                        }break;
                    case 2://revplace
                        {
                        if(which)
                            {
                            comparee.pop_back();
                            comparee.push_front(randVal);
                            }
                        else
                            {
                            alany.revplace(randVal);
                            }
                        }break;
                    
                    }
                
                }
            }

    void bigTest(int meret)//passed
        {
        cout<<"test started"<<endl;
        for(int i=1;i<meret;i++)
            {
            for(int j=0;j<100;j++)
                {test(i);}
            cout<<i<<", ";
            }
        cout<<endl<<"test done"<<endl;
        }
    }
#endif