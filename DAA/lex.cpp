//============================================================================
// Name        : lex.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<string.h>
using namespace std;

class op_table
{
public:
	char o[30];
	int line;

};

class keyword_table
{
public:
	string keyword;
	int line;
};

class identifier_table
{
public:
	string  identifier;
	int line;
};

bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}


bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=')
        return (true);
    return (false);
}


char* subString(char* str, int left, int right)
{
    int i;
    char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));

    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];


    subStr[right - left + 1] = '\0';
    return (subStr);
}

bool validIdentifier(char* str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isDelimiter(str[0]) == true)
        return (false);
    return (true);
}


bool isKeyword(char* str)
{
    if (!strcmp(str, "if") || !strcmp(str, "else") ||
        !strcmp(str, "while") || !strcmp(str, "do") ||
        !strcmp(str, "break") ||
         !strcmp(str, "continue") || !strcmp(str, "int")
        || !strcmp(str, "double") || !strcmp(str, "float")
        || !strcmp(str, "return") || !strcmp(str, "char")
        || !strcmp(str, "case") || !strcmp(str, "char")
        || !strcmp(str, "sizeof") || !strcmp(str, "long")
        || !strcmp(str, "short") || !strcmp(str, "typedef")
        || !strcmp(str, "switch") || !strcmp(str, "unsigned")
        || !strcmp(str, "void") || !strcmp(str, "static")
        || !strcmp(str, "struct") || !strcmp(str, "goto"))
        return (true);
    return (false);
}


void parse_string(char* s)
{
	int len = strlen(s);

	int left=0;
	int right=0;

	op_table op[20];
	int op_length=0;



	while(left<=right && right<=len)
	{

		if(isDelimiter(s[right]) == false)
		{
			right++;
		}

		if(isDelimiter(s[right]) == true && left==right)
		{
			if(isOperator(s[right]) == true)
				cout<<s[right]<<"is a operator"<<endl;

			right++;
			left=right;

		}
		else if( (isDelimiter(s[right]) == true && left !=right) || (right == len && left!=right))
		{

			char* subStr = subString(s, left, right - 1);
			if (isKeyword(subStr) == true)
			{
			   printf("'%s' IS A KEYWORD\n", subStr);
			}
			else if (validIdentifier(subStr) == true  && isDelimiter(s[right - 1]) == false)
			{
			   printf("'%s' IS A VALID IDENTIFIER\n", subStr);
			}
			else if (validIdentifier(subStr) == false && isDelimiter(s[right - 1]) == false)
			{
			   printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
			}
			 left = right;



		}

	}


}

int main()
{
	char str[100] = "int a = b + 1c; ";

	    parse_string(str); // calling the parse function

	   return 0;

}
