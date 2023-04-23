#ifndef STATIONARY_QUEUE_H
#define STATIONARY_QUEUE_H
#include<vector>
#include<deque>//only for debugging
#include<iostream>//only for debugging
#include<cstdlib>//only for debugging
#include<chrono>//only for debugging

using namespace std;

namespace StationaryQueue
    {
    template<typename T>
    class SQ// stationary queue, with fix size, single memory access on combined en-/dequeue, both ways
        {
        private:

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
            T& access(int index)//random access
                {
                int ShiftedPlace=index+offset;
                return data->at(ShiftedPlace-( ShiftedPlace >= data->size() )*data->size()) ;
                }

            void addTo(const T&x,int index)
                {
                int ShiftedPlace=index+offset;
                data->insert(data->begin()+(ShiftedPlace-( ShiftedPlace >= data->size() )*data->size()),x) ;
                if( ShiftedPlace <= data->size())
                    {offset++;}
                }
            
            void deleteFrom(int index)
                {
                int ShiftedPlace=index+offset;
                data->erase(data->begin()+(ShiftedPlace-( ShiftedPlace >= data->size() )*data->size())) ;
                if( ShiftedPlace <= data->size())
                    {offset--;}
                }

            T placing(const T&x)//combied popfront,pushback
                {
                T temp=x;
                swap(temp, access(0));//temp holds the old value now

                offset++;
                offset%=data->size();

                return temp;
                }
            
            T revplace(const T&x)//combied popback,pushfront
                {
                T temp=x;
                swap(temp, access(data->size()-1));//temp holds the old value now

                offset+=data->size()-1;//+=szie, and then decrement
                offset%=data->size();

                return temp;
                }

            void push_front(const T&x)
                {addTo(x,0);}

            void push_back(const T&x)
                {addTo(x,data->size()-1);}
            
            T pop_back()
                {T temp=access(data->size()-1);deleteFrom(data->size()-1);return temp;}

            T pop_front()
                {T temp=access(0);deleteFrom(0);return temp;}

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
            srand((chrono::system_clock::now()).time_since_epoch().count());
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
            srand((chrono::system_clock::now()).time_since_epoch().count());
            
            
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