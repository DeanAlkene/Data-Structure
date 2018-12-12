#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 507;
int n, m;
int maze[MAXN][MAXN], idx[MAXN][MAXN], dxy[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
void DFS(int row, int col, int id)
{
    if(row < 0 || col < 0 || row >= n || col >= m) return;
    if(idx[row][col] > 0 || maze[row][col] == -1) return;
    idx[row][col] = id;
    for(int i = 0; i < 4; ++i)
        DFS(row+dxy[i][0], col+dxy[i][1],id);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int cnt = 0;
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            cin >> maze[i][j];
    memset(idx, 0, sizeof(idx));
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            if(idx[i][j] == 0 && maze[i][j] == 0)
                DFS(i, j, ++cnt);
    cout << cnt << '\n';
    cout << flush;
    return 0;
}