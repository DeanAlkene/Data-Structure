#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1e6+7;
int A[MAXN], B[MAXN];
void merge(int seq[], int left, int mid, int right);
void mergeSort(int seq[], int left, int right);

struct Node
{
    int data;
    int i;
    int j;
};
class minHeap
{
    private:
        int length;
        Node *array;
        int maxSize;

        void doubleSpace();
        void buildHeap();
        void precolateDown(int hole);
    public:
        minHeap(int capacity = 5000);
        ~minHeap();
        void enQueue(const Node &x);
        Node deQueue();
};

void minHeap::doubleSpace()
{
    Node *tmp = array;
    maxSize *= 2;
    array = new Node[maxSize];
    for(int i = 1; i <= length; ++i)
    {
        array[i] = tmp[i];
    }
    delete tmp;
}
void minHeap::precolateDown(int hole)
{
    int child;
    Node tmp = array[hole];
    for(; hole * 2 <= length; hole = child)
    {
        child = hole * 2;
        if(child != length && array[child + 1].data < array[child].data)
            child++;
        if(array[child].data < tmp.data)
            array[hole] = array[child];
        else  
            break;
    }
    array[hole] = tmp;
}
minHeap::minHeap(int capacity)
{
    array = new Node[capacity];
    maxSize = capacity;
    length = 0;
}
minHeap::~minHeap()
{
    delete [] array;
}
void minHeap::enQueue(const Node &x)
{
    if(length == maxSize - 1)
        doubleSpace();
    int hole = ++length;
    for(; hole > 1 && x.data < array[hole/2].data; hole /= 2)
    {
        array[hole] = array[hole/2];
    }
    array[hole] = x;
}
Node minHeap::deQueue()
{
    Node tmp;
    tmp = array[1];
    array[1] = array[length--];
    precolateDown(1);
    return tmp;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, k = 0;
    minHeap d;
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> A[i];
    }
    for(int i = 1; i <= n; ++i)
    {
        cin >> B[i];
    }
    mergeSort(A, 1, n);
    mergeSort(B, 1, n);
    Node in;
    for(int i = 1; i <= n; ++i)
    {
        in.data = A[1] + B[i];
        in.i = 1;
        in.j = i;
        d.enQueue(in);
    }
    for(int i = 1; i <= n; ++i)
    {
        Node tmp;
        tmp = d.deQueue();
        cout << tmp.data << ' ';
        if(tmp.i + 1 <= n && tmp.j <= n)
        {
            in.data = A[tmp.i + 1] + B[tmp.j];
            in.i = tmp.i + 1;
            in.j = tmp.j;
            d.enQueue(in);
        }
    }
    cout << '\n';
    cout << flush;
    return 0;
}

void mergeSort(int seq[], int left, int right)
{
    if(left == right) return;
    int mid = (left + right) / 2;
    mergeSort(seq, left, mid);
    mergeSort(seq, mid + 1, right);
    merge(seq, left, mid, right);
}
 
void merge(int seq[], int left, int mid, int right)
{
    int len = right - left + 1;
    int i = left, j = mid + 1, k = 0;
    int *tmp = new int[len];
    while(i <= mid && j <= right)
    {
        if(seq[i] <= seq[j])
            tmp[k++] = seq[i++];
        else
        {
            tmp[k++] = seq[j++];
        }
    }
    while(i <= mid)
    {
        tmp[k++] = seq[i++];
    }
    while(j <= right)
    {
        tmp[k++] = seq[j++];
    }
 
    for(i = 0, k = left; k <= right; )
    {
        seq[k++] = tmp[i++];
    }
    delete tmp;
}