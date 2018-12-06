#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int board[10][10];
int visit[10][10];
int minCost, sx, sy, ex, ey;
int moveXY[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
bool check(int x, int y)
{
    if(x >= 0 && y >= 0 && x < 6 && y < 6)
        return true;
    return false;
}
void DFS(int x, int y, int cost, int state)
{
    if(cost < minCost)
    {
        if(x == ex && y == ey)
        {
            minCost = cost;
            return;
        }
        for(int i = 0; i < 4; ++i)
        {
            int nx = x + moveXY[i][0];
            int ny = y + moveXY[i][1];
            if(!check(nx, ny))
                continue;
            if(visit[nx][ny] == 0)
            {
                int tmpCost = state * board[nx][ny];
                int nState = (tmpCost % 4) + 1;
                int nCost = cost + tmpCost;
                visit[nx][ny] = 1;
                DFS(nx, ny, nCost, nState);
                visit[nx][ny] = 0;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        minCost = 1e9;
        for(int j = 0; j < 6; ++j)
        {
            for(int k = 0; k < 6; ++k)
            {
                cin >> board[j][k];
            }
        }
        cin >> sx >> sy >> ex >> ey;
        memset(visit, 0, sizeof(visit));
        DFS(sx, sy, 0, 1);
        cout << minCost << '\n';
    }

    cout << flush;
    return 0;
}