/*
    AUTHOR: Syed Sanzam
    Topic : Context Free Grammar
    DATE: 23.09.19

    The Code follows the following CFG,
        A --> a X d
        X --> b b X
        X --> b c X
        X --> Empty
*/


#include <bits/stdc++.h>

using namespace std;


int len;
int read = 0;

bool X(string str)
{
	bool checkLastChar = true;
	while(read < len - 1)
	{
		if(str[read] == 'b')
		{
			if(str[read + 1] == 'b')
			{
				read = read + 2;
			}
			else if(str[read + 1] == 'c')
			{
				read = read + 2;
			}
			else
			{
				checkLastChar = false;
				break;
			}
		}

		else
		{
			checkLastChar = false;
			break;
		}
	}
	return checkLastChar;
}

void A(string str)
{
	len = str.length();
	if(str[0] == 'a')
	{
		read++;
		if(len == 2)
		{
			if(str[len - 1] == 'd')
			{
				cout << "Accepted" << endl;
			}
			else
			{
				cout << "Not Accepted" << endl;
			}
		}
		else
		{
			if(X(str))
			{
				if(str[len - 1] == 'd')
				{
					cout << "Accepted" << endl;
				}
				else
				{
					cout << "Not Accepted" << endl;
				}
			}
			else
			{

				cout << "Not Accepted" << endl;
			}
		}
	}
}

void init()
{
    int noOfTimes = 0;
    string s = " ";

    cout << "No. of Times :" << endl;
    cin >> noOfTimes;

    for(int i = 0; i < noOfTimes; i++)
    {
        cout << "String: ";
        cin >> s;
        A(s);
        len = 0;
        read = 0;
        cout << endl;
    }
}

int main()
{
    init();
}
