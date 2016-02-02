#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
//#include <string.h>

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
	//memset(head, 0, sizeof(StackNode));
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
	StackNode* newNode = (StackNode*)calloc(1,sizeof(StackNode));	
	//memset(newNode, 0, sizeof(StackNode)-1);
	if(newData.sign == '\0')
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
		printf("Stack is empty!");
	}
}

ElementType StackPop(StackNode* head,StackNode** top)//出栈
{
    if(!StackEmpty(*top))
    {
        ElementType popData;
        if((*top)->data.sign == '\0')
        {
            popData.num = (*top)->data.num;
        }
        else
        {
            popData.sign = (*top)->data.sign;
        }
        head->next = (*top)->next;
	    (*top)->next = NULL;
	    free(*top);
        *top = head->next;
        return popData;
    }
    else
    {
        printf("Stack is empty!");
    }
}

void PrintStack(StackNode* head)//打印栈
{
	StackNode* ptr = head;
	printf("HEAD->");
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		if (ptr->data.sign == '\0')
		{
			printf("%d->", ptr->data.num);
		}
		else
		{
			printf("%c->", ptr->data.sign);
		}	
	}
	printf("NULL\n");
}

int ArrayToInfix(char* input, ElementType* infix)//输入字符串转为中缀表达式
{
	int i = 0;
	int j = 0;
    int value = 0;
	while(input[i] != '\n')
	{
		if (input[i] >= '0' && input[i] <= '9')
		{
			while (input[i] >= '0' && input[i] <= '9')
			{
				value = value * 10 + (input[i] - '0');
				i++;			
			}	
			infix[j++].num = value;
			value = 0;
		}
		if(input[i] != '\n')
		{
			infix[j++].sign = input[i];
			i++;
		}
	}
	infix[j].sign = '\0';
	return j;
}

void PrintFormula(ElementType* formula,int len)//打印表达式
{
	int i = 0;
	if (formula == NULL)
		return ;
	for(i = 0;i < len;++i)
	{
		if (formula[i].sign == '\0')//该位数据为数字
		{
			printf("%d", formula[i].num);	
		}
		else//该位数据为运算符
		{
			printf("%c", formula[i].sign);
		}
	}
	printf("\n");
}

int InfixToSuffix(ElementType* infix, ElementType* suffix,int len)//中缀表达式转为后缀表达式
{
	int i = 0;
	int j = 0;
	StackNode* sign_head;
	StackNode* sign_top;
	InitStack(&sign_head,&sign_top);
	for (i = 0; i < len; ++i)
	{
		if (infix[i].sign == '\0')//中缀读到数字
		{
			suffix[j++].num = infix[i].num;
		}
		else//中缀读到符号
		{
			if (StackEmpty(sign_top))//符号栈为空
			{
				StackPush(sign_head, &sign_top, infix[i]);
			}
			else if (infix[i].sign == '(')//中缀读到'('
			{
				StackPush(sign_head, &sign_top, infix[i]);
			}
			else if (infix[i].sign == ')')//中缀读到')'
			{
				while (StackPeek(sign_top).sign != '(' && !StackEmpty(sign_top))
				{
					suffix[j++] = StackPop(sign_head, &sign_top);
				}
				if (StackPeek(sign_top).sign == '(' && !StackEmpty(sign_top))
				{
					StackPop(sign_head, &sign_top);
				}
			}
			else if (infix[i].sign == '+' || infix[i].sign == '-')
			{
				ElementType temp;
				temp = StackPeek(sign_top);
				if (temp.sign == '*' || temp.sign == '/')
				{
					while (!StackEmpty(sign_top) && StackPeek(sign_top).sign != '(')
					{
						suffix[j++] = StackPop(sign_head, &sign_top);
					}
					StackPush(sign_head, &sign_top, infix[i]);
				}
				else
				{
					StackPush(sign_head, &sign_top, infix[i]);
				}
			}
			else
			{
				StackPush(sign_head, &sign_top, infix[i]);
			}
		}
	}
	while (!StackEmpty(sign_top))
	{
		suffix[j++] = StackPop(sign_head, &sign_top);
	}
	free(sign_head);
	return j;
}

int GetResult(ElementType* suffix,int len)//由后缀表达式计算出值
{
	int i = 0;
	char sign = '\0';
	int val1 = 0;
	int val2 = 0;
	int res = 0;
	ElementType temp;
	StackNode* head;
	StackNode* top;
	temp.sign = '\0';
	InitStack(&head, &top);
	for (i = 0; i < len; ++i)
	{
		if (suffix[i].sign == '\0')
		{
			StackPush(head, &top, suffix[i]);
		}
		else
		{
			sign = suffix[i].sign;
			val1 = StackPop(head, &top).num;
			val2 = StackPop(head, &top).num;
			switch (sign)
			{
				case '+':temp.num = val2 + val1; break;
				case '-':temp.num = val2 - val1; break;
				case '*':temp.num = val2 * val1; break;
				case '/':temp.num = val2 / val1; break;
			}
			StackPush(head,&top,temp);
		}
	}
	res = StackPop(head, &top).num;
	return res;
}

int main()
{
	char input[20] = {0};
	int len = 0;
	int res = 0;
	int i = 0;
	int j = 0;
	ElementType infix[20] = {0};
	ElementType suffix[20] = {0};
	
	//StackNode* infix_head;
	//StackNode* top;
	
	fgets(input,20,stdin);
	len = ArrayToInfix(input,infix);
	//PrintFormula(infix, len);
	len = InfixToSuffix(infix,suffix,len);
	//PrintFormula(suffix, len);
	res = GetResult(suffix,len);
	printf("= %d\n", res);
	//PrintInfix(infix,len);
	/*InitStack(&infix_head, &top);
	for (i = 0; i < len; ++i)
	{
		StackPush(infix_head,&top,infix[i]);
	}
	PrintStack(infix_head);*/
	
}
