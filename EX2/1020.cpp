#include <iostream>
#include <cmath>
#define MAXN 1000
using namespace std;

struct node
{
    int base;
    int exp = 0;
};
bool isPrime(int num);

int main()
{
    int num, tmp, factor[MAXN], index = 0, length;
    cin >> num;
    tmp = num;
    for(int i = 2; i < sqrt(num); ++i)
    {
        if(isPrime(i))
        {
            while(tmp % i == 0)
            {
                tmp = tmp / i;
                factor[index] = i;
                ++index;
            }
        }
    }

    if(tmp > 1)
    {
        factor[index] = tmp;
        length = index + 1;
    }
    else
    {
        length = index;
    }

    cout << num << '=';
    int j = 0;
    node result[100];
    result[0].base = factor[0];
    result[0].exp = 1;
    int last = factor[0];
    for(int i = 1; i < length; ++i)
    {
        if(factor[i] == last)
        {
            result[j].exp++;
        }
        else
        {
            j++;
            result[j].base = factor[i];
            result[j].exp = 1;
        }
        last = factor[i];
    }

    for(int i = 0; i <= j; ++i)
    {
        cout << result[i].base << '(' << result[i].exp << ')';
    }
    cout << endl;
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