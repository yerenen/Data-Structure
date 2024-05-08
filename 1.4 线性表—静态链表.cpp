/*线性表*/
/*静态链表：用数组的方式实现的链表*/
/*
--优点：增、删操作不需要大量移动元素
--缺点：不能随机存取，只能从头结点开始依次往后查找，容量固定不可变
适用场景：
①不支持指针的低级语言；
②数据元素数量固定不变的场景（如操作系统的文件分配表）
*/
#include<iostream>//静态链表的最大长度
#include<stdio.h>
#define MAXSIZE 100
using namespace std;
typedef struct Node{
	int data;//存储数据元素
	int next;//下一个元素的数组下标
}SLinkList;
/*
typedef struct Node{
	int data;//存储数据元素
	int next;//下一个元素的数组下标
}SLinkList[MAXSIZE];
*/
//1、初始化静态链表：在存储数组中建立空闲链表
int InitList(SLinkList S[])
{
	for (int i = 0;i < MAXSIZE;i++)
	{
		S[i].next = i + 1;
	}
	S[MAXSIZE - 1].next = 0;
	return 0;
}
/*
int InitList(SLinkList S)
{
	for (int i = 0;i < MAXSIZE;i++)
	{
		S[i].next = i + 1;
	}
	S[MAXSIZE - 1].next = 0;
	return 0;
}
*/
#if 0
//若空闲链表非空，则返回分配的结点下标，否则返回0
int AllocNode(SLinkList& S)
{
	int i;
	i = S[0].next;
	if (i == 0)
		return 0;
	S[0].next = S[i].next;
	return i;
}
//将下标为i的空闲结点回收到备用链表
void FreeNode(SLinkList S, int i)
{
	S[i].next = S[0].next;
	S[0].next = i;
}
//2、创建一个含有n个结点的静态链表,返回表头在存储数组的位置
void CreateList(SLinkList S, int n)
{
	int hesd, k, s, i;
	k = AllocNode(S);//从空闲链表中取得一个空结点
	head = k;
	for (int i = 1;i < -n;i++)
	{
		s = AllocNode(S);
		scanf("%d", &S[s].data);
		S[k].next = s;
		k = s;
	}
	S[k].next = 0;
	return head;
}
#endif
int main(void)
{
	SLinkList S[MAXSIZE];
	InitList(S);
	for (int i = 0;i < MAXSIZE;i++)
	{
		S[i].data = S[i].next;
		cout << S[i].data << endl;
	}
	return 0;
}
