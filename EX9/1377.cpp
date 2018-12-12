#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1e5+7;
int seq[MAXN], sum[MAXN], L[2*MAXN], R[2*MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, b, index, ans = 0;
    cin >> n >> b;
    for(int i = 1; i <= n; ++i)
    {
        cin >> seq[i];
        if(seq[i] == b)
            index = i;
        else
        {
            if(seq[i] > b)
                seq[i] = 1;
            else
                seq[i] = -1;
        }
    }
    memset(L, 0, sizeof(L));
    memset(R, 0, sizeof(R));
    memset(sum, 0, sizeof(sum));
    L[n] = R[n] = 1;
    for(int i = index - 1; i >= 1; --i)
    {
        sum[i] = sum[i+1] + seq[i];
        L[sum[i]+n]++;
    }
    for(int i = index + 1; i <= n; ++i)
    {
        sum[i] = sum[i-1] + seq[i];
        R[sum[i]+n]++;
    }
    for(int i = 0; i < 2*n; ++i)
        ans += (L[i] * R[2*n-i]);
    cout << ans << '\n';
    cout << flush;
    return 0;
}