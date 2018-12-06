#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int power = 4;
const int base = 10000;
const int MAXN = 1007;
class bigInt
{
    friend ostream &operator<<(ostream &os, const bigInt &obj);
    friend bool operator<(const bigInt &a, const bigInt &b);
    friend bool operator>=(const bigInt &a, const bigInt &b);
    friend bool operator==(const bigInt &a, const bigInt &b);
    friend bigInt operator+(const bigInt &a, const bigInt &b);
    friend bigInt operator-(const bigInt &a, const bigInt &b);
    friend bigInt operator*(const bigInt &a, const bigInt &b);
    friend bigInt operator/(const bigInt &a, const bigInt &b);
    private:
        long long int num[MAXN];
    public:
        bigInt() {memset(num, 0, sizeof(num));}
        bigInt(const char *s)
        {
            int len = strlen(s), p, bit;
            memset(num, 0, sizeof(num));
            num[0] = (len + power - 1) / power;
            for(int i = 0, bit = 0; i < len; p *= 10, ++i)
            {
                if(i % power == 0)
                {
                    p = 1;
                    ++bit;
                }
                num[bit] += p * (s[i] - '0');
            }
        }
        bigInt(const bigInt &obj)
        {
            memset(num, 0, sizeof(num));
            for(int i = 0; i <= obj.num[0]; ++i)
            {
                num[i] = obj.num[i];
            }
        }
        bigInt &operator=(const bigInt &right)
        {
            if(this == &right) return *this;
            memset(num, 0, sizeof(num));
            for(int i = 0; i <= right.num[0]; ++i)
            {
                num[i] = right.num[i];
            }
            return *this;
        }
        void addNumber(long long int k)
        {
            if(k != 0 || num[0] != 0)
                num[++num[0]] = k;
        }
        void re()
        {
 
            long long int len = num[0];
            long long int tmp[MAXN];
            for(long long int i = 1; i <= len; ++i)
            {
                tmp[len - i + 1] = num[i];
            }
            for(long long int i = 1; i <= len; ++i)
            {
                num[i] = tmp[i];
            }
        }
        bool isOdd()
        {
            if(num[1] % 2 == 0)
                return false;
            else
                return true;
        }
        void operator/=(const long long int &a)
        {
            for(int i = num[0]; i > 1; --i)
            {
                num[i - 1] += (num[i] % a * base);
                num[i] /= a;
            }
            num[1] /= a;
            while(num[0] > 0 && num[num[0]] <= 0)
                --num[0];
        }
 
        bigInt operator/(const long long int &a)const
        {
            bigInt temp = *this;
            temp /= a;
            return temp;
        }
        void operator *= (const long long int &a)
        {
            for(int i = 1; i <= num[0]; ++i)
                num[i] *= a;
            for(int i = 1; i <= num[0]; ++i)
            {
                num[i + 1] += num[i] / base;
                num[i] %= base;
            }
        }
 
        bigInt operator * (const long long int &a)const
        {
            bigInt temp = *this;
            temp *= a;
            return temp;
        }
};
 
ostream &operator<<(ostream &os, const bigInt &obj)
{
    os << obj.num[obj.num[0]];
    for(long long int i = obj.num[0] - 1; i > 0; --i)
    {
        long long int len = 0, tmp = obj.num[i];
        while(tmp != 0)
        {
            tmp /= 10;
            len++;
        }
        for(long long int j = 0; j < power - len; ++j)
        {
            os << 0;
        }
        if(obj.num[i] != 0)
            os << obj.num[i];
    }
    return os;
}
bool operator<(const bigInt &a, const bigInt &b)
{
    if(a.num[0] < b.num[0])
        return true;
    if(a.num[0] > b.num[0])
        return false;
    for(int i = a.num[0]; i > 0; --i)
    {
        if(a.num[i] != b.num[i])
            return a.num[i] < b.num[i];
    }
    return false;
}
bool operator>=(const bigInt &a, const bigInt &b)
{
    return !(a < b);
}
bool operator==(const bigInt &a, const bigInt &b)
{
    if(a.num[0] != b.num[0])
        return false;
    for(int i = a.num[0]; i > 0; --i)
    {
        if(a.num[i] != b.num[i])
            return false;
    }
    return true;
}
bigInt operator+(const bigInt &a, const bigInt &b)
{
    bigInt result;
    result.num[0] = (a.num[0] > b.num[0]) ? a.num[0] : b.num[0];
    for(long long int i = 1; i <= result.num[0]; ++i)
    {
        result.num[i] += a.num[i] + b.num[i];
        result.num[i + 1] += result.num[i] / base;
        result.num[i] %= base;
    }
    if(result.num[result.num[0] + 1] != 0)
        ++result.num[0];
    return result;
}
bigInt operator-(const bigInt &a, const bigInt &b)
{
    bigInt result = a;
    for(long long int i = 1; i <= result.num[0]; ++i)
    {
        result.num[i] -= b.num[i];
        if(result.num[i] < 0)
        {
            result.num[i] += base;
            --result.num[i + 1];
        }
    }
    while(result.num[0] > 0 && !result.num[result.num[0]])
        --result.num[0];
    return result;
}
bigInt operator*(const bigInt &a, const bigInt &b)
{
    bigInt result;
    result.num[0] = a.num[0] + b.num[0] - 1;
    for(long long int i = 1; i <= a.num[0]; ++i)
    {
        for(long long int j = 1; j <= b.num[0]; ++j)
        {
            result.num[i + j - 1] += a.num[i] * b.num[j];
            result.num[i + j] += result.num[i + j - 1] / base;
            result.num[i + j - 1] %= base;
        }
    }
    if(result.num[result.num[0] + 1])
        ++result.num[0];
    return result;
}
bigInt operator/(const bigInt &a, const bigInt &b)
{
    bigInt x, y;
    if(a == b)
    {
        x.num[0] = 1;
        x.num[1] = 1;
        return x;
    }
    for(long long int i = a.num[0]; i >= 1; --i)
    {
        y.addNumber(a.num[i]);
        y.re();
        while(!(y < b))
        {
            y = y - b;
            ++x.num[i];
        }
        y.re();
    }
    x.num[0] = a.num[0];
    while(x.num[0] > 0 && !x.num[x.num[0]])
        --x.num[0];
    return x;
}
 
void reverse(char *num)
{
    int length = strlen(num);
    char *number = new char[length];
    for (int i = 0; i < length; ++i)
	{
        number[length - i - 1] = num[i];
	}
	for (int i = 0; i < length; ++i)
	{
        num[i] = number[i];
	}
    delete [] number;
}
bigInt value[57][57];

int main()
{
    int k, h;
    bigInt result, one("1"), ans("1");
    cin >> k >> h;
    
    for(int i = 0; i < k; ++i)
    {
        value[2][i] = one;
    }
    for(int i = 3; i <= h; ++i)
    {
        for(int j = 0; j < k; ++j)
        {
            for(int m = k - j - 1; m >= 0; --m)
            {
                value[i][j] = value[i][j] + value[i - 1][m];
            }
        }
    }

    for(int i = 0; i < k; ++i)
    {
        result = result + value[h][i];
    }
    
    cout << result << '\n';
    cout << flush;
    return 0;
}