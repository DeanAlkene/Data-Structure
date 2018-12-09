#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 1e5 + 7;
int a[MAXN], b[MAXN];

int divide(int s[], int low, int high)
{
    int tmp = s[low];
    do
    {
        while (low < high && s[high] >= tmp)
            --high;
        if (low < high)
            s[low] = s[high], ++low;
        while (low < high && s[low] <= tmp)
            ++low;
        if (low < high)
            s[high] = s[low], --high;
    } while (low != high);
    s[low] = tmp;
    return low;
}

void quickSort(int s[], int low, int high)
{
    int mid;
    if (low >= high)
        return;
    mid = divide(s, low, high);
    quickSort(s, low, mid);
    quickSort(s, mid + 1, high);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, sum = 0, next = 0;

    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < m; ++i)
        cin >> b[i];
    quickSort(a, 0, n - 1);
    quickSort(b, 0, m - 1);
    for (int i = 0; i < n; ++i)
    {
        for (int j = next; j < m; ++j)
        {
            //better solve
            //if(a[i] <= b[next])
            //    break;
            if (a[i] > b[j])
            {
                sum++;
                next = j + 1;
                break;
            }
        }
    }
    sum += n;
    cout << sum << '\n';
    cout << flush;
    return 0;
}