/*
** AUTHOR: Syed Sanzam
** TOPIC:  Generating Errors Present in a Source File
** DATE:   September 12, 2019
** COMMENT: Redundancy is ignored intentionally, the unused parts of the code are there for further modification. 
            There's a lot going on, quite messy.I could've done a better job. The capacity of the code is quite limited. 
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <stdbool.h>
#define MAX 100

char errorMessage[MAX][MAX];
int errorCount = 0;

FILE *fpRead;
FILE* fpWrite;
FILE* fpWrite2;


struct Table
{
    char index[MAX];
    char dataType[MAX];
    char name[MAX];
    char type[MAX];
    char scope[MAX];
};

struct Table symbolTable[MAX];

int tableCount = 0;

bool isKeyword(char buffer[])
{
    if(strlen(buffer) == 0)
        return false;
    char keywords[32][10] = {"auto","break","case","char","const","continue","default",
                             "do","double","else","enum","extern","float","for","goto",
                             "if","int","long","register","return","short","signed",
                             "sizeof","static","struct","switch","typedef","union",
                             "unsigned","void","volatile","while"
                            };
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
    int i = 0;
    for(i = 0; i < errorCount; i++)
    {
        printf("%s",errorMessage[i]);
    }
}

void identifyToken(char str[20])
{
    if(str[0] != '\0')
    {
        if(isKeyword(str))
        {

            fputc('[',fpWrite2);
            fputs(str,fpWrite2);
            fputs("]",fpWrite2);

            fputs(str,fpWrite);
            fputc(' ',fpWrite);

        }

        else if(isIdentifier(str))
        {

            fputc('[',fpWrite2);
            fputs("id ",fpWrite2);
            fputs(str,fpWrite2);
            fputs("]",fpWrite2);


            fputs("id ",fpWrite);
            fputs(str,fpWrite);
            fputc(' ',fpWrite);
        }

        else if(isNumber(str))
        {
            fputc('[',fpWrite2);
            fputs(str,fpWrite2);
            fputs("]",fpWrite2);

            fputs(str,fpWrite);
            fputc(' ',fpWrite);

        }
        else if(isSeperator(str))
        {
            fputc('[',fpWrite2);
            fputs(str,fpWrite2);
            fputs("]",fpWrite2);


            fputs(str,fpWrite);
            fputc(' ',fpWrite);

        }
        else if(isParenthesis(str))
        {
            fputc('[',fpWrite2);
            fputs(str,fpWrite2);
            fputs("]",fpWrite2);


            fputs(str,fpWrite);
            fputc(' ',fpWrite);

        }
        else if(isOperator(str))
        {

        }

        else
        {
            //printf("[unkn ");

            fputs("[unkn ",fpWrite2);
            fputs(str,fpWrite2);
            fputs("]",fpWrite2);

            fputs(str,fpWrite);
            fputc(' ',fpWrite);


            char errorPrompt[100];
            strcpy(errorPrompt,str);
            strcat(errorPrompt,"Is invalid\n");
            strcpy(errorMessage[errorCount],errorPrompt);
            errorCount++;
        }
    }

}

void trimSourceFile()
{
    fpRead = fopen("input1.txt","r");
    fpWrite = fopen("input2.txt","w");

	char c;

	while( (c = fgetc(fpRead)) != EOF)
	{

		//Single Line Comment Check
		if(c == '\n')
		{
		    fputs("\n",fpWrite);
			c = fgetc(fpRead);
                if(c == '(')
                {
                    //fputs(" ",fpWrite);

                }
                ungetc(c,fpRead);
		}
		else if(c == '/')
		{
			char d;
			char e;
			char f;

			d = fgetc(fpRead);
			if(d == '/')
			{
				while( (e = fgetc(fpRead)) != EOF)
				{
					if(e == '\n')
                    {
                        //fputc('\n',fpWrite);
						break;
                    }
				}

                fputs("HELLO!",fpWrite);

			}

			//Block Comment Check
			if(d == '*')
			{
				while( (e = fgetc(fpRead)) != EOF)
				{
					if(e == '/')
					{
						f = fgetc(fpRead);
						break;
					}

                    if(e == '\n')
                    {
                        fputc('\n',fpWrite);
                    }
				}
			}
		}
			//Whitespace Check


		else if(c == ' ')
		{
			char b;
			char s;

			b = fgetc(fpRead);

			if(b != '(' && b!= ' ')
			{
				fputc(c,fpWrite);

			}



			fputc(b,fpWrite);
			while ((s = fgetc(fpRead)) != EOF)
			{
				if(s != ' ')
					break;
			}
			fputc(s,fpWrite);
		}


		else
		{

			//Newline & Tab Check
			if(c != '\t' && c != '\n' && c != ' ')
			{
                fputc(c,fpWrite);
                c = fgetc(fpRead);
                if(c == '(')
                {
                    //fputs(" ",fpWrite);

                }
                ungetc(c,fpRead);

                c = fgetc(fpRead);
                bool operatorFound = false;
                if(c == '+' || c == '-' || c == '*' || c == '%' || c == '<' || c == '>' || c == '=')
                {
                    //fputs(" ",fpWrite);
                    operatorFound = true;
                }
                ungetc(c,fpRead);
                if(operatorFound)
                {
                    //fputs(" ",fpWrite);
                }

			}

		}
	}

	fclose(fpRead);
	fclose(fpWrite);
}

void recongniseLexemes()
{
    fpRead = fopen("input2.txt","r");
    fpWrite = fopen("temporary.txt","w");
    fpWrite2 = fopen("input3.txt","w");


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

        if(ch == '\n')
        {
           
            fputc(ch,fpWrite);
            
        }

        if ( !(ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
                ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
                ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
                ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '\'' || ch == '\n'))
        {

            buffer[j++] = ch;

        }

        else
        {

            buffer[j] = '\0';
            j = 0;

            identifyToken(buffer);
        }

        if ( (ch == '+' || ch == '-' || ch == '*' ||
                ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
                ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
                ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '\''))
        {
            toks[k++] = ch;
            k = 0;
            identifyToken(toks);
            //printf("\nvalue of toks:%s\n",toks);

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

                            fputs("[",fpWrite2);
                            fputc(ch,fpWrite2);
                            fputc(testC,fpWrite2);
                            fputs("]",fpWrite2);


                            printf("%c%c ",ch,testC);
                            fputc(ch,fpWrite);
                            fputc(testC,fpWrite);
                            fputc(' ',fpWrite);

                            alreadyPrinted = true;
                        }
                    }

                    if(!alreadyPrinted)
                    {

                        fputs("[",fpWrite2);
                        fputc(ch,fpWrite2);
                        fputs("]",fpWrite2);


                        fputc(ch,fpWrite);
                        fputc(' ',fpWrite);

                        ungetc(testC,fpRead);
                    }
                }
            }

        }
    }

    fclose(fpWrite);
    fclose(fpWrite2);


}


void prepareIntermediateFile()
{
    fpRead = fopen("temporary.txt","r");
    fpWrite = fopen("intermediate.txt","w");
    char ch;

    int lineCount = 1;
    char lineCountBuffer[MAX];
    bool lineNumberPrinted = false;

    while( (ch = fgetc(fpRead)) != EOF)
    {
        if(!lineNumberPrinted)
        {
            itoa(lineCount,lineCountBuffer,10);
            fputs(lineCountBuffer,fpWrite);
            fputs(" ",fpWrite);
            lineNumberPrinted = true;
        }
        if(ch == '\n')
        {
            fputc(ch,fpWrite);
            lineCount++;
            lineNumberPrinted = false;
        }
        else
        {
            fputc(ch,fpWrite);
        }

    }

    fclose(fpRead);
    fclose(fpWrite);
}


void createSymbolTable()
{
    fpRead = fopen("input3.txt","r");
    char dataTypeBuffer[MAX];
    char scope[MAX];
    char type[MAX] ;
    char funcName[MAX];
    char ch;
    char buffer[MAX];
    
    int j = 0;

    bool isInsideFunction = false;
    bool legit = false;

    while( (ch = fgetc(fpRead)) != EOF)
    {
        if(ch == '[')
        {
            while( (ch = fgetc(fpRead)) != EOF)
            {
                if(ch != ']' && ch != '[')
                {
                    buffer[j++] = ch;
                }

                else
                {
                    buffer[j] = '\0';
                    j = 0;
                    if(strcmp("int",buffer) == 0 || strcmp("float",buffer) == 0 || strcmp("double",buffer) == 0)
                    {
                        strcpy(dataTypeBuffer,buffer);

                        char temp[MAX];
                        int t = 0;
                        while( (ch = fgetc(fpRead)) != EOF)
                        {
                            if(ch != ']')
                            {
                                temp[t++] = ch;
                            }
                            else
                            {

                                temp[t] = '\0';
                                t = 0;
                                int len = strlen(temp);
                                int i = 0;
                                char name[MAX];
                                int nameIndex = 0;
                                for(i = 4; i < len; i++)
                                {
                                    name[nameIndex++] = temp[i];
                                }
                                name[nameIndex] = '\0';
                                nameIndex = 0;

                                //printf("\nNaam hocche:%s\n",name);
                                //printf("length hocche:%d\n",strlen(name));

                                if(strlen(name) > 0)
                                {
                                    strcpy(symbolTable[tableCount].name,name);
                                }
                                ch = fgetc(fpRead);
                                ch = fgetc(fpRead);


                                if(ch == '(')
                                {
                                    strcpy(scope,"global");
                                    strcpy(type,"func");
                                    if(strlen(name) > 0)
                                    {

                                        strcpy(symbolTable[tableCount].scope,scope);
                                        strcpy(symbolTable[tableCount].type,type);
                                        strcpy(symbolTable[tableCount].dataType,dataTypeBuffer);
                                    }

                                    strcpy(funcName,name);
                                    isInsideFunction = true;

                                }
                                else if(ch == '}')
                                {
                                    strcpy(scope,"global");
                                    isInsideFunction = false;
                                }
                                else
                                {

                                    strcpy(type,"var");
                                    if(strlen(name) > 0)
                                    {
                                        strcpy(symbolTable[tableCount].type,type);
                                        strcpy(symbolTable[tableCount].dataType,dataTypeBuffer);
                                    }

                                    if(isInsideFunction)
                                    {
                                        if(strlen(name) > 0)
                                        {
                                            strcpy(symbolTable[tableCount].scope,funcName);
                                        }
                                    }
                                    else
                                    {
                                        if(strlen(name) > 0)
                                        {
                                            strcpy(symbolTable[tableCount].scope,"global");
                                        }
                                    }

                                    if(strlen(name) > 0)
                                    {
                                        strcpy(symbolTable[tableCount].type,type);
                                        strcpy(symbolTable[tableCount].dataType,dataTypeBuffer);
                                    }

                                }

                                if(strlen(name) > 0)
                                {

                                    int temp = tableCount + 1;
                                    char tempIndex[MAX];
                                    itoa(temp,tempIndex,10);
                                    strcpy(symbolTable[tableCount].index,tempIndex);
                                    tableCount++;
                                }

                                break;
                            }
                        }
                    }
                }
            }

        }

    }

    fclose(fpRead);
}

void displaySymbolTable()
{
    printf("\n");
    printf("\t\t\t\tSymbol Table:\n\n");

    int i = 0;
    for(i = 0; i < tableCount; i++)
    {

        printf("%s\t\t",symbolTable[i].index);
        printf("%s\t\t",symbolTable[i].type);
        printf("%s\t\t",symbolTable[i].name);
        printf("%s\t\t",symbolTable[i].dataType);
        printf("%s",symbolTable[i].scope);
        printf("\n");

    }

}

void displayIntermediateFile()
{
    printf("Intermediate File:\n\n");
    fpRead = fopen("intermediate.txt","r");
    char ch;
    while( (ch = fgetc(fpRead)) != EOF)
    {
        printf("%c",ch);
    }

    fclose(fpRead);
}

void detectErrors()
{
    printf("\n\n");
    printf("Types of Detected Errors:\n\n");

    fpRead = fopen("intermediate.txt","r");

    char ch;
    char buffer[MAX];
    char previousBuffer[MAX];
    char lineCountBuffer[MAX];

    int tokenCount = 1;
    int j = 0;
    int l = 0;

    bool ifFound = false;
    bool duplicatePrinted = false;
    bool openingBraceFound = false;
    bool closingBraceFound = false;
    bool bracePrinted = false;

    strcpy(previousBuffer,"NULL");

    while( (ch = fgetc(fpRead)) != EOF)
    {

        if(ch == '\n')
        {
            tokenCount = 1;
            duplicatePrinted = false;
        }

        else if(ch != ' ')
        {
            buffer[j++] = ch;
        }
        else
        {
            buffer[j] = '\0';
            j = 0;
            if(tokenCount == 1)
            {
                strcpy(lineCountBuffer,buffer);
            }

            tokenCount++;
             //printf("\nValue of buffer:%s\n",buffer);
             //printf("\nValue of previous buffer:%s\n",previousBuffer);
             //strcpy(previousBuffer,buffer);

            if(strcmp(buffer,previousBuffer) == 0 && !duplicatePrinted)
            {
                printf("Duplicate token at line: %s\n",lineCountBuffer);
                duplicatePrinted = true;
            }

            strcpy(previousBuffer,buffer);

            

            if(strcmp(buffer,"if") == 0)
            {
                //printf("If found!");
                ifFound = true;
            }

            else if(strcmp(buffer,"else") == 0)
            {
                //printf("ei porjonto ashlo\n");
                //printf("value of ifFound:%d\n",ifFound);
                if(!ifFound)
                {
                    printf("Unmatched else at line: %s\n",lineCountBuffer);
                    
                }
                ifFound = false;
            }

            if(strcmp(buffer,"{") == 0)
            {
                if(!closingBraceFound)
                {
                    openingBraceFound = true;
                }
                bracePrinted = false;
            }

            else if(strcmp(buffer,"}") == 0)
            {
            
                closingBraceFound = true;
                openingBraceFound = false;
                if(!bracePrinted)
                {
                    printf("Misplaced '}' at line: %s\n",lineCountBuffer);
                    bracePrinted = true;
                }
            }

            if(strcmp(buffer,"id") == 0)
            {
                char identifier[MAX];
                while( (ch = fgetc(fpRead)) != EOF)
                {
                    if(ch != ' ')
                    {
                        buffer[j++] = ch;
                    }
                    else
                    {
                        buffer[j] = '\0';
                        j = 0;
                        //printf("\nvalue of id:%s\n",buffer);
                        
                        int i = 0;
                        int sameIdOccurence = 0;
                        bool isIdentifierValid = false;
                        bool checkRedeclaration = false;
                        char tempScope[MAX];

                        for(i = 0; i < tableCount;i++)
                        {
                            if(strcmp(symbolTable[i].name,buffer) == 0)
                            {
                                checkRedeclaration = true;
                                strcpy(tempScope,symbolTable[i].scope);
                                int j = 0;
                                for(j = 0; j < tableCount; j++)
                                {
                                    if(strcmp(buffer,symbolTable[j].name) == 0 && strcmp(tempScope,symbolTable[j].scope) == 0)
                                    {
                                        sameIdOccurence++;
                                    }

                                }
                                if(sameIdOccurence > 1)
                                {
                                    isIdentifierValid = false;
                                }
                                else
                                {
                                    isIdentifierValid = true;
                                }
                                break;
                            }
                        }

                        if(!isIdentifierValid)
                        {
                            printf("Invalid identifier at line: %s\n",lineCountBuffer);
                        }

                        break;
                    }
                }
            }
        }
    }

    fclose(fpRead);
}

int main()
{
    trimSourceFile();
    recongniseLexemes(); 
    createSymbolTable(); 
    prepareIntermediateFile();
    displayIntermediateFile();
    detectErrors();

    return 0;
}


