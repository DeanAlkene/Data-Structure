#include <iostream>
using namespace std;

bool judgeSudoku(int S[][10]);

int main()
{
    int n;
    int S[10][10];
    
    cin >> n;
    for(int times = 0; times < n; ++times)
    {
        for(int i = 1; i <= 9; ++i)
        {
            for(int j = 1; j <= 9; ++j)
            {
                cin >> S[i][j];
            }
        }
        if(judgeSudoku(S))
            cout << "Right" << endl;
        else
            cout << "Wrong" << endl;
    }
    return 0;
}

bool judgeSudoku(int S[][10])
{
    int R[10][10] = {0}, C[10][10] = {0}, B[10][10] = {0};
    for(int i = 1; i <= 9; ++i)
    {
        for(int j = 1; j <= 9; ++j)
        {
            int i_tmp = (i-1) / 3, j_tmp = (j-1) / 3, num;
            if(i_tmp == 0)
                num = j_tmp + 1;
            else
            {
                if(i_tmp == 1)
                    num = j_tmp + 4;
                else
                    num = j_tmp + 7;
            }
            R[i][S[i][j]] = 1;
            C[j][S[i][j]] = 1;
            B[num][S[i][j]] = 1;
        }
    }

    for(int i = 1; i <= 9; ++i)
    {
        for(int j = 1; j <= 9; ++j)
        {
            if(!R[i][j])
                return false;
            if(!C[i][j])
                return false;
            if(!B[i][j])
                return false;
        }
    }
    return true;
}