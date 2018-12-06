#include <iostream>
#include <cstdio>
#include <cstring>
#define MAXN 100000
using namespace std;

int search_n(long long int a[], int left, int right, long long int pos, int n)
{
    if(pos >=a [n - 1])
        return n - 1;
    if(pos < a[0])
        return -1;
    long long int mid = (left+right) / 2;

    if(a[mid-1] <= pos && a[mid] > pos)
        return mid - 1;
    if(a[mid+1] > pos && a[mid] <= pos)
        return mid;

    if(a[mid] > pos)
    {
        right = mid;
        return search_n(a, left, right, pos, n);
    }
    else if(a[mid] <= pos)
    {
        left = mid;
        return search_n(a, left, right, pos, n);
    }
}

int main()
{
    int n, t, index;
    long long int X[MAXN], Y[MAXN];
    scanf("%d %d", &n, &t);
    //ios::sync_with_stdio(false);
    for(int i = 0; i < n; ++i)
    {
        scanf("%lld", &X[i]);
    }
    for(int i = 0; i < t; ++i)
    {
        scanf("%lld", &Y[i]);
    }
    for(int i = 0; i < t; ++i)
    {
        index = search_n(X, 0, n - 1, Y[i], n);
        int tmp = n - index - 1;
        printf("%d", tmp);
        printf("\n");
    }
    return 0;
}