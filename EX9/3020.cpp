#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int n, m;

class Heap
{
  private:
    long long *array;
    int sz;
    int maxSize;

  public:
    Heap(int initSize = 101)
    {
        array = new long long[initSize];
        sz = 0;
        maxSize = initSize;
    }
    long long deQueue()
    {
        long long tmp = array[1];
        array[1] = array[sz--];
        precolateDown(1);
        return tmp;
    }
    void enQueue(long long x)
    {
        if (sz == maxSize - 1)
            doubleSpace();
        int hole = ++sz;
        for (; hole > 1 && x < array[hole / 2]; hole /= 2)
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
        long long tmp = array[hole];
        for (; 2 * hole <= sz; hole = child)
        {
            child = 2 * hole;
            if (child != sz && array[child + 1] < array[child])
                child++;
            if (array[child] < tmp)
                array[hole] = array[child];
            else
                break;
        }
        array[hole] = tmp;
    }
    long long getHead()
    {
        return array[1];
    }
    bool isEmpty()
    {
        return sz == 0;
    }
    void doubleSpace()
    {
        long long *tmp = array;
        maxSize *= 2;
        array = new long long[maxSize];
        for (int i = 1; i <= sz; ++i)
        {
            array[i] = tmp[i];
        }
        delete[] tmp;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    Heap h(n);
    long long tmp, ans = 0;
    for(int i = 0; i < n; ++i)
    {
        cin >> tmp;
        h.enQueue(tmp);
    }
    while(m > 2 && n % (m - 1) != 1) //each merge k-1 nodes disappeared, one node last in the end, so k % (m-1) == 1
    {
        h.enQueue(0);
        n++;
    }
    while(h.getSize() != 1)
    {
        tmp = 0;
        for(int i = 0; i < m; ++i)
        {
            tmp += h.deQueue();
        }
        ans += tmp;
        h.enQueue(tmp);
    }
    cout << ans << '\n';
    cout << flush;
    return 0;
}