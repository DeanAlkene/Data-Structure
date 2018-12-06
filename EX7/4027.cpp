#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 1e5 + 7;

int A[MAXN], B[MAXN], A_tmp[MAXN], B_tmp[MAXN], minList[MAXN];
int max(int x, int y)
{
    return (x > y) ? x : y;
}
int getMin(int index, int len)
{
    int left = 0, right = len - 1, mid;
    while(left < right)
    {
        mid = (left + right) / 2;
        if(minList[mid] >= A_tmp[index])
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}
int LIS(int n)
{
    int len;
    minList[0] = A_tmp[0];
    len = 1;
    for(int i = 1; i < n; ++i)
    {
        if(A_tmp[i] > minList[len-1])
        {
            minList[len++] = A_tmp[i];
        }
        else
        {
            int tmp = getMin(i, len);
            minList[tmp] = A_tmp[i];
        }
    }
    return len;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> A[i];
    for(int i = 0; i < n; ++i)
    {
        cin >> B[i];
        B_tmp[B[i]] = i;
    }
    for(int i = 0; i < n; ++i)
        A_tmp[i] = B_tmp[A[i]];
        
    int length = LIS(n);
    cout << length << '\n';
    cout << flush;
    return 0;
}
