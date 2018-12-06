#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN = 1e6 + 7;
int seq[MAXN], minList[MAXN];

int getMin(int index, int len)
{
    int left = 0, right = len, mid;
    while(left < right)
    {
        mid = (left + right) / 2;
        if(minList[mid] >= seq[index])
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, length;
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> seq[i];
    }
    minList[1] = seq[1];
    length = 1;
    for(int i = 2; i <= n; ++i)
    {
        if(seq[i] > minList[length])
        {
            minList[++length] = seq[i];
        }
        else
        {
            int tmp = getMin(i, length);
            minList[tmp] = seq[i];
        }
    }

    cout << length << '\n';
    cout << flush;
    return 0;
}