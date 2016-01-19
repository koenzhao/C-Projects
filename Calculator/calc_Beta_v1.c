#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct UnionType
{
	char sign;
	int num;
} ElementType;

int ArrayToInfix(char* input, ElementType* infix)
{
	int i = 0;
	int j = 0;
	int value = 0;
	while(input[i] != '\0')
	{
		while(input[i] >= '0' && input[i] <= '9')
		{
			value = value * 10 + (input[i] - '0');
			i++;			
		}	
		infix[j++].num = value;
		value = 0;
		if(input[i] != '\0')
		{
			infix[j++].sign = input[i];
			i++;
		}
	}
	infix[j].sign = '\0';
	return j;
}

void PrintInfix(ElementType* infix,int len)
{
	int i = 0;
	if(infix == NULL)
		return ;
	for(i = 0;i < len;++i)
	{
		if(infix[i].sign == '\0')
		{
			printf("%d",infix[i].num);	
		}
		else
		{
			printf(" %c ",infix[i].sign);
		}
	}

}

void InfixToSuffix(ElementType* infix, ElementType* suffix)
{

}

int main()
{
	char input[20] = {0};
	int lenOfInfix = 0;
	ElementType infix[20] = {0};
	ElementType suffix[20] = {0};
	fgets(input,20,stdin);
	lenOfInfix = ArrayToInfix(input,infix);
	PrintInfix(infix,lenOfInfix);
}
