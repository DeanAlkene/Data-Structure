#include <iostream>
#include <cstdio>
#include <cstring>
#define MAXN 1000
#define INF 10000000
using namespace std;

//HDUOJ 2612 CHANGED
int maze[MAXN][MAXN], visit[MAXN][MAXN], go[MAXN][MAXN], back[MAXN][MAXN];

struct Point
{
    int x;
    int y;
    int step;
};

template <class T>
class seqQueue
{
    private:
        T *data;
        int maxSize;
        int front, rear;
        int length;
        void doubleSpace();
    public:
        seqQueue(int size = 1000);
        ~seqQueue();
        bool isEmpty() const;
        void enQueue(const T &x);
        T deQueue();
        T getHead() const;
        int getLength() {return length;}
};

template <class T>
void seqQueue<T>::doubleSpace()
{
    T* tmp = data;
    data = new T[2 * maxSize];
    for(int i = 1; i < maxSize; ++i)
    {
        data[i] = tmp[(front + i) % maxSize];
    }
    front = 0;
    rear = maxSize - 1;
    maxSize *= 2;
    delete tmp;
}

template <class T>
seqQueue<T>::seqQueue(int size)
{
    data = new T[size];
    maxSize = size;
    front = rear = 0;
    length = 0;
}

template <class T>
seqQueue<T>::~seqQueue()
{
    delete [] data;
}

template <class T>
bool seqQueue<T>::isEmpty() const
{
    return front == rear;
}

template <class T>
void seqQueue<T>::enQueue(const T &x)
{
    if((rear + 1) % maxSize == front)
        doubleSpace();
    rear = (rear + 1) % maxSize;
    data[rear] = x;
    length++;
}

template <class T>
T seqQueue<T>::deQueue()
{
    front = (front + 1) % maxSize;
    return data[front];
    length--;
}

template <class T>
T seqQueue<T>::getHead() const
{
    return data[(front + 1) % maxSize];
}

bool check(int x, int y, int m, int n)
{
    if(x >= 0 && y >= 0 && x < m && y < n && maze[x][y] != 1 && visit[x][y] == 0)
        return true;
    return false;
}

int findShortest(Point start, int mark[][MAXN], int m, int n)
{
    int move_x[4] = {1,0,-1,0}, move_y[4] = {0,1,0,-1};
    Point s, e;
    seqQueue<Point> path;
    s.x = start.x;
    s.y = start.y;
    s.step = 0;
    path.enQueue(s);
    while(!path.isEmpty())
    {
        s = path.deQueue();
        for(int i = 0; i < 4; ++i)
        {
            e.x = s.x + move_x[i];
            e.y = s.y + move_y[i];
            if(!check(e.x, e.y, m, n))
                continue;
            e.step = s.step + 1;
            visit[e.x][e.y] = 1;
            if(maze[e.x][e.y] == 4)
            {
                mark[e.x][e.y] = e.step;
            }
            path.enQueue(e);
        }
    }
}
int main()
{
    int m, n;
    Point pos, home;
    scanf("%d %d", &n, &m);
    memset(visit, 0, sizeof(visit));
    memset(go, 0, sizeof(go));
    memset(back, 0, sizeof(back));
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            scanf("%d", &maze[i][j]);
            if(maze[i][j] == 2)
            {
                pos.x = i;
                pos.y = j;
            }
            if(maze[i][j] == 3)
            {
                home.x = i;
                home.y = j;
            }
        }
    }
    visit[pos.x][pos.y] = 1;
    findShortest(pos, go, m, n);

    memset(visit, 0, sizeof(visit));
    visit[home.x][home.y] = 1;
    findShortest(home, back, m, n);

    int minDist = INF;
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(minDist > go[i][j] + back[i][j] && go[i][j] && back[i][j])
                minDist = go[i][j] + back[i][j];
        }
    }
    printf("%d", minDist);
    printf("\n");
    return 0;
}