#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 107;
int n, m;
char maze[MAXN][MAXN];
int dxy[4][2] = {{-1,0},{0,1},{1,0},{0,-1}}, visited[MAXN][MAXN];
struct Point
{
    int x;
    int y;
    int step;
};
Point sp, ep;
 
bool check(Point p)
{
    if(p.x < 1 || p.y < 1 || p.x > n || p.y > m || visited[p.x][p.y] || maze[p.x][p.y] == '*')
        return false;
    return true;
}
 
int BFS(Point start, Point finish)
{
    Point s, e;
    Point q[100007];
    int head = 0, tail = 0;
    s.x = start.x;
    s.y = start.y;
    s.step = 0;
    visited[s.x][s.y] = 1;
    q[tail++] = s;
    while(head != tail)
    {
        s = q[head++];
        if(s.x == finish.x && s.y == finish.y) return s.step;
        for(int i = 0; i < 4; ++i)
        {
            if(i == 0 || i == 2)
            {
                if(maze[s.x][s.y] == '-')
                    continue;
            }
            if(i == 1 || i == 3)
            {
                if(maze[s.x][s.y] == '|')
                    continue;
            }
            e.x = s.x + dxy[i][0];
            e.y = s.y + dxy[i][1];
            if(!check(e))
                continue;
            if(i == 0 || i == 2)
            {
                if(maze[e.x][e.y] == '-')
                    continue;
            }
            if(i == 1 || i == 3)
            {
                if(maze[e.x][e.y] == '|')
                    continue;
            }
            e.step = s.step + 1;
            visited[e.x][e.y] = 1;
            q[tail++] = e;
        }
    }
    return -1;
}
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    cin >> sp.x >> sp.y >> ep.x >> ep.y;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            cin >> maze[i][j];
    memset(visited, 0, sizeof(visited));
    int ans = BFS(sp, ep);    
    cout << ans << '\n';
    cout << flush;
    return 0;
}