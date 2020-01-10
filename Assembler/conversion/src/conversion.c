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
#include <string.h>
#include <ctype.h>

void createMOT();
void createROT();
void conv();

struct ltable
{
	int index;
	char literal[20];
	int address;

};

struct stable
{
	int index;
	char symbol[20];
	int address;
	int length;
};

int main(void)
{
	int ch;
	printf("1.Create new MOT file\n");
	printf("2.Add new ROT file\n");
	printf("3.Start Conversion\n");
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
	char m[20],o[20],type[20];
	int check=1;

	do
	{
	printf("Enter Mnemonic:");
	scanf("%s",m);
	printf("\nEnter opcode:");
	scanf("%s",o);
	printf("\nEnter Type:");
	scanf("%s",type);
	fprintf(f,"Mnemonic:%s\tOpcode:%s\tType:%s\n",m,o,type);
	printf("Press 0 to finish creation or 1 to continue\n");
	scanf("%d",&check);
	}while(check != 0);

	fclose(f);
}

void createROT()
{
	FILE *f;
	f = fopen("rot.txt","w");
	char operand[20],opcode[20],type[20];
	int check=1;

	do
	{
	printf("Enter Operand:");
	scanf("%s",operand);
	printf("\nEnter opcode:");
	scanf("%s",opcode);
	printf("\nEnter type:");
	scanf("%s",type);
	fprintf(f,"Operand:%s\tOpcode:%s\tType:%s\n",operand,opcode,type);
	printf("Press 0 to finish creation or 1 to continue\n");
	scanf("%d",&check);
	}while(check != 0);

	fclose(f);
}

void createins()
{
	FILE *f;
	f = fopen("ins.txt","w");
	char l[20],m[20],op1[20],op2[20];
	int check=1;

	do
	{
	printf("Enter Label:");
	scanf("%s",l);
	printf("\nEnter opcode:");
	scanf("%s",m);
	printf("\nEnter Operand1:");
	scanf("%s",op1);
	printf("\nEnter Operand2:");
	scanf("%s",op2);
	fprintf(f,"%s\t%s\t%s\t%s\n",l,m,op1,op2);
	printf("Press 0 to finish creation or 1 to continue\n");
	scanf("%d",&check);
	}while(check != 0);

	fclose(f);
}

int checkformat(char operand[20])
{
	int i,num=0,alpha=0,equal=0,sq=0,md=0;
	for(i=0;i<strlen(operand);i++)
	{
		if(isdigit(operand[i])!= 0)
		{
			num++;
		}
		else if(isalpha(operand[i])!=0)
		{
			alpha++;
		}

		 if(operand[i] == 61)
		{
			equal++;
		}
		else if(operand[i] == 39)
		{
			sq++;
		}
		 if(i==2)
		 {
		if(isdigit(operand[i])!= 0)
		{
			md++;
		}
		 }
	}

	if(num == strlen(operand))
	{
		return 1;
	}
	else if(alpha == strlen(operand))
	{
		return 2;
	}
	else if(equal == 1 && sq == 2 && md == 1)
	{
		return 3;

	}
	else
	{
		return -1;
	}







}

void conv()
{
	int count = 0;
	int lc=0;
	int category;
	int literalcount=0;
	int symbolcount=0;


	struct ltable lt[20];
	struct stable st[20];


	char m[20],op1[20],op2[20],l[20];
	char m1[20],o[20],type[20];
	char r[20],o1[20],type1[20];

	int i=0,flag=0;

	FILE *ins;
	ins = fopen("ins.txt","r");
	while(fscanf(ins,"%s\t%s\t%s\t%s\n",l,m,op1,op2) != EOF)
	{
		count++;

		//printf("%s\t%s\t%s\t%s\n",l,m,op1,op2);




		FILE *f;
		f = fopen("mot.txt","r");
		//printf("%s\t",l);
		printf("%d\t",lc);
		while( fscanf(f,"Mnemonic:%s\tOpcode:%s\tType:%s\n",m1,o,type) != EOF )
		    {
					if(count == 1)
						{
							if(strcmp(m,"start")!=0)
							{
								printf("START ERROR\n");
							}
							else
							{
								lc = atoi(op1);
							}
						}

				if(strcmp(m,m1) == 0)
				{
					printf("(%s %s)\t",type,o);
					flag=1;
				}


		    }
		fclose(f);
		flag=0;
		if(strcmp(type,"ad") != 0)
		{
			lc++;
		}

		if(strcmp(m,"ltorg")==0)
		{
				i=0;
				while(lt[i].address!=0)
				{
					i++;
				}
				while(i<=literalcount)
				{
					lt[i].address = lc;
					lc++;
					i++;
				}
				printf("\n");

		}


		FILE *ff;
		ff = fopen("rot.txt","r");
		if(strcmp(op1,"-")!=0)
		{

		while( fscanf(ff,"Operand:%s\tOpcode:%s\tType:%s\n",r,o1,type1) != EOF )
			{

				if(strcmp(r,op1) == 0)
				{
					printf("(%s)\t",o1);
					flag=1;
				}


			}

		fclose(ff);
		if(flag ==0 )
		{
			category = checkformat(op1);
			if(category ==1)
			{
				printf("(C,%s)\n",op1);
			}
		}
		}

		flag=0;



		if(flag==0 && strcmp(op2,"-")!=0)
		{
			category=checkformat(op2);

			if(category == 1)
			{
				printf("(C,%s)\n",op2);
			}
			if( category == 3)
			{
				int lflag=0;
				printf("(L,%d)\n",literalcount);

				for(i=0;i<=literalcount;i++)
				{
					if(strcmp(lt[i].literal,op2)==0)
					{
						lflag=1;
					}
				}
				if(lflag==0)
				{

					lt[literalcount].index = literalcount;
					strcpy(lt[literalcount].literal,op2);
					lt[literalcount].address = 0;
					literalcount++;
				}
			}
			if( category == 2)
			{
				printf("(S,%d)\n",symbolcount);
				symbolcount++;
			}
		}



	}

	printf("\n\n");
	printf("\tLiteral Table\n");
	printf("\tIndex\tLiteral\tAddress\n");
	for(i=0;i<literalcount;i++)
	{
		printf("\t%d\t%s\t%d\n",lt[i].index,lt[i].literal,lt[i].address);
	}






}
