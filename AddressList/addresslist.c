#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "addresslist.h"

// 主函数
int main(int argc, char *argv[])
{
    // 初始化链表及命令
	LinkList head = NULL;
	char cmd = '\0';

    // 初始化链表
	Init(&head);
    
    // 从文件中加载链表
	Load(head);
    
    // 进入到操作菜单
	Menu(&cmd, head);

	return 0;
}

// 打印帮助信息
void PrintHelp() {
	printf("-----------------------------------------------------\n");
	printf("\t\t\tAddressList System\t\t\t\n");
	printf("\n");
	printf("\t\t\t1.Search Contact\n");
	printf("\t\t\t2.New Contact\n");
	printf("\t\t\t3.Update Contact\n");
	printf("\t\t\t4.Delete Contact\n");
	printf("\t\t\t5.Exit\n");
	printf("-----------------------------------------------------\n");    
}

// 菜单
int Menu(char *cmd, LinkList head)
{
    
    // 进入到程序主循环
    while(1) {
        
        // 打印帮助信息
        PrintHelp();

        // 输入操作命令
        *cmd = getchar();
        printf("cmd = %c\n", *cmd);
        
        // 清空标准输入缓存
        setbuf(stdin, NULL);
        
        // 清空屏幕
        system("clear");
        
        // 列出所有联系人 
        List(head);
        
        // 根据输入操作
        switch (*cmd) {
            
            // 查询联系人
            case '1': 
                Search(head); 
                break;
            
            // 添加联系人并保存到文件
            case '2': 
                New(head); 
                Save(head); 
                break;
            
            // 更新联系人并保存到文件
            case '3': 
                Update(head); 
                Save(head);
                break;
            
            // 删除联系人并保存到文件
            case '4': 
                Remove(head);
                Save(head);
                break;
            
            // 退出系统
            case '5':
                exit(0);
            
            
            default : 
                printf("Input Error. Try Again\n");
                continue;
        }
        
        getchar();
    
    }

	return 0;
}

// 初始化联系人链表
int Init(LinkList *head)
{
    // 为链表第一个节点分配内容空间
	*head = (LinkList)malloc(sizeof(Node));

    // 初始化第一个节点的电话为空
	strcpy((*head)->number,"\0");

    // 初始化第一个节点的名字为空
	strcpy((*head)->name,"\0");
    
    // 设置第一个节点的next指针指向NULL，表示这也是最后一个节点
	(*head)->next = NULL;

	return 0;
}

// 增加新的联系人
int New(LinkList head)
{
    
    // 创建新节点
	Node *newnode = NULL;	

    // 为新节点分配内存
	if (!(newnode = (Node *)malloc(sizeof(Node)))) {
		perror("malloc");
	}

    // 输入新节点所需的信息
	printf("Input Contact Name:\n");
	scanf("%s", newnode->name);
	printf("Input Contact Number:\n");
	scanf("%s", newnode->number);

	// 将新节点插入到链表的头节点后
    // 头节点指针指向新节点，新节点指针指向
	newnode->next = head->next;
	head->next = newnode;

	return 0;
}

// 删除联系人
int Remove(LinkList head)
{
    // 首先获取目标联系人的名字
	char d_name[MAX_NAME_LEN];
    
	Node *cur = NULL;
	Node *pre = NULL;
	
    // 列出所有联系人的信息
    List(head);
    
    // 输入联系人名字
	printf("Input Contact Name:\n");
	scanf("%s", d_name);
	
    // 遍历链表查找目标联系人
	cur = head->next;
    
    // 需要记录节点的前一节点，当删除后仍然能够维护链表
	pre = head;
    
    // 遍历链表
	while (cur != NULL) {
        
        // 比较节点的名字和目标名字是否一致
		if (0 == (strcmp(d_name, cur->name))) {
            
            // 删除节点的信息
			printf("Remove Contact :%s Number:%s\n", cur->name, cur->number);
            
            // 将删除节点前节点的next指针指向后节点
			pre->next = cur->next;
            
            // 释放删除节点的内存
			free(cur);
            
            return 0;
		}
        
        // 继续遍历
		pre = pre->next;
		cur = cur->next;
	}

	printf("Remove Successfully!\n");

	return 0;
}



