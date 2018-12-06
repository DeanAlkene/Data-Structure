#include <iostream>
#include <cstring>
using namespace std;

void dealCommand(char file[][2001], char *command, int lines);
void splitCommand(char *command, int &i, int &j, char *str, int &num);
void List(char file[][2001], int i, int j, int lines);
void Ins(char file[][2001], int i, int j, char *str, int lines);
void Del(char file[][2001], int i, int j, int num, int lines);
void Quit(char file[][2001], int lines);

int main()
{
	char file[100][2001];
	int i = 0, lines;
	cin.getline(file[i],2001);
	while(strcmp(file[i],"******") != 0)
	{
		i++;
		cin.getline(file[i],2001);
	}
	lines = i + 1;

	i = 0;
	char command[151];
	cin.getline(command,151);
	while(command[0] != 'q')
	{
		dealCommand(file, command, lines);
		cin.getline(command,151);
	}
	Quit(file, lines);

	return 0;
}

void dealCommand(char file[][2001], char *command, int lines)
{
	char flag = command[0];
	int i, j, num;
	char str[101];
	splitCommand(command, i, j, str, num);
	switch(flag)
	{
	case 'l':
		List(file, i, j, lines);
		break;
	case 'i':
		Ins(file, i, j, str, lines);
		break;
	case 'd':
		Del(file, i, j, num, lines);
		break;
	case 'q':
		Quit(file, lines);
		break;
	}
}

void splitCommand(char *command, int &i, int &j, char *str, int &num)
{
	int m = 0,n = 0;
	char tmp[101];
	while(command[m] != ' ' && command[m] != '\0')
		++m;
	//find first blank
	n = ++m;
	while(command[m] != ' ' && command[m] != '\0')
	{
		tmp[m - n] = command[m];
		++m;
	}
	tmp[m - n] = '\0';
	i = 0;
	n = 0;
	while(tmp[n] != '\0')
	{
		i = i * 10 + tmp[n] - '0';
		++n;
	}
	//find second blank
	n = ++m;
	while(command[m] != ' ' && command[m] != '\0')
	{
		tmp[m - n] = command[m];
		++m;
	}
	tmp[m - n] = '\0';
	j = 0;
	n = 0;
	while(tmp[n] != '\0')
	{
		j = j * 10 + tmp[n] - '0';
		++n;
	}
	//if there is a third blank
	if(command[m] == ' ')
	{
		if(command[0] == 'i')
		{
			n = ++m;
			while(command[m] != '\0')
			{
				str[m - n] = command[m];
				++m;
			}
			str[m - n] = '\0';
		}
		else
		{
			n = ++m;
			while(command[m] != '\0')
			{
				tmp[m - n] = command[m];
				++m;
			}
			tmp[m - n] = '\0';
			num = 0;
			n = 0;
			while(tmp[n] != '\0')
			{
				num = num * 10 + tmp[n] - '0';
				++n;
			}
		}
	}
}

void List(char file[][2001], int i, int j, int lines)
{
    i--;
    j--;
	if(j - i < 0 || i < 0 || j >= lines - 1)
		cout << "Error!" << endl;
	else
	{
		for(int k = i; k <= j; ++k)
		{
			cout << file[k] << endl;
		}
	}
}

void Ins(char file[][2001], int i, int j, char *str, int lines)
{
    i--;
    j--;
	if(i < 0 || i >= lines - 1)
		cout << "Error!" << endl;
	else
	{
		int len = strlen(file[i]);
		if(j < 0 || j > len)
			cout << "Error!" << endl;
		else
		{
			int s_len = strlen(str);
			int k;
			for(k = len - 1; k >= j; --k)
			{
				file[i][k + s_len] = file[i][k];
			}
			file[i][len + s_len] = '\0';
			for(k = j; k < j + s_len; ++k)
			{
				file[i][k] = str[k - j];
			}
		}
	}
}

void Del(char file[][2001], int i, int j, int num, int lines)
{
    i--;
    j--;
	if(i < 0 || i >= lines - 1)
		cout << "Error!" << endl;
	else
	{
		int len = strlen(file[i]);
		if(j < 0 || j > len)
			cout << "Error!" << endl;
		else
		{
			if(len - j < num)
				cout << "Error!" << endl;
			else
			{
				int k;
				for(k = j + num; k < len; ++k)
				{
					file[i][k - num] = file[i][k];
				}
				file[i][k - num] = '\0';
			}
		}
	}
}

void Quit(char file[][2001], int lines)
{
	List(file, 1, lines - 1, lines);
}