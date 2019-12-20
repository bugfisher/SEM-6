/*
 ============================================================================
 Name        : conversion.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>

void createMOT();
void createROT();
void conv();

int main(void)
{
	int ch;
	printf("1.Create new MOT file\n");
	printf("2.Add new ROT file\n");
	printf("3.Enter Assembly Language\n");
	scanf("%d",&ch);
	switch(ch)
	{
	case 1:
		createMOT();
		break;
	case 2:
		createROT();
		break;
	case 3:
		conv();
		break;
	default:
		printf("Enter appropriate option\n");
		break;
	}


	return EXIT_SUCCESS;
}

void createMOT()
{
	FILE *f;
	f = fopen("mot.txt","w");
	char m[20],o[20];
	int check=1;

	do
	{
	printf("Enter Mnemonic:");
	scanf("%s",m);
	printf("\nEnter opcode:");
	scanf("%s",o);
	fprintf(f,"Mnemonic:%s\tOpcode:%s\n",m,o);
	printf("Press 0 to finish creation or 1 to continue\n");
	scanf("%d",&check);
	}while(check != 0);

	fclose(f);
}

void createROT()
{
	FILE *f;
	f = fopen("rot.txt","w");
	char r[20],o[20];
	int check=1;

	do
	{
	printf("Enter REGISTER:");
	scanf("%s",r);
	printf("\nEnter opcode:");
	scanf("%s",o);
	fprintf(f,"REGISTER:%s\tOpcode:%s\n",r,o);
	printf("Press 0 to finish creation or 1 to continue\n");
	scanf("%d",&check);
	}while(check != 0);

	fclose(f);
}

void conv()
{
	char m[20],op1[20],op2[20];
	char m1[20],o[20];
	char r[20],o1[20];
	printf("Enter the Instruction\n");
	scanf("%s",m);
	scanf("%s",op1);
	scanf("%s",op2);

	int i=0,flag=0;




		FILE *f;
		f = fopen("mot.txt","r");

		while( fscanf(f,"Mnemonic:%s\tOpcode:%s\n",m1,o) != EOF )
		    {
				if(strcmp(m,m1) == 0)
				{
					printf("%s\t",o);
					flag=1;
				}

		    }
		fclose(f);
		flag=0;

		FILE *ff;
		ff = fopen("rot.txt","r");

		while( fscanf(ff,"REGISTER:%s\tOpcode:%s\n",r,o1) != EOF )
			{
				if(strcmp(r,op1) == 0)
				{
					printf("%s\t",o1);
					flag=1;
				}

			}
		fclose(ff);

		printf("%s\n",op2);

		if(flag==0)
		{
			printf("Invalid Instruction\n");
		}







}