// 更新联系人
int Update(LinkList head)
{
    // 首先获取目标联系人的名字
	Node *cur = NULL;
	char m_name[MAX_NAME_LEN];	

	printf("Input Contact Name:\n");
	scanf("%s", m_name);

    // 遍历链表查找目标联系人
	cur = head->next;
	while (cur != NULL) {
        
        // 比较节点的名字和目标名字是否一致
		if (0 == (strcmp(m_name, cur->name))) {
			printf("Input New Name:");
			scanf("%s", cur->name);
			printf("Input New Number:");
			scanf("%s", cur->number);
			printf("Update Successfully!\n");

			return 0;
		}
		cur = cur->next;
	}

    // 没有找到联系人信息
	printf("NOT FOUND:%s\n", m_name);

	return 0;
}

// 查找联系人：可以根据名字及号码查找
int Search(LinkList head)
{
    // 首先获取目标联系人的名字
	Node *cur = NULL;
	char q_name[MAX_NAME_LEN];

	printf("Input Contact Name or Number:\n");
	scanf("%s", q_name);
    
    // 遍历链表查找目标联系人
	cur = head->next;
	while (cur != NULL) {
        
        // 比较节点和目标信息是否一致
		if ((0 == strcmp(q_name, cur->name)) || (0 == strcmp(q_name, cur->number))) {
			printf("Found Contact:\n");
			printf("\tName\t\tNumber\n");
			printf("\t%s\t\t%s\n", cur->name, cur->number);
			return 0;
		}
		cur = cur->next;
	}
	
	printf("NOT FOUND!\n");

	return 0;
}


// 从文件中加载通讯录
int Load(LinkList head)
{
	FILE *r_file = NULL;
	Node *newnode = NULL;

    // 打开数据文件
	r_file = fopen(DATA_FILE, "rt");
	if (!r_file) {
        // 如果文件不存在则创建文件
		perror("fopen");
		r_file = fopen(DATA_FILE, "wt");
		fclose(r_file);
		return 0;
	}
	
    
	// 循环读取文件内容
	while (!feof(r_file)) {
        
        // 创建新节点
		if (!(newnode = (Node *)malloc(sizeof(Node)))) {
			perror("malloc");
			exit(-1);
		}
        
        // 格式化读取文件内容
		fscanf(r_file, "%s\t%s\n", newnode->name, newnode->number);
		printf("Read Data:%s\t%s...\n", newnode->name, newnode->number);
        
        // 将新节点加入到链表
		newnode->next = head->next;
		head->next = newnode;
	}
    

	printf("Load Successfully!\n");

	fclose(r_file);

	return 0;
}

// 把通讯录保存到文件中
int Save(LinkList head)
{
	Node *cur = NULL;
	FILE *w_file = NULL;

    // 打开当前目录文件
	w_file = fopen(DATA_FILE, "wt");
    
	if (!w_file) {
		perror("fopen");
		exit(-1);
	}

    // 遍历链表依次将节点数据写入文件
	cur = head->next;
	while (cur != NULL) {
		fprintf(w_file, "%s\t%s\n", cur->name, cur->number);
		printf("Write Data: %s\t%s...\n", cur->name, cur->number);
		cur = cur->next;
	}
	
	printf("Saved Successfully!\n");

	return 0;
}


// 列出所有的联系人
int List(LinkList head)
{
    // 遍历节点打印所有联系人的姓名及号码
	Node *cur = NULL;
	
	printf("\tName\t\t\tNumber\n");
	
    // 开始遍历
	cur = head->next;
	while (cur != NULL) {
		printf("\t%s\t\t%s\n", cur->name, cur->number);	
		cur = cur->next;
	}

	return 0;
}
