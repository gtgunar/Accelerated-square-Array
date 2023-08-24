#ifndef STATIONARY_QUEUE_H
#define STATIONARY_QUEUE_H
#include <vector>
#include <deque>    //only for debugging
#include <iostream> //only for debugging
#include <cstdlib>  //only for debugging
#include <chrono>   //only for debugging
#include <fstream>  //only for debugging
using std::cout;
using std::deque;
using std::endl;
using std::ofstream;
using std::vector;
using namespace std::chrono;

namespace StationaryQueue
{
    template <typename T>
    void swapAround(T *a, T *b)
    {
        T temp = *a;
        *a = *b;
        *b = temp;
    }
    template <typename T>
    class SQ
    {
    private:
    public:
        short int offset;
        deque<T> *data;
        void offsetmove(bool back = false)
        {
            offset += back ? -1 : 1;
            offset %= data->size() > 1 ? data->size() - 1 : 1;
        }

    public:
        SQ() : offset(0) // offset:arbitrary, might find better
        {
            data = new deque<T>(0);
        }
        SQ(int _size) : offset(_size / 2) // offset:arbitrary, might find better
        {
            data = new deque<T>(_size);
        }

        T &access(int index) // random access
        {
            return data->at(index);
        }

        T &access(int index) const // random access
        {
            return data->at(index);
        }

        void addTo(int index, const T &x)
        {
            data->insert(data->begin() + index, x);
        }

        void deleteFrom(int index)
        {
            data->erase(data->begin() + index);
        }

        T placing(const T &x) // popfront+pushback
        {
            push_back(x);
            return pop_front();
        }

        T revplace(const T &x)
        {
            push_front(x);
            return pop_back();
        }

        void push_front(const T &x) { addTo(0, x); }
        void push_back(const T &x) { addTo(data->size(), x); }

        T pop_back()
        {
            T temp = access(data->size() - 1);
            deleteFrom(data->size() - 1);
            return temp;
        }
        T pop_front()
        {
            T temp = access(0);
            deleteFrom(0);
            return temp;
        }

        ~SQ() { delete data; }

        void log() const
        {
            cout << "//////////////.-.-/////////----//////////" << endl;
            cout << " vectorsize: " << data->size() << " offset: " << offset << endl;
            cout << "raw elements:" << endl;
            for (int i = 0; i < data->size(); i++)
            {
                cout << (*data)[i] << ", ";
            }
            cout << endl;
            cout << "read elements:" << endl;
            for (int i = 0; i < data->size(); i++)
            {
                cout << access(i) << ", ";
            }
            cout << endl
                 << "|//////////////.-.-.////---/////////////|" << endl;
        }
        void log(ofstream &x)
        {
            if (data->size())
            {
                x << "////////////////////.-.-////--/////////" << endl;
                x << " vectorsize: " << data->size() << " offset: " << offset << endl;
                x << "raw elements:" << endl;
                for (int i = 0; i < data->size(); i++)
                {
                    x << (*data)[i] << ", ";
                }
                x << endl;
                x << "read elements:" << endl;
                for (int i = 0; i < data->size(); i++)
                {
                    x << "access attempt at " << i << access(i) << ", ";
                }
                x << endl
                  << "|////////////.-.///////-////////////|" << endl;
            }
        }
    };
}

#endif