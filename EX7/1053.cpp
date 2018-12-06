#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 1e5 + 7;
const int HASH_MAX = 500000;
struct Point
{
    int x = -1;
    int y = -1;
    int value;
};
Point val[HASH_MAX];
int row[MAXN], col[MAXN];
void swap(int &a, int &b)
{
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}
void init()
{
    for(int i = 0; i < MAXN; ++i)
    {
        row[i] = i;
        col[i] = i;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n, m, num, op, pos;
    unsigned int x, y;
    cin >> n;
    init();
    for(int i = 0; i < n; ++i)
    {
        cin >> x >> y >> num;
        pos = x * y % HASH_MAX;
        while(val[pos].x != -1)
            pos = (pos + 1) % HASH_MAX;
        val[pos].x = x;
        val[pos].y = y;
        val[pos].value = num;
    }
    cin >> m;
    for(int i = 0; i < m; ++i)
    {
        cin >> op;
        switch(op)
        {
            case 0:
                cin >> x >> y;
                swap(row[x], row[y]);
                break;
            case 1:
                cin >> x >> y;
                swap(col[x], col[y]);
                break;
            case 2:
                cin >> x >> y;
                x = row[x];
                y = col[y];
                pos = x * y % HASH_MAX;
                while(!(val[pos].x == x && val[pos].y == y) && val[pos].x != -1)
                    pos = (pos + 1) % HASH_MAX;
                if(val[pos].x == -1)
                    cout << 0 << '\n';
                else
                    cout << val[pos].value << '\n';
                break;
        }
    }

    cout << flush;
    return 0;
}