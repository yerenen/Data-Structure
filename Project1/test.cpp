#include<iostream>
#include<stdio.h>
using namespace std;
#define MAXSIZE 100
typedef struct BiNode {
	char data;
	struct BiNode* lchild, * rchild;//左右孩子指针
}BiNode, * BiTree;
/*遍历的算法实现-先序遍历*/
//若二叉树为空，则空操作；
//若二叉树非空，则访问根节点（D）
//前序遍历左子树（L）
//前序遍历右子树（R）
void visit(BiTree T)
{
	printf("%c", T->data);
}
/*前序遍历算法*/
void PreOrderTraverse(BiTree T)
{
	if (T == NULL)//空二叉树
		return;
	else
	{
		visit(T);//访问根节点
		PreOrderTraverse(T->lchild);//递归遍历左子树
		PreOrderTraverse(T->rchild);//递归遍历右子树
	}
}
/*前序遍历算法（非递归方式）*/
void PreOrderTraverse1(BiTree T)
{
	if (T == NULL)
		return;
}
/*中序遍历算法*/
void InOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	InOrderTraverse(T->lchild);//中序遍历左子树
	visit(T);
	InOrderTraverse(T->rchild);//中序遍历右子树
}
/*后序遍历算法*/
void PostOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	visit(T);
}
/*二叉树的层次遍历*/
/*
算法思路：（使用一个队列）
--将根结点入队
--队不空时循环：从队列中出列一个结点*p，访问它；
①如果它有左孩子结点，将左孩子结点入队；
②如果它有右孩子结点，将右孩子结点入队。
*/
#define MAXQSIZE 100
typedef struct {
	BiNode* data[MAXQSIZE];
	int front;
	int rear;
}SqQueue;//顺序队列类型
int EnQueue(SqQueue& Q, BiNode* e)//队列从队尾元素入
{
	Q.data[Q.rear] = e;
	Q.rear = Q.rear + 1;
	return 0;
}
int Is_Empty(SqQueue Q)
{
	if (Q.front == Q.rear)//队空
		return 1;
	else
		return 0;
}
int DeQueue(SqQueue& Q, BiNode* e)
{
	if (Q.front == Q.rear)
		printf("队空");
	e = Q.data[Q.front];
	Q.front = Q.front + 1;
	return e->data;
}
//判空的条件始终有问题
//问：怎么将二叉树的结点放进队列？？
//问：为啥参数用的是指针？
void LevelOrder(BiNode* T)//层序遍历
{
	BiNode* p = T;
	SqQueue qu;
	qu.front = qu.rear = 0;
	EnQueue(qu, p);//根结点指针进入队列
	while (!Is_Empty(qu))//队不为空，则循环
	{
		p = qu.data[qu.front];
		DeQueue(qu, p);//出队结点p
		visit(p);//访问结点p
		if (p->lchild != NULL)
		{
			EnQueue(qu, p->lchild);//有左孩子时将其进队
		}
		if (p->rchild != NULL)
		{
			EnQueue(qu, p->rchild);//有右孩子时将其进队
		}
	}
}
/*（递归的方式）建立二叉树*/
/*按前序输入二叉树中结点的值（一个字符）*/
/*#表示空树，构造二叉链表表示二叉树T */
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
		T->data = ch;//生成根节点
		CreateBiTree(T->lchild);//构造左子树
		CreateBiTree(T->rchild);//构造右子树
	}
}
int main(void)
{
	BiTree T;
	T = NULL;
	cout << "请输入二叉树的前序序列（以#代表空结点）：" << endl;
	CreateBiTree(T);
	cout << "先序遍历结果为：" << endl;
	PreOrderTraverse(T);
	cout << endl;
	cout << "中序遍历结果为：" << endl;
	InOrderTraverse(T);
	cout << endl;
	cout << "后序遍历结果为：" << endl;
	PostOrderTraverse(T);
	cout << endl;
	cout << "层序遍历结果为：" << endl;
	LevelOrder(T);
	cout << endl;
	//cout << "T树深度为" << Depth(T)<<endl;
	//cout<<"T树结点个数为" << NodeCount(T)<<endl;
	return 0;
	/*
	测试数据：AB#D##C##
	*/
}



