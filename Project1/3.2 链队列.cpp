#include<iostream>
#include<stdio.h>
using namespace std;
typedef char QElemType;
/*带头结点的链式队列*/
typedef struct QNode {//结点结构
	QElemType data;//存储数据
	struct QNode* next;//存储指针
}QNode,*QueuePtr;
typedef struct//队列的链表结构
{
	QueuePtr front;
	QueuePtr rear;//队头队尾指针
}LinkQueue;
/*链队列的初始化*/
int InitQueue(LinkQueue& Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return 0;
}
/*销毁链队列*/
int DestroyQueue(LinkQueue& Q)
{
	QNode * p;
	while (Q.front)
	{
		p = Q.front->next;//Q.rear = Q.front->next;
		Q.front = p;//free(Q.front);
		//Q.front = Q.rear;
	}
	return 0;
}
/*链队列入队：队列的链式表示和实现*/
int EnQueue(LinkQueue &Q, QElemType e)
{
	if (!Q.front)
		InitQueue(Q);
	QNode *p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return 0;
}
int Is_Empty(LinkQueue Q)
{
	if (Q.front->next)
	{
		printf("队不空");
		return 0;//队空
	}
	else
	{
		printf("队空");
		return 1;
	}
}
/*链队列出队*/
int DeQueue(LinkQueue &Q,char e)
{
	if (Is_Empty == 0)//判空
		printf("队空");
	else
	{
		QueuePtr p = Q.front->next;
		e = p->data;
		Q.front->next = p->next;
		//if (Q.rear == p)//如果删除的结点为尾结点
		//	Q.rear = Q.front;
		delete(p);
		return e;
	}
}
/*链队列中求队头元素*/
int GetHead(LinkQueue Q, QElemType& e)
{
	if (Q.front == Q.rear)//判断队空
		return 0;
	e = Q.front->next->data;
	return 0;
}
/*链队列的遍历*/
int scanQueue(LinkQueue Q)
{
	int k = 0;
	QueuePtr p =Q.front->next;
	while (p)
	{
		cout << p->data;
		p = p->next;
		k++;
	}
	return k;
}
int main(void)
{
	char e = '/0';
	char a = 'A';
	char b = 'B';
	char c = 'C';
	char d = 'D';
	LinkQueue Q;
	LinkQueue* p=&Q;
	InitQueue(Q);
	EnQueue(Q, a);
	EnQueue(Q, b);
	EnQueue(Q, c);
	EnQueue(Q, d);
	cout << "1、入队后遍历队列：" << endl;
	scanQueue(Q);
	cout << endl;
	DeQueue(Q,e);
	cout << "2、出队后遍历队列：" << endl;
	scanQueue(Q);
	cout << endl;
	cout << "3、取队头元素：" <<endl;
	GetHead(Q,e);
	cout << e << endl;
	cout << "4、判空：" << endl;
	Is_Empty(Q);
	cout << endl;
	DeQueue(Q,e);
	DeQueue(Q,e);
	DeQueue(Q,e);
	cout << "5、出完队后再次判空：" << endl;
	Is_Empty(Q);
}
