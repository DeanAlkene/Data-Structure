#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 1e3 + 7;

char x[MAXN], y[MAXN], input[MAXN];
int state[MAXN][MAXN];
int max(int x, int y)
{
    return (x > y) ? x : y;
}
int LCS(char *x, char *y, int n, int m)
{
    memset(state, 0, sizeof(state));
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m; ++j)
        {
            if(x[i-1] == y[j-1])
                state[i][j] = state[i-1][j-1] + 1;
            else
                state[i][j] = max(state[i-1][j],state[i][j-1]);
        }
    }
    return state[n][m];
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    cin >> x;
    cin >> y;
    int length = LCS(x, y, n, m);
    cout << length << '\n';
    cout << flush;
    return 0;
}
