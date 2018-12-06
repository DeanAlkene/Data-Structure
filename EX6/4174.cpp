#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1e5 + 7;
struct mnt
{
    long long pos;
    long long h;
};
mnt seq[MAXN];
void merge(mnt A[], int left, int mid, int right);
void mergeSort(mnt A[], int left, int right);
long long findMax(int n);
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        cin >> seq[i].pos;
    }
    for(int i = 0; i < n; ++i)
    {
        cin >> seq[i].h;
    }
    mergeSort(seq, 0, n - 1);
    long long result = findMax(n);
    if(n > 1)
        cout << result << '\n';
    else
        cout << 1 << '\n';
    cout << flush;
    return 0;
}

void mergeSort(mnt A[], int left, int right)
{
    if(left == right) return;
    int mid = (left + right) / 2;
    mergeSort(A, left, mid);
    mergeSort(A, mid + 1, right);
    merge(A, left, mid, right);
}
 
void merge(mnt A[], int left, int mid, int right)
{
    int len = right - left + 1;
    int i = left, j = mid + 1, k = 0;
    mnt *tmp = new mnt[len];
    while(i <= mid && j <= right)
    {
        if(A[i].pos <= A[j].pos)
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

long long findMax(int n)
{
    long long total = 2;
    for(int i = 1; i < n - 1; ++i)
    {
        if(seq[i].pos - seq[i].h > seq[i-1].pos)
            total++;
        else
        {
            if(seq[i].pos + seq[i].h < seq[i+1].pos)
            {
                total++;
                seq[i].pos += seq[i].h;
            }
        }
    }
    return total;
}