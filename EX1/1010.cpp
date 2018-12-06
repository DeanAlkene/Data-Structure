#include <iostream>
using namespace std;

int main()
{
    int budget[12];
    int in_hand = 0, bank = 0, warning_month = 0;
    for(int i = 0; i < 12; ++i)
    {
        cin >> budget[i];
    }

    for(int i = 0; i < 12; ++i)
    {
        in_hand += 300;
        if(in_hand - budget[i] >= 100)
        {
            int money = (in_hand - budget[i]) / 100;
            bank += money * 100;
            in_hand -= money * 100;
        }
        if(in_hand - budget[i] < 0)
        {
            warning_month = i + 1;
            break;
        }
        else
        {
            in_hand -= budget[i];
        }
    }

    if(warning_month == 0)
    {
        in_hand += bank * 1.2;
        cout << in_hand;
    }
    else
    {
        cout << -warning_month;
    }

    return 0;
}