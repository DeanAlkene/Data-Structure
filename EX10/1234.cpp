#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1e4+7;
int n, m;

struct edge
{
    int s, e, w;
    bool operator<(const edge &right) const {return w < right.w;}
};

struct edgeNode
{
    int idx;
    int weight;
    edgeNode *next;
    edgeNode(int i, int w, edgeNode *n): idx(i), weight(w), next(n) {}
};

struct verNode
{
    int idx;
    edgeNode *head;
    verNode(int i = 0, edgeNode *h = NULL): idx(i), head(h) {}
};
verNode verList[MAXN];

void addEdge(int u, int v, int w)
{
    verList[u].head = new edgeNode(v, w, verList[u].head);
}

class DisjointSet
{
    private:
        int size;
        int *parent;
    public:
        DisjointSet(int n);
        ~DisjointSet() {delete [] parent;}
        void Union(int root1, int root2);
        int Find(int x);
};
DisjointSet::DisjointSet(int n)
{
    size = n;
    parent = new int[size];
    for(int i = 0; i < size; ++i)
        parent[i] = -1;
}
void DisjointSet::Union(int root1, int root2)
{
    if(root1 == root2)
        return;
    if(parent[root1] > parent[root2])
    {
        parent[root2] += parent[root1];
        parent[root1] = root2;
    }
    else
    {
        parent[root1] += parent[root2];
        parent[root2] = root1;
    }
}

int DisjointSet::Find(int x)
{
    if(parent[x] < 0) return x;
    return parent[x] = Find(parent[x]);
}

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

long long Kruskal()
{
    int edgesAccepted = 0, u, v;
    long long cnt = 0;
    edgeNode *tmp;
    edge ed;
    DisjointSet ds(n+1);
    priorityQueue<edge> pq;
    for(int i = 1; i <= n; ++i)
    {
        for(tmp = verList[i].head; tmp != NULL; tmp = tmp->next)
        {
            if(i < tmp->idx)
            {
                ed.s = i;
                ed.e = tmp->idx;
                ed.w = tmp->weight;
                pq.enQueue(ed);
            }

        }
    }

    while(edgesAccepted < n - 1)
    {
        ed = pq.deQueue();
        u = ds.Find(ed.s);
        v = ds.Find(ed.e);
        if(u != v)
        {
            edgesAccepted++;
            ds.Union(u, v);
            cnt += ed.w;
        }
    }
    return cnt;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int u, v, w;
    cin >> n >> m;
    for(int i = 0; i < m; ++i)
    {
        cin >> u >> v >> w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    long long ans = Kruskal();
    cout << ans << '\n';
    cout << flush;
    return 0;
}