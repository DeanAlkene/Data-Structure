#include <iostream>
using namespace std;

void mergeSort(int A[], int left, int right);
void merge(int A[], int left, int mid, int right);

int main()
{
    int n, tmp;
    unsigned long long sum = 0;
    int place[100000];
    bool flag = false;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        cin >> place[i];
    }
    mergeSort(place, 0, n-1);

    for(int i = 0; i < n/2; ++i)
    {
        sum += place[n-i-1] - place[i];
    }

    cout << sum << endl;
}

void mergeSort(int A[], int left, int right)
{
    if(left == right)
        return;
    int mid = (left + right) / 2;
    mergeSort(A, left, mid);
    mergeSort(A, mid+1, right);
    merge(A, left, mid, right);
}
void merge(int A[], int left, int mid, int right)
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