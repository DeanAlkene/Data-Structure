#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int num);

int main()
{
    int i, j, n, gap;

	cin >> n;
    if(isPrime(n))
    {
        gap = 0;
    }
    else
    {
        for(i = n+1; !isPrime(i); ++i){}
        for(j = n-1; !isPrime(j) && j >= 2; --j){}
        gap = i - j;
    }
    
    cout << gap;
    return 0;
}

bool isPrime(int num)
{
    int tmp = sqrt(num);
    for(int i = 2; i <= tmp; ++i)
    {
        if(num % i == 0)
            return 0;
    }
    return 1;
}
