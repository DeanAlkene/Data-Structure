#include <iostream>
using namespace std;

int findFastest(long long sum[]);

int main()
{
    long long sum[3] = {0}, wait[3] = {0}, w1, t1, w2, t2;
    int a[100000], n;
    
    cin >> n;
    //Old method
    for(int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    for(int i = 0; i < n; i += 3)
    {
        wait[0] += sum[0];
        sum[0] += a[i];
    }
    for(int i = 1; i < n; i += 3)
    {
        wait[1] += sum[1];
        sum[1] += a[i];
    }
    for(int i = 2; i < n; i += 3)
    {
        wait[2] += sum[2];
        sum[2] += a[i];
    }
    w1 = wait[0] + wait[1] + wait[2];
    t1 = sum[0];
    for(int j = 1; j < 3; ++j)
    {
        if(sum[j] > t1)
            t1 = sum[j];
    }

    //New method
    wait[0] = wait[1] = wait[2] = sum[0] = sum[1] = sum[2] = 0;
    for(int i = 0; i < n; ++i)
    {
        int minQ = findFastest(sum);
        wait[minQ] += sum[minQ];
        sum[minQ] += a[i];
    }
    w2 = wait[0] + wait[1] + wait[2];
    t2 = sum[0];
    for(int j = 1; j < 3; ++j)
    {
        if(sum[j] > t2)
            t2 = sum[j];
    }

    cout << w1 << ' ' << t1 << endl;
    cout << w2 << ' ' << t2 << endl;
    return 0;
}

int findFastest(long long sum[])
{
    int minQ = 0;
    long long tmp = sum[0];
    for(int i = 0; i < 3; ++i)
    {
        if(sum[i] < tmp)
        {
            tmp = sum[i];
            minQ = i;
        }
    }
    return minQ;
}
