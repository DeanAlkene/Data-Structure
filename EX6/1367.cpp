#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 3e4 + 7;
long long a[MAXN], b[MAXN];
inline long long max(long long a, long long b) {return a > b ? a : b;}
long long total, ch[32 * MAXN][2], value[32 * MAXN];
        
void insert(long long x)
{
    long long now = 0;
    for(long long i = 31; i >= 0; --i)
    {
        long long next = ((1 << i) & x) ? 1 : 0;
        if(ch[now][next] == -1)
        {
            memset(ch[total], -1, sizeof(ch[total]));
            ch[now][next] = total;
            total++;
        }
        now = ch[now][next];
    }
    value[now] = x;
}
long long search(long long x)
{
    long long now = 0;
    for(long long i = 31; i >= 0; --i)
    {
        long long next = ((1 << i) & x) ? 1 : 0;
        if(next == 0)
            now = ch[now][1] != -1 ? ch[now][1] : ch[now][0];
        else
            now = ch[now][0] != -1 ? ch[now][0] : ch[now][1];
    }
    return x ^ value[now];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n,m;
    memset(ch, -1, sizeof(ch));
    memset(value, 0, sizeof(value));
    total = 1;
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
    {
        cin >> a[i];
        insert(a[i]);
    }
    for(int i = 0; i < m; ++i)
    {
        cin >> b[i];
    }
    long long maxXOR = -1;
    for(int i = 0; i < m; ++i)
    {
        maxXOR = max(maxXOR, search(b[i]));
    }
    cout << maxXOR << '\n';
    cout << flush;
    return 0;
}