#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct UnionType
{
	char sign;
	int num;
} ElementType;

typedef struct StackType//栈元素定义
{
	ElementType data;
	struct StructType* next;
} StackNode;

void InitStack(StackNode** head, StackNode** top)//初始化栈
{
	*head = (StackNode*)malloc(sizeof(StackNode));	
	*top = NULL;
}

bool StackEmpty(StackNode* top)//判断栈是否为空
{
	if(top == NULL)
		return true;
	else 
		return false; 	
}

void StackPush(StackNode* head, StackNode** top, ElementType newData)//压入栈
{
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));	
	if(newData->sign == '\0')
	{
		newNode->data.num = newData.num;
	}
	else 
	{
		newNode->data.sign = newData.sign;
	}
	newNode->next = head->next;//头插法
	head->next = newNode;
	*top = head->next;//更新栈顶指针
}

ElementType StackPeek(StackNode* top)//查看栈顶元素
{
	if(!StackEmpty(top))//判断栈是否为空
	{
		return top->data;	
	}
	else 
	{
		printf("Stack is empty!")
	}
}

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
		if(infix[i].sign == '\0')//该位数据为数字
		{
			printf("%d",infix[i].num);	
		}
		else//该位数据为运算符
		{
			printf(" %c ",infix[i].sign);
		}
	}

}

void InfixToSuffix(ElementType* infix, ElementType* suffix)
{

}

int GetResult(ElementType* suffix,int len,int res)
{

}

int main()
{
	char input[20] = {0};
	int len = 0;
	int res = 0;
	ElementType infix[20] = {0};
	ElementType suffix[20] = {0};
	fgets(input,20,stdin);
	len = ArrayToInfix(input,infix);
	PrintInfix(infix,len);
}
