#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN = 1e5 + 7;
long long int trees[MAXN];

long long int getInverseNum(long long int seq[], int n);
void mergeSort(long long int A[], int left, int right, long long int &num);
void merge(long long int A[], int left, int mid, int right, long long int &num);

int main()
{
    long long int n, k;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        cin >> trees[i];
    }
    k = getInverseNum(trees, n);
    cout << k << '\n';
    cout << flush;
    return 0;
}

long long int getInverseNum(long long int seq[], int n)
{
    long long int a = 0;
    mergeSort(seq, 0, n - 1, a);
    return a;
}
void mergeSort(long long int A[], int left, int right, long long int &num)
{
    if(left == right) return;
    int mid = (left + right) / 2;
    mergeSort(A, left, mid, num);
    mergeSort(A, mid + 1, right, num);
    merge(A, left, mid, right, num);
}
void merge(long long int A[], int left, int mid, int right, long long int &num)
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
            num += mid - i + 1;
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