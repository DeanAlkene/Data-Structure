#include <iostream>
#include <cstring>
#define MAXL 101
using namespace std;

bool ifEncode(char str[], char code[], int n);

int main()
{
    int length;
    char str[MAXL], code[MAXL];
    bool flag = false;
    cin >> str;
    cin >> code;
    length = strlen(str);
    for (int i = 2; i <= length; ++i)
    {
        if(length % i == 0)
        {
            if(ifEncode(str, code, i))
            {
                cout << i << endl;
                flag = true;
                break;
            }
        }
    }
    if(!flag)
        cout << "No Solution" << endl;
    return 0;
}

bool ifEncode(char str[], char code[], int n)
{
    char tmp[MAXL];
    int length = strlen(str);
    for(int i = 0; i < length; ++i)
    {
        tmp[i % n + i / n] = str[i]; 
    }
    tmp[length] = '\0';

    return (strcmp(code, tmp) == 0);
}