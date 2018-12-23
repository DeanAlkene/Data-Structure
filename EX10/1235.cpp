#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 2e5+7;
const int INF = 1e9;
int n, m, start, finish;
int q[4 * MAXN], pre[MAXN];
bool known[MAXN];

struct vertex
{
    int idx, distance, edges;
    vertex(): distance(INF), edges(0) {}
    bool operator<(const vertex &right) const
    {
        return (distance < right.distance || (distance == right.distance && edges < right.edges));
    }
};
vertex dist[MAXN];

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
        void init(int s)
        {
            array[1].idx = s;
            array[s].idx = 1;
        }
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

void printPath(int s, int e)
{
    if(s == e)
    {
        cout << verList[s].idx;
        return;
    }
    printPath(s, pre[e]);
    cout << ' ' << verList[e].idx;
}

void Dijkstra(int s, int f)
{
    priorityQueue<vertex> pq(dist, n);
    memset(known, 0, sizeof(known));
    dist[s].distance = 0;
    pre[s] = s;
    pq.init(s);

    while(!pq.isEmpty())
    {
        vertex vt = pq.deQueue();
        if(!known[vt.idx])
        {
            int vid = vt.idx;
            known[vid] = true;
            edgeNode *tmp;
            for(tmp = verList[vid].head; tmp != NULL; tmp = tmp->next)
            {
                if(!known[tmp->idx] && 
                (dist[vid].distance + tmp->weight < dist[tmp->idx].distance ||
                (dist[vid].distance + tmp->weight == dist[tmp->idx].distance && 
                dist[vid].edges + 1 < dist[tmp->idx].distance)))
                {
                    vertex cur;
                    cur.distance = dist[vid].distance + tmp->weight;
                    cur.edges = dist[vid].edges + 1;
                    cur.idx = tmp->idx;
                    dist[tmp->idx] = cur;
                    pq.enQueue(cur);
                    pre[tmp->idx] = vid;
                }
            }
        }
        if(known[f])
            break;
    }
    cout << dist[f].distance << '\n';
    printPath(s, f);
}

void clear(int n)
{
    for(int i = 1; i <= n; ++i)
    {
        edgeNode *tmp, *cur;
        if(verList[i].head != NULL)
        {
            tmp = verList[i].head;
            cur = tmp->next;
            while(cur)
            {
                tmp = cur->next;
                delete cur;
                cur = tmp;
            }
            verList[i].head = NULL;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int u, v, w;
    cin >> n >> m >> start >> finish;
    for(int i = 1; i <= n; ++i)
    {
        verList[i].idx = i;
    }
    for(int i = 0; i < m; ++i)
    {
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }
    for(int i = 1; i <= n; ++i)
    {
        dist[i].idx = i;
    }
    Dijkstra(start, finish);
    clear(n);
    cout << flush;
    return 0;
}