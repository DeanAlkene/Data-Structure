#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1e5 + 7;
bool __greater(int a, int b) { return a > b; }
bool __less(int a, int b) { return a < b; }
class Heap
{
  private:
    int array[MAXN];
    bool (*op)(int, int);
    int sz;

  public:
    Heap(bool (*fun)(int, int))
    {
        op = fun;
        sz = 0;
    }
    int deQueue()
    {
        int tmp = array[1];
        array[1] = array[sz--];
        precolateDown(1);
        return tmp;
    }
    void enQueue(int x)
    {
        int hole = ++sz;
        for (; hole > 1 && op(x, array[hole / 2]); hole /= 2)
        {
            array[hole] = array[hole / 2];
        }
        array[hole] = x;
    }
    int getSize()
    {
        return sz;
    }
    void precolateDown(int hole)
    {
        int child;
        int tmp = array[hole];
        for (; 2 * hole <= sz; hole = child)
        {
            child = 2 * hole;
            if (child != sz && op(array[child + 1], array[child]))
                child++;
            if (op(array[child], tmp))
                array[hole] = array[child];
            else
                break;
        }
        array[hole] = tmp;
    }
    int getHead()
    {
        return array[1];
    }
    bool isEmpty()
    {
        return sz == 0;
    }
};

void add(int x, Heap &maxHeap, Heap &minHeap)
{
    if (maxHeap.isEmpty())
    {
        maxHeap.enQueue(x);
        return;
    }
    if (x > maxHeap.getHead())
        minHeap.enQueue(x);
    else
        maxHeap.enQueue(x);
    if (minHeap.getSize() - maxHeap.getSize() > 1)
        maxHeap.enQueue(minHeap.deQueue());
    else
    {
        if (maxHeap.getSize() - minHeap.getSize() > 1)
            minHeap.enQueue(maxHeap.deQueue());
    }
}

int getMid(Heap &maxHeap, Heap &minHeap)
{
    if (minHeap.getSize() != maxHeap.getSize())
        return maxHeap.getSize() < minHeap.getSize() ? minHeap.getHead() : maxHeap.getHead();
    else
        return maxHeap.getHead();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, tmp;
    Heap maxHeap(__greater);
    Heap minHeap(__less);
    cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        cin >> tmp;
        add(tmp, maxHeap, minHeap);
        if (i % 2)
            cout << getMid(maxHeap, minHeap) << ' ';
    }
    cout << '\n';
    cout << flush;
    return 0;
}