/*
** AUTHOR: Syed Sanzam
** TOPIC:  Categorize Lexemes and Modify Tokens 
** DATE:   July 29, 2019
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <stdbool.h>
#define MAX 100

char errorMessage[MAX][MAX];
int errorCount = 0;

bool isKeyword(char buffer[])
{
	if(strlen(buffer) == 0) return false;
	char keywords[32][10] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};
  	int i;
  	bool flag = false;


	for(i = 0; i < 32; ++i)
  	{
		if(strcmp(keywords[i], buffer) == 0)
		{
			flag = true;
			break;
		}
	}

	return flag;
}

bool isIdentifier(char *str)
{
	int len = strlen(str);
	int i = 0;

	while(i < len)
	{
		if(isalpha(str[i]) || str[i] == '_')
		{
			i++;
			while(isdigit(str[i]) || isalpha(str[i]) || str[i] == '_' )
			{
				i++;
			}

			break;
		}

		else
		{
			break;
		}
	}

	if(i == len) 
		return true;
	else 
		return false;
}

bool isNumber(char *str)
{
	int i = 0;
	while(i < strlen(str))
	{
		if(isdigit(str[i]))
		{
			i++;
		}

		else if(str[i] == '.')   
		{
			i++;
			while(isdigit(str[i]))
				i++;
			break;
		}

		else
			break;	
	}
	if(i == strlen(str))
		return true;
	else
		return false;

}

bool isSeperator(char* str)
{
	char ch;
	int len = strlen(str);
	int i = 0;
	bool flag = false;

	if(str[0] == '\0')
		return false;

	for(i = 0; i < len; i++)
	{
		ch = str[i];
		if(ch == ';' || ch == ','  || ch == '\'' )
		{
			flag = true;
			break;
		}
	}

	return flag;
}

bool isOperator(char *str)
{
	char ch = str[0];
	if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '!' || ch == '=')
		return true;
	return false;
}

bool isParenthesis(char* str)
{
	char ch;
	int len = strlen(str);
	int i = 0;
	bool flag = false;

	if(str[0] == '\0')
		return false;

	for(i = 0; i < len; i++)
	{
		ch = str[i];
		if(ch == '(' || ch == ')'  || ch == '{' || ch == '}' || ch == '[' || ch == ']' )
		{
			flag = true;
			break;
		}
	}

	return flag;
}


void printErrorMessage()
{
	for(int i = 0; i < errorCount; i++)
	{
		printf("%s",errorMessage[i]);
	}
}

void print(char str[20])
{
	if(str[0] != '\0')
	{
		if(isKeyword(str))
		{
			printf("[kw ");
			printf("%s",str);
			printf("] ");
		}
		else if(isIdentifier(str))
		{
			printf("[id ");
			printf("%s",str);
			printf("] ");
		}

		else if(isNumber(str))
		{
			printf("[num ");
			printf("%s",str);
			printf("] ");
		}
		else if(isSeperator(str))
		{
			printf("[sep ");
			printf("%s",str);
			printf("] ");
		}
		else if(isParenthesis(str))
		{
			printf("[par ");
			printf("%s",str);
			printf("] ");
		}
		else if(isOperator(str))
		{

		}
		else
		{
			printf("[unkn ");
			printf("%s",str);
			printf("] ");
			char errorPrompt[100];
			strcpy(errorPrompt,str);
			strcat(errorPrompt, " Is invalid\n");
			strcpy(errorMessage[errorCount],errorPrompt);
			errorCount++;
		}
	}

}

int main()
{
	
	FILE *fpRead;
	fpRead = fopen("input.txt","r");
	//fpRead = fopen("testinput.txt","r");

	char operators[] = "+-*/%=<>";
	char ch;
	char testC;
	char buffer[1000];
	char toks[1000];
	

	int test = 0;
	int j = 0;
	int i = 0;
	int k = 0;

	while( (ch = fgetc(fpRead)) != EOF)
	{
		if ( !(ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '\''))
		{

			buffer[j++] = ch;
		}

		else
		{
			
			buffer[j] = '\0';
			j = 0;
			print(buffer);
		}

		if ( (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '\''))
		{
			toks[k++] = ch;
			k = 0;
			print(toks);
				
		}
	
		if(ch == '+' || ch == '-' || ch == '=' || ch == '>' || ch == '<' || ch == '*' || ch == '/')
		{
			bool alreadyPrinted = false;
	   		for(i = 0; i < strlen(operators); ++i)
	        {
	   			if(ch == operators[i])
	   			{
	   			    testC = fgetc(fpRead);
	   			    for(test = 0; test < strlen(operators); test++)
	                {
	                    if(testC == operators[test])
	                    {
	                        printf("[op ");
							printf("%c%c",ch,testC);
							printf("] ");
	                        alreadyPrinted = true;
	                    }
	                }

	                if(!alreadyPrinted)
	                  {
	                    printf("[op ");
						printf("%c",ch);
						printf("] ");
	                    ungetc(testC,fpRead);
	                  }
	   			}
	   		}

		}
	}

	printf("\n\n");
	if(errorCount == 0)
	{
		printf("No errors found!\n");
	}
	else
	{
		printf("!!Warning!!\n");
		printErrorMessage();
		printf("\n");
	}
	return 0;
}
