#include<iostream>
#include<stdio.h>
using namespace std;
typedef char QElemType;
/*��ͷ������ʽ����*/
typedef struct QNode {//���ṹ
	QElemType data;//�洢����
	struct QNode* next;//�洢ָ��
}QNode,*QueuePtr;
typedef struct//���е�����ṹ
{
	QueuePtr front;
	QueuePtr rear;//��ͷ��βָ��
}LinkQueue;
/*�����еĳ�ʼ��*/
int InitQueue(LinkQueue& Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return 0;
}
/*����������*/
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
/*��������ӣ����е���ʽ��ʾ��ʵ��*/
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
		printf("�Ӳ���");
		return 0;//�ӿ�
	}
	else
	{
		printf("�ӿ�");
		return 1;
	}
}
/*�����г���*/
int DeQueue(LinkQueue &Q,char e)
{
	if (Is_Empty == 0)//�п�
		printf("�ӿ�");
	else
	{
		QueuePtr p = Q.front->next;
		e = p->data;
		Q.front->next = p->next;
		//if (Q.rear == p)//���ɾ���Ľ��Ϊβ���
		//	Q.rear = Q.front;
		delete(p);
		return e;
	}
}
/*�����������ͷԪ��*/
int GetHead(LinkQueue Q, QElemType& e)
{
	if (Q.front == Q.rear)//�ж϶ӿ�
		return 0;
	e = Q.front->next->data;
	return 0;
}
/*�����еı���*/
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
	cout << "1����Ӻ�������У�" << endl;
	scanQueue(Q);
	cout << endl;
	DeQueue(Q,e);
	cout << "2�����Ӻ�������У�" << endl;
	scanQueue(Q);
	cout << endl;
	cout << "3��ȡ��ͷԪ�أ�" <<endl;
	GetHead(Q,e);
	cout << e << endl;
	cout << "4���пգ�" << endl;
	Is_Empty(Q);
	cout << endl;
	DeQueue(Q,e);
	DeQueue(Q,e);
	DeQueue(Q,e);
	cout << "5������Ӻ��ٴ��пգ�" << endl;
	Is_Empty(Q);
}
