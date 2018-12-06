#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int MAXN = 2014;
long long int INF = 1e12;
int in[MAXN], inSeq[MAXN], deSeq[MAXN];
int state[MAXN][MAXN];
void merge(int A[], int left, int mid, int right);
void mergeSort(int A[], int left, int right);
long long int findMin(int seq[], int n);
long long int min(long long int x, long long int y)
{
    return (x < y) ? x : y;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    long long int minCost_1, minCost_2;
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> in[i];
        inSeq[i] = in[i];
    }
    mergeSort(inSeq, 1, n);
    for(int i = 1; i <= n; ++i)
    {
        deSeq[i] = inSeq[n - i + 1];
    }
    minCost_1 = findMin(inSeq, n);
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= n; ++j)
            cout << state[i][j] << '\t';
        cout << '\n';
    }
    minCost_2 = findMin(deSeq, n);
    cout << min(minCost_1, minCost_2) << '\n';
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

long long int findMin(int seq[], int n)
{
    long long int minCost = INF;
    long long int tmp;
    for(int i = 1; i <= n; ++i)
    {
        state[1][i] = abs(seq[i] - in[1]);
    }
    for(int i = 2; i <=n; ++i)
    {
        tmp = INF;
        for(int j = 1; j <= n; ++j)
        {
            tmp = min(tmp, state[i-1][j]);
            state[i][j] = tmp + abs(in[i] - seq[j]);
        }
    }
    for(int i = 1; i <= n; ++i)
    {
        minCost = min(minCost, state[n][i]);
    }
    return minCost;
}