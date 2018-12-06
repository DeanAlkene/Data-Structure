#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN = 1e5 + 7;
const int INF = 1e9;
int stone[MAXN];
void merge(int A[], int left, int mid, int right);
void mergeSort(int A[], int left, int right);
bool check(int x, int m, int n);
bool check_1(int x, int m, int n, int index);
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, k, left, right, mid, secondMax = -1;
    cin >> n >> m >> k;
    for(int i = 0; i < n; ++i)
    {
        cin >> stone[i];
    }
    mergeSort(stone, 0, n - 1);
    for(int i = 1; i < n; ++i)
    {
        stone[i] = stone[i] - stone[0];
    }
    stone[0] = 0;
    if(k == 1)
    {
        left = 0, right = stone[n - 1];
        while(left <= right)
        {
            mid = (left + right) / 2;
            if(check(mid, n - m, n))
            {
                left = mid + 1;
            }
            else
                right = mid - 1;
        }
        cout << right << '\n';
    }
    else
    {
        for(int j = 0; j < n; j += (n - 1) / 2)
        {
            left = 0, right = stone[n - 1];
            while(left <= right)
            {
                mid = (left + right) / 2;
                if(check_1(mid, n - m, n, j))
                {
                    left = mid + 1;
                }
                else
                    right = mid - 1;
            }
            if(right > secondMax)
                secondMax = right;
        }
 
        cout << secondMax << '\n';
    }
 
    cout << flush;
    return 0;
}
 
void mergeSort(int A[], int left, int right)
{
    if(left == right) return;
    int mid = (left + right) / 2;
    mergeSort(A, left, mid);
    mergeSort(A, mid + 1, right);
    merge(A, left, mid, right);
}
 
void merge(int A[], int left, int mid, int right)
{
    int len = right - left + 1;
    int i = left, j = mid + 1, k = 0;
    int *tmp = new int[len];
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
 
bool check(int x, int m, int n)
{
    int last = 0, k = 0;
    for(int i = 1; i < n; ++i)
    {
        if(stone[i] - last < x)
        {
            k++;
        }
        else
            last = stone[i];
    }
    if(k <= m)
        return true;
    else
        return false;
}
 
bool check_1(int x, int m, int n, int index)
{
    int last = 0, k = 0, i = 1;
    if(index == 0)
    {
        last = stone[1];
        i = 2;
    }
    for(; i < n; ++i)
    {
        if(i == index)
            continue;
        if(stone[i] - last < x)
        {
            k++;
        }
        else
            last = stone[i];
    }
    if(k <= m)
        return true;
    else
        return false;
}

