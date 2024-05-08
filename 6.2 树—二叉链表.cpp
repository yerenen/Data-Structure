#if 0
��
1.1 ������
1.1.1 ��������洢�ṹ
#endif
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
typedef struct{
	BiNode * data[MAXQSIZE];//��1��data�����ŵ���ָ��BiNode���ĵ�ַ
	int front;
	int rear;
}SqQueue;//˳��������ͣ��������ʹ��˳��ѭ�����У�
int EnQueue(SqQueue& Q, BiNode *e)//���дӶ�βԪ����
{
	Q.data[Q.rear] = e;
	Q.rear= Q.rear + 1;
	return 0;
}
int Is_Empty(SqQueue Q)//ע�������Is_Emptyд����Ϊ�շ���1��True������Ϊ�շ���0.
{
	if (Q.front == Q.rear)//�ӿ�
		return 1;
	else
		return 0;
}
int DeQueue(SqQueue& Q, BiNode *e)
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
void LevelOrder(BiNode *T)//�������
{
	BiNode *p=T;
	SqQueue qu;
	qu.front = qu.rear = 0;//ע���ʼ��
	EnQueue(qu, p);//�����ָ��������
	while (!Is_Empty(qu))//�Ӳ�Ϊ�գ���ѭ��
	//��2��ע�������Is_Empty����
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
/*�����������㷨��Ӧ��-���ƶ����������ö��������������˼�룩*/
/*����ǿ������ݹ������
* ���������½��ռ䣬���Ƹ����
* �ݹ鸴��������
* �ݹ鸴��������*/
int Copy(BiTree T, BiTree& NewT)
{
	if (T == NULL)
	{
		NewT = NULL;
		return 0;
	}
	else
	{
		NewT = new BiNode;//�ڴ��з���һ���µĿռ�
		NewT->data = T->data;
		Copy(T->lchild, NewT->lchild);
		Copy(T->rchild, NewT->rchild);
	}
}
/*�����������㷨��Ӧ�á�����������������*/
/*����ǿ����������Ϊ0��
* ���򣬵ݹ��������������ȼ�Ϊm���ݹ��������������ȼ�Ϊn���������������Ϊm��n�Ľϴ��߼�1
*/
int Depth(BiTree T)
{
	if (T == NULL)
		return 0;//����ǿ�������0
	else
	{
		int m = Depth(T->lchild);
		int n = Depth(T->rchild);
		if (m > n)
			return (m + 1);
		else
			return (n + 1);
	}
}
/*�����������㷨��Ӧ�á�������������Ľ������*/
/*����ǿ������������Ϊ0��
* ���򣬽�����Ϊ�������Ľ�����+�������Ľ�����+1��
*/
int NodeCount(BiTree T)
{
	if (T == NULL)
		return 0;
	else
	{
		return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
	}
}
/*�����������㷨��Ӧ�á������������Ҷ�ӽ������*/
/*����ǿ������������Ϊ0��
* ���򣬽�����Ϊ�������Ľ�����+�������Ľ�����+1*/

int LeafCount(BiTree T)
{
	if (T == NULL)//����ǿ�������0
		return 0;
	if (T->lchild == NULL && T->rchild == NULL)
		return 1;
	else
	{
		return LeafCount(T->lchild) + LeafCount(T->rchild);
	}
}
/*���ݹ�ķ�ʽ������������*/
/*��ǰ������������н���ֵ��һ���ַ���*/
/*#��ʾ������������������ʾ������T */
void CreateBiTree(BiTree &T)
//ע�ⴴ����������ʱ�������������Ĳ���ΪBiTree &T
//���Ǳ�����������ʱ�������еĲ�����ΪBiNode *T
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
	cout << "T�����Ϊ" << Depth(T)<<endl;
	cout<<"T��������Ϊ" << NodeCount(T)<<endl;
	return 0;
	/*
	�������ݣ�AB#D##C##
	*/
}