#ifndef STATIONARY_QUEUE_H
#define STATIONARY_QUEUE_H

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
    deque<T> *data;


    public:
        SQ() // offset:arbitrary, might find better
        {
            data = new deque<T>(0);
        }
        SQ(int _size)  // offset:arbitrary, might find better
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


    };


#endif