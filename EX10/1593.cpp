#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1e5+7;
struct Mouse
{
    int idx;
    int mark;
    int strength;
    friend bool operator>(const Mouse &a, const Mouse &b)
    {
        if(a.mark > b.mark)
            return true;
        else
        {
            if(a.mark == b.mark)
            {
                return a.idx < b.idx;
            }
            else
                return false;
        }
    }
};
Mouse in[2 * MAXN];
class priorityQueue
{
    private:
        int maxSize;
        Mouse *array;
        int currentSize;
        void doubleSpace();
        void buildHeap();
        void precolateDown(int hole);
    public:
        priorityQueue(int capacity = 100);
        priorityQueue(const Mouse data[], int size);
        ~priorityQueue();
        bool isEmpty() const;
        void enQueue(const Mouse &x);
        Mouse deQueue();
        Mouse getHead() const;
};

void priorityQueue::doubleSpace()
{
    Mouse *tmp = array;
    maxSize *= 2;
    array = new Mouse[maxSize];
    for(int i = 1; i <= currentSize; ++i)
    {
        array[i] = tmp[i];
    }
    delete [] tmp;
}

void priorityQueue::precolateDown(int hole)
{
    int child;
    Mouse tmp = array[hole];
    for(; hole * 2 <= currentSize; hole = child)
    {
        child = hole * 2;
        if(child != currentSize && array[child+1] > array[child])
            child++;
        if(array[child] > tmp)
            array[hole] = array[child];
        else
            break;
    }
    array[hole] = tmp;
}

void priorityQueue::buildHeap()
{
    for(int i = currentSize / 2; i > 0; --i)
    {
        precolateDown(i);
    }
}

priorityQueue::priorityQueue(const Mouse data[], int size)
{
    maxSize = size + 10;
    currentSize = size;
    array = new Mouse[maxSize];
    for(int i = 0; i < size; ++i)
    {
        array[i+1] = data[i];
    }
    buildHeap();
}

priorityQueue::priorityQueue(int capacity)
{
    array = new Mouse[capacity];
    maxSize = capacity;
    currentSize = 0;
}

priorityQueue::~priorityQueue()
{
    delete [] array;
}


bool priorityQueue::isEmpty() const
{
    return currentSize == 0;
}


Mouse priorityQueue::getHead() const
{
    return array[1];
}


void priorityQueue::enQueue(const Mouse &x)
{
    if(currentSize == maxSize - 1)
        doubleSpace();
    int hole = ++currentSize;
    for(; hole > 1 && x > array[hole/2]; hole /= 2)
    {
        array[hole] = array[hole/2];
    }
    array[hole] = x;
}


Mouse priorityQueue::deQueue()
{
    Mouse tmp;
    tmp = array[1];
    array[1] = array[currentSize--];
    precolateDown(1);
    return tmp;
}

void bubbleUp(int num)
{
    if(num == 0 || in[num-1] > in[num])
        return;
    Mouse tmp = in[num];
    while(num > 0 && tmp > in[num-1])
    {
        in[num] = in[num-1];
        --num;
    }
    in[num] = tmp;
}

void compete(int num1, int num2)
{
    Mouse &a = in[num1], &b = in[num2];
    if(a.strength > b.strength)
    {
        a.mark += 2;
        bubbleUp(num1);
    }
    else
    {
        if(a.strength == b.strength)
        {
            a.mark += 1;
            bubbleUp(num1);
            b.mark += 1;
            bubbleUp(num2);
        }
        else
        {
            b.mark += 2;
            bubbleUp(num2);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, r, p, s;
    cin >> n >> r;

    for(int i = 0; i < 2 * n; ++i)
    {
        cin >> p;
        in[i].mark = p;
        in[i].idx = i+1;
    }
    for(int i = 0; i < 2 * n; ++i)
    {
        cin >> s;
        in[i].strength = s;
    }
    priorityQueue h1(in, 2 * n);
    int last = 0;
    while(!h1.isEmpty())
    {
        in[last++] = h1.deQueue();
    }
    for(int i = 0; i < r; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            compete(2*j, 2*j+1);
        }
    }
    for(int i = 0; i < 2 * n; ++i)
    {
        cout << in[i].idx << ' ';
    }
    cout << '\n';
    cout << flush;
    return 0;
}
