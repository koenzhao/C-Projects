#ifndef __ADDRESSLIST_H_
#define __ADDRESSLIST_H_

// 名字的最长字符数
#define MAX_NAME_LEN 32

// 数字最大长度
#define MAX_NUMBER_LEN 32

// 数据文件路径
#define DATA_FILE "/tmp/data.txt"

/* 
    定义联系人结构体contact
    name：名字
    number：手机号码
    next：指向链表的下一个节点
*/
typedef struct contact{
	char name[MAX_NAME_LEN];
	char number[MAX_NUMBER_LEN];
	struct contact *next;
}Node, *LinkList;

// 交互式菜单操作：cmd为输入的命令信息
int Menu(char *cmd, LinkList head);

// 初始化链表
int Init(LinkList *head);

// 创建新的联系人
int New(LinkList head);

// 删除联系人
int Remove(LinkList head);

// 更新联系人
int Update(LinkList head);

// 查找联系人
int Search(LinkList head);

// 从文件中加载通讯录
int Load(LinkList head);

// 把通讯录保存到文件中
int Save(LinkList head);

// 列出所有的联系人
int List(LinkList head);

#endif

