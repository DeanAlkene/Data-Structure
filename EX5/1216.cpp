#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN = 1e5;
const int INF = 1e9;
char operation[10];
int q[MAXN];

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
        int find(const T &x);
        void decrease(int i, int v);
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
    for(int i = currentSize / 2; i > 0; ++i)
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

template<class T>
int priorityQueue<T>::find(const T &x)
{
    int head = 0, tail = 0, minElem = INF, index, left, right, i;
    if(x < array[1])
        return 1;
    q[++tail] = 1;
    while(head != tail)
    {
        index = q[++head];
        if(2 * index <= currentSize)
        {
            left = 2 * index;
            
            if(array[left] <= x)
                q[++tail] = left;
            else
            {
                if(array[left] < minElem)
                {
                    minElem = array[left];
                    i = left;
                }   
            }

            if(left != currentSize)
            {
                right = 2 * index + 1;
                if(array[right] <= x)
                    q[++tail] = right;
                else
                {
                    if(array[right] < minElem)
                    {
                        minElem = array[right];
                        i = right;
                    }   
                }
            }
                
        }
    }
    return i;
}

template<class T>
void priorityQueue<T>::decrease(int i, int v)
{
    int hole = i;
    T tmp = array[i] - v;
    for(; hole > 1 && tmp < array[hole/2]; hole /= 2)
    {
        array[hole] = array[hole/2];
    }
    array[hole] = tmp;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    priorityQueue<int> bt;
    int m, a, b;
    cin >> m;
    for(int i = 0; i < m; ++i)
    {
        cin >> operation;
        char op = operation[0];
        switch(op)
        {
            case 'i':
                cin >> a;
                bt.enQueue(a);
                break;
            case 'f':
                cin >> a;
                cout << bt.find(a) << '\n';
                break;
            case 'd':
                cin >> a >> b;
                bt.decrease(a, b);
                break;
        }
    }
    cout << flush;
    return 0;
}