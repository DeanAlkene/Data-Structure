#include <iostream>
using namespace std;

int Ackerman(int m, int n);

int main()
{
    int m, n, akm;
    cin >> m >> n;
    akm = Ackerman(m, n);
    cout << akm << endl;
    return 0;
}

int Ackerman(int m, int n)
{
    if(m == 0)
        return n+1;
    else
    {
        if(n == 0)
            return Ackerman(m - 1, 1);
        else
            return Ackerman(m - 1, Ackerman(m, n - 1));
    }
}