#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1e6+7;
int tree[MAXN];
int chain1[MAXN], chain2[MAXN];
int LCA(int i, int j)
{
    int now, m = 0, n = 0, k;
    now = i;
    while(now != -1)
    {
        chain1[m++] = now;
        now = tree[now];   
    }
    now = j;
    while(now != -1)
    {
        chain2[n++] = now;
        now = tree[now];
    }
    if(m > n)
    {
        int delta = m - n;
        k = 0;
        while(chain1[k + delta] != chain2[k])
            ++k;
        return chain2[k];
    }
    else
    {
        int delta = n - m;
        k = 0;
        while(chain1[k] != chain2[k + delta])
            ++k;
        return chain1[k];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, x, y, lc, rc;
    memset(tree, -1, sizeof(tree));
    cin >> n >> x >> y;
    for(int i = 1; i <= n; ++i)
    {
        cin >> lc >> rc;
        tree[lc] = tree[rc] = i;
    }
    cout << LCA(x, y) << '\n';
    
    cout << flush;
    return 0;
}