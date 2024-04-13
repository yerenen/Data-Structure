#include<iostream>
#include<stdio.h>
using namespace std;
#define MAXSIZE 100
typedef struct BiNode {
	char data;
	struct BiNode* lchild, * rchild;//���Һ���ָ��
}BiNode, * BiTree;
/*�������㷨ʵ��-�������*/
//��������Ϊ�գ���ղ�����
//���������ǿգ�����ʸ��ڵ㣨D��
//ǰ�������������L��
//ǰ�������������R��
void visit(BiTree T)
{
	printf("%c", T->data);
}
/*ǰ������㷨*/
void PreOrderTraverse(BiTree T)
{
	if (T == NULL)//�ն�����
		return;
	else
	{
		visit(T);//���ʸ��ڵ�
		PreOrderTraverse(T->lchild);//�ݹ����������
		PreOrderTraverse(T->rchild);//�ݹ����������
	}
}
/*ǰ������㷨���ǵݹ鷽ʽ��*/
void PreOrderTraverse1(BiTree T)
{
	if (T == NULL)
		return;
}
/*��������㷨*/
void InOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	InOrderTraverse(T->lchild);//�������������
	visit(T);
	InOrderTraverse(T->rchild);//�������������
}
/*��������㷨*/
void PostOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	visit(T);
}
/*�������Ĳ�α���*/
/*
�㷨˼·����ʹ��һ�����У�
--����������
--�Ӳ���ʱѭ�����Ӷ����г���һ�����*p����������
������������ӽ�㣬�����ӽ����ӣ�
����������Һ��ӽ�㣬���Һ��ӽ����ӡ�
*/
#define MAXQSIZE 100
typedef struct {
	BiNode* data[MAXQSIZE];
	int front;
	int rear;
}SqQueue;//˳���������
int EnQueue(SqQueue& Q, BiNode* e)//���дӶ�βԪ����
{
	Q.data[Q.rear] = e;
	Q.rear = Q.rear + 1;
	return 0;
}
int Is_Empty(SqQueue Q)
{
	if (Q.front == Q.rear)//�ӿ�
		return 1;
	else
		return 0;
}
int DeQueue(SqQueue& Q, BiNode* e)
{
	if (Q.front == Q.rear)
		printf("�ӿ�");
	e = Q.data[Q.front];
	Q.front = Q.front + 1;
	return e->data;
}
//�пյ�����ʼ��������
//�ʣ���ô���������Ľ��Ž����У���
//�ʣ�Ϊɶ�����õ���ָ�룿
void LevelOrder(BiNode* T)//�������
{
	BiNode* p = T;
	SqQueue qu;
	qu.front = qu.rear = 0;
	EnQueue(qu, p);//�����ָ��������
	while (!Is_Empty(qu))//�Ӳ�Ϊ�գ���ѭ��
	{
		p = qu.data[qu.front];
		DeQueue(qu, p);//���ӽ��p
		visit(p);//���ʽ��p
		if (p->lchild != NULL)
		{
			EnQueue(qu, p->lchild);//������ʱ�������
		}
		if (p->rchild != NULL)
		{
			EnQueue(qu, p->rchild);//���Һ���ʱ�������
		}
	}
}
/*���ݹ�ķ�ʽ������������*/
/*��ǰ������������н���ֵ��һ���ַ���*/
/*#��ʾ������������������ʾ������T */
void CreateBiTree(BiTree& T)
{
	char ch;
	cin >> ch;
	if (ch == '#')
		T = NULL;
	else
	{
		T = new BiNode;
		//T = (BiTree)malloc(sizeof(BiTree));//?
		if (!T)
			exit(OVERFLOW);//T = new BiTNode;
		T->data = ch;//���ɸ��ڵ�
		CreateBiTree(T->lchild);//����������
		CreateBiTree(T->rchild);//����������
	}
}
int main(void)
{
	BiTree T;
	T = NULL;
	cout << "�������������ǰ�����У���#����ս�㣩��" << endl;
	CreateBiTree(T);
	cout << "����������Ϊ��" << endl;
	PreOrderTraverse(T);
	cout << endl;
	cout << "����������Ϊ��" << endl;
	InOrderTraverse(T);
	cout << endl;
	cout << "����������Ϊ��" << endl;
	PostOrderTraverse(T);
	cout << endl;
	cout << "����������Ϊ��" << endl;
	LevelOrder(T);
	cout << endl;
	//cout << "T�����Ϊ" << Depth(T)<<endl;
	//cout<<"T��������Ϊ" << NodeCount(T)<<endl;
	return 0;
	/*
	�������ݣ�AB#D##C##
	*/
}



