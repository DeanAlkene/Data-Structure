#include <iostream>
#include <cmath>
#define MAXN 100
using namespace std;

bool checkFull(int bowl[][MAXN], int l);
void grow(int bowl[][MAXN], int l);

int main()
{
    int l, bowl[MAXN][MAXN], i, j, turn = 0;
    cin >> l;
    for(i = 0; i < l; ++i)
    {
        for(j = 0; j < l; ++j)
        {
            cin >> bowl[i][j];
        }
    }
    while(!checkFull(bowl, l))
    {
        grow(bowl, l);
        turn++;
    }
    cout << turn << endl;
    return 0;
}

bool checkFull(int bowl[][MAXN], int l)
{
    int i, j;
    for(i = 0; i < l; ++i)
    {
        for(j = 0; j < l; ++j)
        {
            if(bowl[i][j] == 0)
                return false;
        }
    }
    return true;
}

void grow(int bowl[][MAXN], int l)
{
    int i, j, tmp[MAXN][MAXN];
    for(i = 0; i < l; ++i)
    {
        for(j = 0; j < l; ++j)
        {
            tmp[i][j] = bowl[i][j];
        }
    }
    for(i = 0; i < l; ++i)
    {
        for(j = 0; j < l; ++j)
        {
            if(tmp[i][j] == 1)
            {
                if(i > 0 && tmp[i-1][j] == 0)
                    bowl[i-1][j] = 1;
                if(i < l - 1 && tmp[i+1][j] == 0)
                    bowl[i+1][j] = 1;
                if(j > 0 && tmp[i][j-1] == 0)
                    bowl[i][j-1] = 1;
                if(j < l -1 && tmp[i][j+1] == 0)
                    bowl[i][j+1] = 1;
            }
        }
    }
}