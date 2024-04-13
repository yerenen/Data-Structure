#if 0
树
1.1 二叉树
1.1.1 线索二叉树（Threaded Binary Tree）
--为什么要研究线索二叉树？
当用二叉链表作为二叉树的存储结构时，可以很方便地找到某个结点的左右孩子；但一般情况下，无法直接找到该结点在某种遍历序列中的前驱和后继结点。
--解决方法：
①通过遍历寻找——费时间
②再增设前驱、后继指针域——增加了存储负担
③利用二叉链表的空指针域——如果某个结点的左孩子为空，则将空的左孩子指针域改为指向其前驱；如果某结点的右孩子为空，则将空的右孩子指针域改为指向其后继。——这种改变指向的指针被称为线索。
--这种加上了线索的二叉树称为线索二叉树(Threaded Binary Tree)
对于二叉树按某种遍历次序使其变为线索二叉树的过程叫线索化。
#endif
#include<iostream>
#include<stdio.h>
using namespace std;
//为了区分lchild和rchild指针到底是指向孩子的指针，还是指向前驱或者后继的指针，对二叉链表中每个结点增设两个标志域ltag和rtag，并约定：
//ltag=0  lchild指向该结点的左孩子
//ltag=1  lchild指向该结点的前驱
//rtag=0  rchild指向该结点的右孩子
//rtag=1  lchild指向该结点的后继
typedef char TElemType;
typedef struct BiThrNode{
	TElemType data;//存放数据域
	int ltag, rtag;//存放标记整数
	struct BiThrNode* lchild;
	struct BiThrNode* rchild;
}BiThrNode,*BiThrTree;
TElemType Nil = '#';
void CreateBiThrTree(BiThrTree *T)
{
	TElemType h;
	cin >> h;
	if (h == Nil)
		*T = NULL;
	else
	{
		*T = (BiThrTree)malloc(sizeof(BiThrNode));
		if (!*T)
			exit(OVERFLOW);
		(*T)->data = h;
		CreateBiThrTree(&((*T)->lchild));
		if ((*T)->lchild)//如果有左孩子
			(*T)->ltag = 0;
		CreateBiThrTree(&((*T)->rchild));
		if ((*T)->lchild)//如果有右孩子
			(*T)->rtag = 0;
	}
}
void InOrderTraverse_Thr(BiThrTree T)//中序遍历
{
	//?
}
int main(void)
{
	BiThrTree H=NULL;
	printf("请按前序输入二叉树(如:'ABDH##I##EJ###CF##G##')\n");
	CreateBiThrTree(&H); /* 按前序产生二叉树 */
	cout << H->lchild->data << endl;
	InOrderTraverse_Thr(H);
}