#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;
const int MAXN = 1e5 + 7;
const int MAXNN = 1e6 + 7;
long long int song[MAXN], boyList[MAXNN], girlList[MAXNN];

void merge(long long int A[], int left, int mid, int right);
void mergeSort(long long int A[], int left, int right);

template <class T>
class seqQueue
{
    private:
        T *data;
        int maxSize;
        int front, rear;
        void doubleSpace();
    public:
        seqQueue(int size = 1000007);
        ~seqQueue();
        bool isEmpty() const;
        void enQueue(const T &x);
        T deQueue();
        T getHead() const;
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
}

template <class T>
T seqQueue<T>::deQueue()
{
    front = (front + 1) % maxSize;
    return data[front];
}

template <class T>
T seqQueue<T>::getHead() const
{
    return data[(front + 1) % maxSize];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    long long int n, m, gender, arrTime, timer = 0, boyNum = 0, girlNum = 0, songNum = 0;
    double boyWT = 0, girlWT = 0;
    seqQueue<long long int> boy, girl;
    cin >> n;
    for(long long int i = 0; i < n; ++i)
    {
        cin >> song[i];
    }
    cin >> m;
    for(long long int i = 0; i < m; ++i)
    {
        cin >> gender >> arrTime;
        if(gender == 1)
        {
            boyList[boyNum] = arrTime;
            boyNum++;

        }
        else
        {
            girlList[girlNum] = arrTime;
            girlNum++;
        }
    }

    mergeSort(boyList, 0, boyNum - 1);
    mergeSort(girlList, 0, girlNum - 1);

    for(int i = 0; i < boyNum; ++i)
    {
        boy.enQueue(boyList[i]);
    }
    for(int i = 0; i < girlNum; ++i)
    {
        girl.enQueue(girlList[i]);
    }

    for(; songNum < n; timer += song[songNum++])//...
    {
        while((!boy.isEmpty() && !girl.isEmpty()) && boy.getHead() <= timer && girl.getHead() <= timer)
        {
            boyWT += timer - boy.deQueue();
            girlWT += timer - girl.deQueue();
        }
    }

    while(!boy.isEmpty() && boy.getHead() <= timer)
    {
        boyWT += timer - song[songNum - 1] - boy.deQueue(); //LAST SONG
    }

    while(!girl.isEmpty() && girl.getHead() <= timer)
    {
        girlWT += timer - song[songNum - 1] - girl.deQueue();
    }

    cout << setprecision(2) << fixed << boyWT / boyNum << ' ' << setprecision(2) << fixed << girlWT / girlNum << '\n';
    cout << flush;
    return 0;
}

void mergeSort(long long int A[], int left, int right)
{
    if(left == right) return;
    int mid = (left + right) / 2;
    mergeSort(A, left, mid);
    mergeSort(A, mid + 1, right);
    merge(A, left, mid, right);
}

void merge(long long int A[], int left, int mid, int right)
{
    int len = right - left + 1;
    int i = left, j = mid + 1, k = 0;
    long long int *tmp = new long long int[len];
    while(i <= mid && j <= right)
    {
        if(A[i] <= A[j])
            tmp[k++] = A[i++];
        else
        {
            tmp[k++] = A[j++];
        }
    }
    while(i <= mid)
    {
        tmp[k++] = A[i++];
    }
    while(j <= right)
    {
        tmp[k++] = A[j++];
    }

    for(i = 0, k = left; k <= right; )
    {
        A[k++] = tmp[i++];
    }
    delete tmp;
}