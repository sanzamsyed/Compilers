/*
    AUTHOR: Nusrat Anika || Syed Sanzam
    Topic : Context Free Grammar (Evaluation of Arithmetic Expression)
    DATE: 25.09.19

    The Code follows the following CFG,

        E -> E + T | E - T | T

        T -> T * F | T / F | F

        F -> (E) | n
*/

#include <bits/stdc++.h>

using namespace std;

int len;
int read = 0;
bool check;

void factor(string s);

bool isNumber(string s)
{
    bool isNum = false;
    while(true)
    {
        if(isdigit(s[read]))
        {
            read++;
            isNum = true;
        }

        else
            break;
    }

    return isNum;

}

bool isChar(string s)
{
    bool isChar = false;
    while(true)
    {
        if(isalpha(s[read]))
        {
            read++;
            isChar = true;
        }

        else
            break;
    }

    return isChar;

}
void term(string s)
{
    factor(s);
    if(read < len)
    {
        if(check)
        {
            if(s[read] == '+'||s[read] == '-'||s[read] == '*'||s[read] == '/' || s[read] == '=')
            {
                check = true;
                read++;
                term(s);
            }
            else
            {
                check = false;
                return;
            }
        }
    }
    else
    	return;
}

void factor(string s)
{
    check = false;
    if(read < len)
    {
        if(isNumber(s) || isChar(s))
        {
            check = true;
            return;
        }
        else if(s[read] == '(')
        {
            read++;
            term(s);
            if(s[read] == ')')
            {
                read++;
                check = true;
                return;
            }
            else
                check = false;
        }

        else
        {
            read++;
            check = false;
            return ;
        }
    }
    else
    	return;
}

void expression(string s)
{
    if(s.length() > 1)
    {
        term(s);
        if(check)
            cout << "Accepted!" << endl;

        else
            cout << "Not Accepted!" << endl;
    }
    else
        cout << "Accepted!" << endl;
}

void init()
{
    int noOfTime = 0;
    cout << "No. of Times: " << endl;
    cin >> noOfTime;
    for(int i = 0; i < noOfTime; i++)
    {
        string s;
        cout << "Expression: " << endl;
        cin >> s;
        len = s.length();
        expression(s);

        read = 0;
    }
}

int main()
{
    init();
    return 0;
}

