#include <iostream>
using namespace std;

int main()
{
    int l, i, j, pace, level, temp_i, temp_j;
    cin >> l >> i >> j;
    i--;
    j--;
    if(i >= l/2)
        temp_i = l - i - 1;
    else
        temp_i = i;
    if(j >= l/2)
        temp_j = l - j - 1;
    else
        temp_j = j;
    if(temp_i < temp_j)
        level = temp_i + 1;
    else
        level = temp_j + 1;

    int start = 0;
    for(int tmp = 1; tmp < level; ++tmp)
        start += (l - 2*tmp) * 4 + 4;

    int delta = 0, length = l - 2 * (level - 1);
    if(i == level - 1)
    {
        delta = j - level + 1;
    }
    else
    {
        if(i == l - level)
            delta = 2 * length - 1 + l - level - 1 - j;
        else
        {
            if(j > l/2)
                delta = length + i - level;
            else
                delta = 2 * length - 2 + length + l - level - i - 1;
        }
    }
    pace = start + delta;
    cout << pace << endl;
    return 0;
}