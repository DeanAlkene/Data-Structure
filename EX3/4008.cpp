#include <iostream>
#include <cstring>
using namespace std;

char *add(const char *a, const char *b)
{
	int len1 = strlen(a), len2 = strlen(b);
	int minLen = (len1 > len2 ? len2 : len1);
	int len = (len1 > len2 ? len1 : len2) + 1;
	char *result = new char[len + 1];
	int carry = 0, tmp, i;

	for (i = 0; i < minLen; ++i)
	{
		tmp = a[i] - 'a' + b[i] - 'a' + carry;
		result[i] = tmp % 26 + 'a';
		carry = tmp / 26;
	}

	while (i < len1)
	{
		tmp = a[i] - 'a' + carry;
		result[i] = tmp % 26 + 'a';
		carry = tmp / 26;
		++i;
	}

	while (i < len2)
	{
		tmp = b[i] - 'a' + carry;
		result[i] = tmp % 26 + 'a';
		carry = tmp / 26;
		++i;
	}

	if (carry != 0)
		result[i++] = carry + 'a';

	result[i] = '\0';

	return result;
}

void reverse(char *s)
{
    int length = strlen(s);
    char *str = new char[length];
    for (int i = 0; i < length; ++i)
	{
        str[length - i - 1] = s[i];
	}
	for (int i = 0; i < length; ++i)
	{
        s[i] = str[i];
	}
    delete [] str;
}

int main()
{
    char s_a[101], s_b[101];
    char *result;
    cin >> s_a;
    cin >> s_b;
    reverse(s_a);
    reverse(s_b);
    result = add(s_a, s_b);
    reverse(result);
    cout << result << endl;
    return 0;
}