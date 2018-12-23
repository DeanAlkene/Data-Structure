#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 107;
int n, m;
int per[MAXN], maze[MAXN][MAXN], distant[MAXN][MAXN];
bool vis[MAXN][MAXN], siv[MAXN];
int dxy[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
inline int min(int a, int b) { return a < b ? a : b; }
struct Point
{
    int x;
    int y;
    int step;
    Point(int xx = 0, int yy = 0, int ss = 0) : x(xx), y(yy), step(ss) {}
};
Point tresure[MAXN], q[1000 * MAXN];
inline void swap(int &a, int &b)
{
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}

void reverse(int left, int right)
{
    for (right--; left < right; left++, right--)
        swap(per[left], per[right]);
}

bool nextPermutation(int left, int right)
{
    int cur = right - 1, prev = cur - 1;
    while (cur > left && per[prev] >= per[cur])
    {
        --cur;
        --prev;
    }
    if (cur <= left)
        return false;
    for (cur = right - 1; per[cur] <= per[prev]; cur--)
        ;
    swap(per[cur], per[prev]);
    reverse(prev + 1, right);
    return true;
}

bool check(Point p)
{
    if (p.x < 0 || p.y < 0 || p.x >= n || p.y >= m || vis[p.x][p.y] || maze[p.x][p.y] == -1)
        return false;
    return true;
}

int BFS(Point start, Point finish)
{
    Point s, e;
    memset(vis, 0, sizeof(vis));
    int head = 0, tail = 0;
    s.x = start.x;
    s.y = start.y;
    s.step = 0;
    vis[s.x][s.y] = true;
    q[tail++] = s;
    while (head != tail)
    {
        s = q[head++];
        if (s.x == finish.x && s.y == finish.y)
            return s.step;
        for (int i = 0; i < 4; ++i)
        {
            e.x = s.x + dxy[i][0];
            e.y = s.y + dxy[i][1];
            if (!check(e))
                continue;
            e.step = s.step + 1;
            vis[e.x][e.y] = true;
            q[tail++] = e;
        }
    }
    return -1;
}

void DFS(int x, int t_num, int m, int s, int &ans)
{
    for (int i = 0; i < t_num; ++i)
    {
        if (distant[x][i] != 0 && !siv[i])
        {
            if (m + 1 == t_num - 1)
                ans = min(ans, s + distant[x][i]);
            siv[x] = true;
            DFS(i, t_num, m + 1, s + distant[x][i], ans);
            siv[x] = false;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    int t_num = 1, ans = 1e9;
    bool flag = false;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> maze[i][j];
            if (maze[i][j] == 1)
            {
                tresure[t_num].x = i;
                tresure[t_num].y = j;
                ++t_num;
            }
            if (maze[i][j] == 2)
            {
                tresure[0].x = i;
                tresure[0].y = j;
            }
        }
    }
    memset(distant, 0, sizeof(distant));
    for (int i = 0; i < t_num; ++i)
    {
        for (int j = 0; j < t_num; ++j)
        {
            if (i != j)
            {
                distant[i][j] = BFS(tresure[i], tresure[j]);
                if (distant[i][j] == -1)
                {
                    flag = true;
                    break;
                }
            }
        }
        if (flag)
            break;
    }
    if (flag)
        cout << -1 << '\n';
    else
    {
        memset(siv, 0, sizeof(siv));
        DFS(0, t_num, 0, 0, ans);
        /*
        for(int i = 0; i <= t_num; ++i)
        {
            per[i] = i;
        }
        do
        {
            int dis = 0;
            for(int i = 0; i < t_num - 1; ++i)
            {
                dis += distant[per[i]][per[i+1]];
            }
            if(dis < ans)
                ans = dis;
        }while(nextPermutation(1, t_num));
        */
        cout << ans << '\n';
    }
    cout << flush;
    return 0;
}