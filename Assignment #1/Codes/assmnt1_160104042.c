/**
 * Author:    Syed Sanzam
 * Subject:   File Trimming
 * Created:   7.14.2019
 * 
 **/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fpRead;
	FILE *fpWrite;

	fpRead = fopen("input1_160104042.c","r");
	fpWrite = fopen("output.txt","w");

	char c;

	while( (c = fgetc(fpRead)) != EOF)
	{
		//Single Line Comment Check
		if(c == '\n')
		{
			fputc(' ',fpWrite);
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
						break;
				}

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
				}
			}
		}
			//Whitespace Check
		else if(c == ' ')
		{
			//If Character after space is a Parenthesis
			char b; 

			//Spaces found after a 'singular space'
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
			if(c != '\t' && c != '\n')
			fputc(c,fpWrite);
		
		}
	}

	fclose(fpRead);
	fclose(fpWrite);




	//Print Both Files on the Console

	FILE *fOut1;
	FILE *fOut2;

	fOut1 = fopen("input1_160104042.c","r");
	fOut2 = fopen("output.txt","r");

	char x;
	char y;

	printf("\nContents of input.c\n");
	while( (x = fgetc(fOut1)) != EOF)
	{
		printf("%c",x);
	}

	printf("\n\nContents of output.txt\n");

	while( (y = fgetc(fOut2)) != EOF)
	{
		printf("%c",y);
	}

	printf("\n\n");

	fclose(fOut1);
	fclose(fOut2);


	return 0;


}