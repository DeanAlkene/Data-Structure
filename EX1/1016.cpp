#include <iostream>
#include <cstring>
using namespace std;

bool greater_0(const char *a, const char *b)
{
	int len1 = strlen(a), len2 = strlen(b);
	if (len1 > len2)
		return true;
	else
	{
		if (len1 < len2)
			return false;
	}

	for (int i = len1 - 1; i >= 0; --i)
	{
		if (a[i] > b[i])
			return true;
		else
		{
			if (a[i] < b[i])
				return false;
		}
	}

	return true;
}

int fill_0(char *a, char *b)
{
    int delta;
    int len1 = strlen(a), len2 = strlen(b), i;
    bool flag = false;

    char *tmp = new char[len2+1];
    for(i = 0; i < len2; ++i)
    {
        tmp[i] = a[i + len1 - len2];
    }
    tmp[len2] = '\0';

    flag = greater_0(tmp, b);

    delete [] tmp;
    if(!flag)
        delta = len1 - len2 - 1;
    else
        delta = len1 - len2;
    if(len1 > len2)
    {
        char *new_b = new char[delta+len2];
        for(i = 0; i < delta; ++i)
        {
            new_b[i] = '0';
        }
        while(b[i-delta] != '\0')
        {
            new_b[i] = b[i - delta];
            i++;
        }
        for(i = 0; i < delta+len2; ++i)
        {
            b[i] = new_b[i];
        }
        b[delta+len2] = '\0';
        delete [] new_b;
    }
    return delta;
}

char *add(const char *a, const char *b)
{
	int len1 = strlen(a), len2 = strlen(b);
	int minLen = (len1 > len2 ? len2 : len1);
	int len = (len1 > len2 ? len1 : len2) + 1;
	char *result = new char[len + 1];
	int carry = 0, tmp, i;

	for (i = 0; i < minLen; ++i)
	{
		tmp = a[i] - '0' + b[i] - '0' + carry;
		result[i] = tmp % 10 + '0';
		carry = tmp / 10;
	}

	while (i < len1)
	{
		tmp = a[i] - '0' + carry;
		result[i] = tmp % 10 + '0';
		carry = tmp / 10;
		++i;
	}

	while (i < len2)
	{
		tmp = b[i] - '0' + carry;
		result[i] = tmp % 10 + '0';
		carry = tmp / 10;
		++i;
	}

	if (carry != 0)
		result[i++] = carry + '0';

	result[i] = '\0';

	return result;
}

char *sub(const char *a, const char *b)
{
    if(!greater_0(a,b))
    {
        char *result = new char[2];
        result[0] = 0;
        result[1] = '\0';
        return result;
    }
	int len1 = strlen(a), len2 = strlen(b);
	int minus = 0, i;
	char *result = new char[len1 + 1];

	for (i = 0; i < len2; ++i)
	{
		result[i] = a[i] - b[i] - minus;
		if (result[i] < 0)
		{
			result[i] += 10;
			minus = 1;
		}
		else
			minus = 0;
		result[i] += '0';
	}

	while (i < len1)
	{
		result[i] = a[i] - '0' - minus;
		if (result[i] < 0)
		{
			result[i] += 10;
			minus = 1;
		}
		else
			minus = 0;

		result[i] += '0';
		++i;
	}

	do
	{
		--i;
	} while (i > 0 && result[i] == '0');

	result[i + 1] = '\0';
	return result;
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

void div(char *a, char *b)
{
    int len1 = strlen(a), len2 = strlen(b);
    int quo[1000] = {0};
    char result[1000];
    int max_del = -1;
    while(greater_0(a,b))
    {
        int delta;
        char *tmp = new char[1000];
        strcpy(tmp,b);
        delta = fill_0(a,tmp);
        a = sub(a,tmp);
        quo[delta]++;
        if(delta>max_del)
            max_del = delta;
    }
    for(int i = 0; i < max_del+1; ++i)
    {
        result[i] = quo[max_del - i] + '0';
    }
    result[max_del+1] = '\0';
    cout << result << endl;
}
int main()
{
    char a[1000],b[1000];
    cin >> a;
    cin >> b;
    reverse(a);
    reverse(b);
    div(a,b);
    //reverse(c);
    //cout << c;
    return 0;
}


