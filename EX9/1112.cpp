#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1007;
int n, k, level[MAXN], known[MAXN];
bool inQueue[MAXN], relation[MAXN][MAXN];

struct Node
{
    int index;
    int level;
    Node(int idx = 0, int l = 0) : index(idx), level(l) {}
    friend bool operator>(const Node &a, const Node &b) {return a.level > b.level;}
};

class Heap
{
  private:
    Node *array;
    int sz;
    int maxSize;

  public:
    Heap(int initSize = 101)
    {
        array = new Node[initSize];
        sz = 0;
        maxSize = initSize;
    }
    Node deQueue()
    {
        Node tmp = array[1];
        array[1] = array[sz--];
        precolateDown(1);
        return tmp;
    }
    void enQueue(Node x)
    {
        if (sz == maxSize - 1)
            doubleSpace();
        int hole = ++sz;
        for (; hole > 1 && x > array[hole / 2]; hole /= 2)
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
        Node tmp = array[hole];
        for (; 2 * hole <= sz; hole = child)
        {
            child = 2 * hole;
            if (child != sz && array[child + 1] > array[child])
                child++;
            if (array[child] > tmp)
                array[hole] = array[child];
            else
                break;
        }
        array[hole] = tmp;
    }
    Node getHead()
    {
        return array[1];
    }
    bool isEmpty()
    {
        return sz == 0;
    }
    void doubleSpace()
    {
        Node *tmp = array;
        maxSize *= 2;
        array = new Node[maxSize];
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

    memset(inQueue, 0,sizeof(inQueue));
    int tmp;
    cin >> n >> k;
    Heap h(n);
    for(int i = 1; i <= n; ++i)
        cin >> level[i];
    for(int i = 1; i <= k; ++i)
    {
        cin >> tmp;
        h.enQueue(Node(tmp, level[tmp]));
        inQueue[tmp] = true;
    }
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            cin >> relation[i][j];
    
    while(!h.isEmpty())
    {
        int idx = h.deQueue().index;
        cout << idx << '\n';
        for(int i = 1; i <= n; ++i)
        {
            if(relation[idx][i] == 1 && inQueue[i] == false)
            {
                h.enQueue(Node(i, level[i]));
                inQueue[i] = true;
            }
        }
    }
    cout << flush;
    return 0;
}