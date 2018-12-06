#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int MAXN = 2e5+7;
long long int st[MAXN][20];
long long int seq[MAXN];
long long int max(long long int x, long long int y)
{
    return (x > y) ? x : y;
}
void getST(int n)
{
    for(int j = 1; j <= 20; ++j)
    {
        for(int i = 1; i <= n; ++i)
        {
            if(i + (1<<j) - 1 <= n)
            {
                st[i][j] = max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
            }
        }
    }
}

int main()
{
    int k, n;
    cin >> k >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> seq[i];
        st[i][0] = seq[i];
    }
    getST(n);
    for(int i = 1; i <= n-k+1; ++i)
    {
        int index = (int) (log((double)(k))/log(2.0));
        cout << max(st[i][index],st[i+k-1-(1<<index)+1][index]) << ' ';
    }
    return 0;
}