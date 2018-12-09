#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1e5 + 7;
int a[MAXN], tmp[MAXN], heap[MAXN];
int sum;
inline void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void merge(int s[], int left, int mid, int right)
{
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right)
    {
        if (s[i] <= s[j])
            tmp[k++] = s[i++];
        else
            tmp[k++] = s[j++];
        ++sum;
    }
    while (i <= mid)
        tmp[k++] = s[i++];
    while (j <= right)
        tmp[k++] = s[j++];
    for (i = 0, k = left; k <= right;)
        s[k++] = tmp[i++];
}

void mergeSort(int s[], int left, int right)
{
    int mid = (left + right) / 2;
    if ((right - left + 1) & 1)
        --mid;
    if (left == right)
        return;
    mergeSort(s, left, mid);
    mergeSort(s, mid + 1, right);
    merge(s, left, mid, right);
}

int divide(int s[], int low, int high)
{
    int k = s[low];
    do
    {
        while (low < high && s[high] >= k)
            --high, ++sum;
        if (low < high)
        {
            s[low] = s[high];
            ++low;
        }
        while (low < high && s[low] <= k)
            ++low, ++sum;
        if (low < high)
        {
            s[high] = s[low];
            --high;
        }
    } while (low != high);
    s[low] = k;
    return low;
}

void quickSort(int s[], int low, int high)
{
    int mid;
    if (low >= high)
        return;
    mid = divide(s, low, high);
    quickSort(s, low, mid);
    quickSort(s, mid + 1, high);
}

void precolateDown(int s[], int hole, int size)
{
    int child, tmp = s[hole];
    for (; 2 * hole + 1 < size; hole = child)
    {
        child = 2 * hole + 1;
        if (child != size - 1 && s[child + 1] < s[child])
        {
            ++sum;
            ++child;
        }
        if (tmp > s[child])
        {
            ++sum;
            s[hole] = s[child];
        }
        else
        {
            ++sum;
            break;
        }
    }
    s[hole] = tmp;
}

void enQueue(int x, int &sz)
{
    int hole = ++sz;
    for (; hole > 1 && x < heap[hole / 2]; hole /= 2, ++sum)
    {
        heap[hole] = heap[hole / 2];
    }
    heap[hole] = x;
}

void heapSort(int s[], int size)
{
    int heapSize = 0;
    for (int i = 0; i < size; ++i)
    {
        enQueue(s[i], heapSize);
    }
    for (int i = 1; i <= heapSize; ++i)
        cout << heap[i] << ' ';
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, op;
    cin >> n >> op;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    sum = 0;
    switch (op)
    {
    case 1:
        heapSort(a, n);
        break;
    case 2:
        mergeSort(a, 0, n - 1);
        break;
    case 3:
        quickSort(a, 0, n - 1);
        break;
    }
    cout << sum << '\n';
    cout << flush;
    return 0;
}