#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 1e3 + 7;

int height[MAXN];
char input[2*MAXN];
inline int max(int a, int b) {return a > b ? a : b;}
void read()
{
    int num, len = 0;
    char *p;
    cin >> input;
    p = input;
    while(*p)
    {
        if(*p >= '0' && *p <= '9')
        {
            num = 0;
            while(*p >= '0' && *p <= '9')
            {
                num = num * 10 + *p - '0';
                ++p;
            }
            height[len++] = num;
        }
        ++p;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, peek = -1, pos = 0, cur, volume = 0;
    cin >> n;
    read();
    for(int i = 0; i < n; ++i)
    {
        if(height[i] > peek)
        {
            peek = height[i];
            pos = i;
        }
    }
    cur = height[0];
    for(int  i = 1; i < pos; ++i)
    {
        cur = max(cur, height[i]);
        volume += cur - height[i];
    }
    cur = height[n-1];
    for(int  i = n - 2; i >= pos; --i)
    {
        cur = max(cur, height[i]);
        volume += cur - height[i];
    }
    cout << volume << '\n';
    cout << flush;
    return 0;
}