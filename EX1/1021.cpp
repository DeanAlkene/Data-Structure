#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int x = 0, y = 0, n, i = 1, j;
    int mnt[150][150] = {0};
    cin >> n;

    mnt[0][0] = 1;
    while(i < n*n)
    {
        while(y+1 < n && !mnt[x][y+1])
        {
            ++y;
            ++i;
            mnt[x][y] = i; 
        }
        while(x+1 < n && !mnt[x+1][y])
        {
            ++x;
            ++i;
            mnt[x][y] = i;
        }
        while(y-1 >= 0 && !mnt[x][y-1])
        {
            --y;
            ++i;
            mnt[x][y] = i;
        }
        while(x-1 >= 0 && !mnt[x-1][y])
        {
            --x;
            ++i;
            mnt[x][y] = i;
        }
    }

    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < n; ++j)
        {
            cout << setw(6) << mnt[i][j];
        }
        cout << endl;
    }
    return 0;
}
