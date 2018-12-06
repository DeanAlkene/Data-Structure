#include <iostream>
#include <cmath>
#define MAXN 100000
#define DIV 99999997
using namespace std;
 
void mergeSort(int A[], int left, int right, int &ans);
void merge(int A[], int left, int mid, int right, int &ans);
int binarySearch(int seq[], int length, int num);
 
int main()
{
    int n, X[MAXN], Y[MAXN], tmp[MAXN], seq[MAXN], ans;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        cin >> X[i];
        tmp[i] = X[i];
    }
 
    mergeSort(tmp, 0, n - 1, ans);
 
    for(int i = 0; i < n; ++i)
    {
        X[i] = binarySearch(tmp, n, X[i]);
    }
 
    for(int i = 0; i < n; ++i)
    {
        cin >> Y[i];
        tmp[i] = Y[i];
    }
 
    mergeSort(tmp, 0, n - 1, ans);
 
    for(int i = 0; i < n; ++i)
    {
        Y[i] = binarySearch(tmp, n, Y[i]);
    }
 
    for(int i = 0; i < n; ++i) //An inverse of the relationship between i and Y[i]
    {
        tmp[Y[i]] = i; //tmp includes the index of ordered Y
    }
    for(int i = 0; i < n; ++i)
    {
        seq[i] = tmp[X[i]]; //from tmp(index of orderd Y and rank of X's to fit the index of Y according to the rank of X)
    }
    
    ans = 0;
    mergeSort(seq, 0, n - 1, ans);
    cout << ans << endl;
    return 0;
}
 
void mergeSort(int A[], int left, int right, int &ans)
{
    if(left == right)
        return;
    int mid = (left + right) / 2;
    mergeSort(A, left, mid, ans);
    mergeSort(A, mid+1, right, ans);
    merge(A, left, mid, right, ans);
}
void merge(int A[], int left, int mid, int right, int &ans)
{
    int len = right - left + 1;
    int i = left,j = mid+1, k = 0;
    int *tmp = new int[len];
    while(i <= mid && j <= right)
    {
        if(A[i] <= A[j])
        {
            tmp[k++] = A[i++];
        }
        else
        {
            ans = (ans + mid - i + 1) % DIV;
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
    for(i = 0,k = left; k <= right;)
    {
        A[k++] = tmp[i++];
    }
    delete tmp;
}
 
int binarySearch(int seq[], int length, int num)
{
    int left = 0, right = length - 1;
    int mid;
    while(left <= right)
    {
        mid = (right + left) / 2;
        if(seq[mid] == num)
            return mid;
        else
        {
            if(seq[mid] > num)
                right = mid - 1;
            else
                left = mid + 1;
        }
    }
    return -1;
}