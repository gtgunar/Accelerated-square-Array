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

            short int size;
            short int offset;
            vector<T>* data;

        public:

            SQ(int _size):size(_size),offset(_size/2)//offset:arbitrary, might find better
                {data=new vector<T>(_size);}
            SQ(const SQ& x, int _size):size(_size),offset(offset/2)//might end up using resize instead
                {
                data=new vector<T>(_size);
                for(int i=0;i<x.size();i++)
                    {access(i)=x.access(i);}
                }

            T& access(int index)//random access
                {
                int eltoltHely=index+offset;
                if( eltoltHely >= size )
                    {return data->at(eltoltHely  -size) ;}
                else
                    {return data->at(eltoltHely       ) ;}
                }
            
            T placing(T x)//combied popfront,pushback
                {
                T temp=x;
                swap(temp, access(0));//temp holds the old value now

                offset++;
                offset%=size;

                return temp;
                }
            
            T revplace(T x)//combied popfront,pushback
                {
                T temp=x;
                swap(temp, access(size-1));//temp holds the old value now

                offset+=size-1;
                offset%=size;

                return temp;
                }


            ~SQ(){delete data;}
            //debug:
            void log()
                {
                cout<<"/////////////////////////////////"<<endl;
                cout<<"storedSize: "<<size<<" vectorsize: "<<data->size()<<" offset: "<<offset<<endl;
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
    
    void neqWarn(float a,float b)
        {
        if(a!=b)
            cout<<a<<"!="<<b<<endl;
        }
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
        
    void bigTest(int meret)//passed
        {
        cout<<"test started"<<endl;
        for(int i=meret;meret;i--)
            {
            for(int j=0;j<100;j++)
                {test(i);}
            cout<<i<<", ";
            }
        cout<<endl<<"test done"<<endl;
        }
    }
#endif