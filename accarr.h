//Márton Attila, 2023
/*TODO:

cleanup memory leak in delete(free on the fly, the unused memory)      
have std error         
implement std interface(iterator and operators)                
    [] done
    move constructor(including with other storage)
    copy constructor(including with other storage)
    .begin
    .end
    ==
    iterator==
    iterator++
///cleanup:
delete public-all
delete non-explanatry comments
clean main
///
teszt performance with compilation
    caching
    avoiding redundant branches, branchless code
    
//////////////////////////////////////////////
*/
#ifndef ACCARR_H
#define ACCARR_H
#include<vector>
#include<cmath>
#include<deque>
using namespace std;

template<typename T>
T popoff(deque<T>* x)
    {
    T toreturn=((*x)[max(0,(int)x->size()-1)]);
    x->pop_back();
    return toreturn;
    }
template<typename T>
T popoff_front(deque<T>* x)
    {
    T toreturn=(*x)[0];
    x->pop_front();
    return toreturn;
    }
template<typename T>//depth=2
class accarr
    {
    public://TODO delete debug-public
    deque<deque<T>*> content;

    int population;//actual population
    int popsqrt()const{return sqrt(population);}//floor(sqrt(population)) <=> sqrt(popsn)
    int popsn()const{return popsqrt()*popsqrt();}//population's lower neighbour sqruare number
    int popp()const{return population-popsn();}//current value of extra population, population-popsn
    bool endLoad()const{return popp() < popsqrt();}//is the end the loadingplace
    int incCount()const{return popp()-popsqrt();}

    int getHotplace(bool delMode=false)const{//where next insert/delete shall go
            if(delMode)
                {
                //cout<<"CURRENT POP:"<<population<<endl;
                if(popp()!=0)
                    {
                    if(popp() <= popsqrt())//endLoad-1
                        {return popsqrt();}
                    else// if(popp() > popsqrt())//redundant
                        {return incCount()-1;}
                    }
                else
                    {return popsqrt()-1;}
                }
            else
                {
                if(endLoad())
                    {return (popsqrt());}
                else
                    {return incCount();}
                }
        }

    void balanceShift(int newat,bool reverse=false){/////////////////////////////////////////////

        if(reverse)//reverse is for delete
            {
            if(newat<getHotplace(true))//erased before hotplace,carry from hotplace to erasementpoint
                {
                T temp=popoff_front(content[getHotplace(true)]);
                for(int i=getHotplace(true)-1;i>newat;i--)
                    {
                    content[i]->push_back(temp);
                    temp=popoff_front(content[i]);
                    }
                content[newat]->push_back(temp);
                }
            else if(newat>getHotplace(true))
                {
                T temp=popoff(content[getHotplace(true)]);
                
                for(int i=getHotplace(true)+1;i<newat;i++)
                    {
                    content[i]->push_front(temp);
                    temp=popoff(content[i]);
                    }
                content[newat]->push_front(temp);
                }    
            else{/*cout<<"delete lucky;"<<endl;*/}
            }
        else
            {
            if(newat<getHotplace())//
                {
                T temp=popoff(content[newat]);
                for(int i=newat+1;i<getHotplace();i++)
                    {
                    content[i]->push_front(temp);
                    temp=popoff(content[i]);
                    }
                content[getHotplace()]->push_front(temp);
                }
            else if(newat>getHotplace())
                {
                T temp=popoff_front(content[newat]);
                for(int i=newat-1;i>getHotplace();i--)
                    {
                    content[i]->push_back(temp);
                    temp=popoff_front(content[i]);
                    }
                content[getHotplace()]->push_back(temp);
                }
            else{/*cout<<"add lucky;"<<endl;*/}
            }
        }//hotplace could be calced
    pair<int,int>getRelPos(int index)const//the pair of block-index and the within block index for a given index value
        {
        if(population==0){return pair<int,int>(0,0);}
        int whichTo,whereTo;
        if(endLoad())
            {
            //cout<<"getRelPos:branch1   ";
            whichTo=index / popsqrt();
            whereTo=index % popsqrt();
            }
        else
            {
            //int unInced=popsqrt()*(popsqrt()-incCount());//////////////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!4
            if(index /(popsqrt()+1) >incCount())//
                {
                int rempart=index-incCount()*(popsqrt()+1);//part stored in the unincremented remainder
                whichTo=incCount()+rempart/popsqrt();
                whereTo= rempart % popsqrt();
                //cout<<"    getRelPos:branch2   ";
                }
            else//case is within sqrt+1 blocks, no mixed lengths
                {
                whichTo=index / (popsqrt()+1);
                whereTo=index % (popsqrt()+1);
                //cout<<"    getRelPos:branch3   ";
                }
            }
        //cout<<"   on population:"<<population<<" index "<<index<<" got: "<< whichTo<<"/" <<whereTo<<"   ";
        return pair<int,int>(whichTo,whereTo);
        }
    public:
    accarr():population(0){content.push_back(new deque<T>());content.push_back(new deque<T>());content.push_back(new deque<T>());}//creates empty instance
    void insert(int index,const T& value)//insert value to index(by becoming the new value at that position)
        { 
        if(index<0||index>population){cout<<"wrong range"<<endl;}//todo:error and popentil fixes
        if(content.size()-2<popsqrt()){content.push_back(new deque<int>());}  
        (content[getRelPos(index).first])->insert(content[getRelPos(index).first]->begin()+getRelPos(index).second,value);
        //!SWAPPED LAST 2
        
        balanceShift(getRelPos(index).first);
        population++;
        }
    T getAt(int index)const//return value at index
        {return (*content[getRelPos(index).first])[getRelPos(index).second];}    
    T& refAt(int index)const//return value at index
        {return (*content[getRelPos(index).first])[getRelPos(index).second];}    
    T& operator[](int index)
        {return refAt(index);}
    void setAt(int index, const T& value)const//overwrite at index, with value
        {(*content[getRelPos(index).first])[getRelPos(index).second]=value;}    

    void erase(int index)//erase at index
        {   
        (content[getRelPos(index).first])->erase
            (content[getRelPos(index).first]->begin()+getRelPos(index).second);
        //!SWAPPED LAST 2
        
        balanceShift(getRelPos(index).first,true);
        population--; 
        }

    void logContent()const{
        for(auto i : content)
            {
            cout<<"######################"<<endl;
            cout<<i<<":"<<i->size()<<endl;
            for(auto j:(*i)){cout<<j<<",\t";}
            cout<<endl<<"//////////////"<<endl;
            }
    cout<<endl<<endl<<endl;
    }
    ~accarr(){for(auto i:content)delete i;}//destroys and frees intance memory
    };


#endif