#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char operation[10];

template <class T>
class priorityQueue
{
    private:
        int maxSize;
        T *array;
        int currentSize;
        void doubleSpace();
        void buildHeap();
        void precolateDown(int hole);
    public:
        priorityQueue(int capacity = 100);
        priorityQueue(const T data[], int size);
        ~priorityQueue();
        bool isEmpty() const;
        void enQueue(const T &x);
        T deQueue();
        T getHead() const;
};

template<class T>
void priorityQueue<T>::doubleSpace()
{
    T *tmp = array;
    maxSize *= 2;
    array = new T[maxSize];
    for(int i = 1; i <= currentSize; ++i)
    {
        array[i] = tmp[i];
    }
    delete [] tmp;
}

template<class T>
void priorityQueue<T>::buildHeap()
{
    for(int i = currentSize / 2; i > 0; --i)
    {
        precolateDown(i);
    }
}

template<class T>
void priorityQueue<T>::precolateDown(int hole)
{
    int child;
    T tmp = array[hole];
    for(; hole * 2 <= currentSize; hole = child)
    {
        child = hole * 2;
        if(child != currentSize && array[child+1] < array[child])
            child++;
        if(array[child] < tmp)
            array[hole] = array[child];
        else
            break;
    }
    array[hole] = tmp;
}

template<class T>
priorityQueue<T>::priorityQueue(int capacity)
{
    array = new T[capacity];
    maxSize = capacity;
    currentSize = 0;
}

template<class T>
priorityQueue<T>::priorityQueue(const T data[], int size)
{
    maxSize = size + 10;
    currentSize = size;
    array = new T[maxSize];
    for(int i = 0; i < size; ++i)
    {
        array[i+1] = data[i];
    }
    buildHeap();
}

template<class T>
priorityQueue<T>::~priorityQueue()
{
    delete [] array;
}

template<class T>
bool priorityQueue<T>::isEmpty() const
{
    return currentSize == 0;
}

template<class T>
T priorityQueue<T>::getHead() const
{
    return array[1];
}

template<class T>
void priorityQueue<T>::enQueue(const T &x)
{
    if(currentSize == maxSize - 1)
        doubleSpace();
    int hole = ++currentSize;
    for(; hole > 1 && x < array[hole/2]; hole /= 2)
    {
        array[hole] = array[hole/2];
    }
    array[hole] = x;
}

template<class T>
T priorityQueue<T>::deQueue()
{
    T tmp;
    tmp = array[1];
    array[1] = array[currentSize--];
    precolateDown(1);
    return tmp;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    priorityQueue<int> bt;
    int m, num;
    cin >> m;
    for(int i = 0; i < m; ++i)
    {
        cin >> operation;
        char op = operation[0];
        switch(op)
        {
            case 'i':
                cin >> num;
                bt.enQueue(num);
                break;
            case 'd':
                bt.deQueue();
                break;
            case 'm':
                cout << bt.getHead() << '\n';
        }
    }
    cout << flush;
    return 0;
}