#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct TreeNode
{
	char Element;
	TreeNode* Right;
	TreeNode* Left;
	TreeNode()
	{
		Element = 0;
		Right = NULL;
		Right = NULL;
	}
}

int main()
{
	int i = 0;
	char input[20] = {0};
	int infix[20] = {0};
	int suffix[20] = {0};
	fgets(input,20,stdin);
	while(input[i] != '\0')
	{
		while(input[i] >= '0' && input[i] <= '9')
		{
			int value = 0;
			value = value*10 + atoi(input[i]);		
		}	
	}
}
