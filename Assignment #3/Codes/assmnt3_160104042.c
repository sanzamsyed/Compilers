/*
**AUTHOR:Syed Sanzam
**Date: August 27, 2019
**Code Condition: Not great, not terrible

*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 100

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
FILE *fpRead;
FILE *fpWrite;

void recogniseLexemes()
{
    fpRead = fopen("sessioninput.txt","r");
    fpWrite = fopen("output.txt","w");

    char ch;
    char buffer[MAX];
    int j = 0;

    while( (ch = fgetc(fpRead)) != EOF)
    {
        if(ch == '[')
        {
            fputc(ch,fpWrite);

            while( (ch = fgetc(fpRead)) != EOF)
            {
                if(ch != ' ')
                {
                    buffer[j++] = ch;
                }
                else
                {
                    buffer[j] = ' ';
                    buffer[j+1] = '\0';
                    j = 0;
                    if(strcmp("id ",buffer) == 0)
                    {
                        fputc('i',fpWrite);
                        fputc('d',fpWrite);
                        fputc(' ',fpWrite);
                    }

                    break;
                }
            }

        }

        else if(ch != ' ')
        {
            fputc(ch,fpWrite);
        }
    }

    fclose(fpRead);
    fclose(fpWrite);
}

void createSymbolTable()
{

    fpRead = fopen("output.txt","r");
    char dataTypeBuffer[MAX];
    char scope[MAX];
    char type[MAX] ;
    char funcName[MAX];
    char ch;
    char buffer[MAX];
    bool isInsideFunction = false;
    int j = 0;

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

                                strcpy(symbolTable[tableCount].name,name);
                                ch = fgetc(fpRead);
                                ch = fgetc(fpRead);

                                if(ch == '(')
                                {
                                    strcpy(scope,"global");
                                    strcpy(type,"func");
                                    strcpy(symbolTable[tableCount].scope,scope);
                                    strcpy(symbolTable[tableCount].type,type);
                                    strcpy(symbolTable[tableCount].dataType,dataTypeBuffer);
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
                                    strcpy(symbolTable[tableCount].type,type);
                                    strcpy(symbolTable[tableCount].dataType,dataTypeBuffer);

                                    if(isInsideFunction)
                                    {
                                        strcpy(symbolTable[tableCount].scope,funcName);
                                    }
                                    else
                                    {
                                        strcpy(symbolTable[tableCount].scope,"global");
                                    }

                                    strcpy(symbolTable[tableCount].type,type);
                                    strcpy(symbolTable[tableCount].dataType,dataTypeBuffer);

                                }

                                int temp = tableCount + 1;
                                char tempIndex[MAX];
                                itoa(temp,tempIndex,10);
                                strcpy(symbolTable[tableCount].index,tempIndex);
                                tableCount++;
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


void getIndexFromSymbolTable()
{
    printf("\n");
    fpRead = fopen("output.txt","r");
    char ch;
    char buffer[MAX];
    char scope[MAX];
    char funcName[MAX];
    int j = 0;
    char dataType[MAX];

    bool isInsideFunction = false;
    bool prevBraceFound = false;

    strcpy(scope,"global");

    while( (ch = fgetc(fpRead)) != EOF)
    {
        if(ch == '[')
        {

            printf("%c",ch);



            ch = fgetc(fpRead);
            printf("%c",ch);

            if(ch == '{')
            {
                prevBraceFound = true;
            }

            if(ch == '}')
            {
                isInsideFunction = false;
                strcpy(scope,"global");
                prevBraceFound = false;
            }

            buffer[j++] = ch;
            ch = fgetc(fpRead);
            printf("%c",ch);
            buffer[j++] = ch;
            buffer[j] = '\0';
            j = 0;

            if(strcmp(buffer,"id") == 0)
            {
                printf(" ");
                while( (ch = fgetc(fpRead)) != EOF)
                {
                    if(ch != ']')
                    {
                        if(ch != ' ')
                            buffer[j++] = ch;
                    }
                    if(ch == ']')
                    {

                        buffer[j] = '\0';

                        if(isInsideFunction)
                        {
                            strcpy(scope,funcName);
                        }

                        int i = 0;
                        for(i = 0; i < tableCount; i++)
                        {
                            if(strcmp(symbolTable[i].name, buffer) == 0)
                            {
                                if( strcmp(symbolTable[i].scope,scope) == 0 ||  strcmp(symbolTable[i].scope,"global") == 0 )
                                    printf("%s", symbolTable[i].index);
                            }
                        }
                        printf("%c",ch);

                        char tempChar1;
                        char tempChar2;

                        tempChar1 = fgetc(fpRead);
                        tempChar2 = fgetc(fpRead);


                        if(tempChar2 == '(')
                        {
                            isInsideFunction = true;
                            if(!prevBraceFound)
                            strcpy(funcName,buffer);
                            //printf("\nfunction paisi!:%s\n",funcName);
                        }

                        ungetc(tempChar2,fpRead);
                        ungetc(tempChar1,fpRead);

                        break;

                    }
                }
            }

        }
        else
            printf("%c",ch);
    }
}



void insert(char *dataType, char *name, char *type, char *scope)
{
    int temp = tableCount + 1;
    char tempIndex[MAX];
    itoa(temp,tempIndex,10);

    strcpy(symbolTable[tableCount].index,tempIndex);
    strcpy(symbolTable[tableCount].dataType,dataType);
    strcpy(symbolTable[tableCount].name,name);
    strcpy(symbolTable[tableCount].type,type);
    strcpy(symbolTable[tableCount].scope,scope);

    tableCount++;

}

void del(int position)
{
    int index = position - 1;
    int i = 0;
    for(int i = 0; i < tableCount-1; i++)
    {
        if(i >= index)
        {
            strcpy(symbolTable[i].dataType,symbolTable[i+1].dataType);
            strcpy(symbolTable[i].name,symbolTable[i+1].name);
            strcpy(symbolTable[i].type,symbolTable[i+1].type);
            strcpy(symbolTable[i].scope,symbolTable[i+1].scope);

        }
    }

    tableCount--;
}


void search(char *dataType, char *name, char *type, char *scope)
{
    int i = 0;
    bool found = false;

    for(i = 0; i < tableCount; i++)
    {
        if(strcmp(symbolTable[i].dataType,dataType) == 0 && strcmp(symbolTable[i].name,name) == 0 && strcmp(symbolTable[i].type,type) == 0 && strcmp(symbolTable[i].scope,scope) == 0)
        {
            found = true;
            break;
        }
    }

    if(found)
    {
        printf("\nEntry found!\n");
        return;
    }
    printf("\nNot found!\n");

}

void update(char *dataType, char *name, char *type, char *scope, char *dt, char *n, char *t, char *s)
{
    int i = 0;
    for(i = 0; i < tableCount; i++)
    {
        if(strcmp(symbolTable[i].dataType,dataType) == 0 && strcmp(symbolTable[i].name,name) == 0 && strcmp(symbolTable[i].type,type) == 0 && strcmp(symbolTable[i].scope,scope) == 0)
        {
            strcpy(symbolTable[i].dataType,dt);
            strcpy(symbolTable[i].name,n);
            strcpy(symbolTable[i].type,t);
            strcpy(symbolTable[i].scope,s);

            break;

        }
    }

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

int main()
{
    /*Step - 1*/
    recogniseLexemes();

    /*Step - 2*/
    createSymbolTable();


    /*Step - 3*/

    /*
    insert("float","arn","func","global");
    insert("float","ani","var","global");
    insert("float","tobeDeleted","var","global");
    update("float","arn","func","global", "double","arnob","func","global");
    search("int","main","func","global");
    del(10);
    displaySymbolTable();
    */


    /*Step - 4 */
    getIndexFromSymbolTable();

    return 0;
}

