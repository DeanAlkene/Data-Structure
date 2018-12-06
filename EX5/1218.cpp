#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 107;
int input[MAXN];

template <class T>
class seqList
{
private:
    T* data;
    int length;
    int maxSize;
    void resize();
public:
    seqList(int initLength = 10);
    ~seqList();
    void clear();
    void insert(int i, const T &x);
    void remove(int i);
    int search(const T &x) const;
    void traverse();
    void Union(T seq[], int n);
    void Intersection(T seq[], int n);
    void Difference(T seq[], int n);
    void mergeSort(T A[], int left, int right);
    void merge(T A[], int left, int mid, int right);
};

template <class T>
void seqList<T>::resize()
{
   T* tmp = data;
   maxSize *= 2;
   data = new T[maxSize];
   for (int i = 0; i < length; ++i)
    {
        data[i] = tmp[i];
    }
    delete [] tmp;
}

template <class T>
seqList<T>::seqList(int initLength)
{
    data = new T [initLength];
    maxSize = initLength;
    length = 0;
}

template <class T>
seqList<T>::~seqList()
{
    delete [] data;
}

template <class T>
void seqList<T>::clear()
{
    length = 0;
}

template <class T>
void seqList<T>::insert(int i, const T &x)
{
    if (length == maxSize)
        resize();
    for(int j = length-1; j >= i; --j)
    {
        data[j+1] = data[j];
    }
    data[i] = x;
    ++length;
}

template <class T>
void seqList<T>::remove(int i)
{
    for(int j = i; j < length - 1; ++j)
    {
        data[j] = data[j+1];
    }
    --length;
}

template <class T>
int seqList<T>::search(const T &x) const
{
    int i;
    for (i = 0; i < length; ++i)
    {
        if (data[i] == x)
            break;
    }
    if (i == length)
        return -1;
    else
        return i;
}

template <class T>
void seqList<T>::traverse()
{
    if(length > 0)
    {
        mergeSort(data, 0, length - 1);
    }
    for(int i = 0; i < length; ++i)
        cout << data[i] << ' ';
    cout << '\n';
}

template <class T>
void seqList<T>::Union(T seq[], int n)
{
    int cnt = 0;
    for(int i = 0; i < n; ++i)
    {
        int index = search(seq[i]);
        if(index == -1)
        {
            insert(length, seq[i]);
            cnt++;
        }
    }
}
template <class T>
void seqList<T>::Intersection(T seq[], int n)
{
    T *tmp = new T[maxSize];
    int cnt = 0;
    for(int i = 0; i < n; ++i)
    {
        int index = search(seq[i]);
        if(index != -1)
        {
            tmp[cnt++] = seq[i];
        }
    }
    for(int i = 0; i < cnt; ++i)
    {
        data[i] = tmp[i];
    }
    length = cnt;
    delete [] tmp;
}
template <class T>
void seqList<T>::Difference(T seq[], int n)
{
    int cnt = 0;
    for(int i = 0; i < n; ++i)
    {
        int index = search(seq[i]);
        if(index != -1)
        {
            remove(index);
            cnt++;
        }
    }
}

template <class T>
void seqList<T>::mergeSort(T A[], int left, int right)
{
    if(left == right) return;
    int mid = (left + right) / 2;
    mergeSort(A, left, mid);
    mergeSort(A, mid + 1, right);
    merge(A, left, mid, right);
}

template <class T>
void seqList<T>::merge(T A[], int left, int mid, int right)
{
    int len = right - left + 1;
    int i = left, j = mid + 1, k = 0;
    int *tmp = new T[len];
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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    char op;
    seqList<int> s;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        cin >> op;
        switch(op)
        {
            case '+':
                cin >> m;
                for(int j = 0; j < m; ++j)
                {
                    cin >> input[j];
                }
                s.Union(input, m);
                s.traverse();
                break;
            case '-':
                cin >> m;
                for(int j = 0; j < m; ++j)
                {
                    cin >> input[j];
                }
                s.Difference(input, m);
                s.traverse();
                break;
            case '*':
                cin >> m;
                for(int j = 0; j < m; ++j)
                {
                    cin >> input[j];
                }
                s.Intersection(input, m);
                s.traverse();
                break;
        }
    }
    cout << flush;
    return 0;
}