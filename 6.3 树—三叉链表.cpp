#if 0
树
1.1 二叉树
1.1.1 三叉链表存储结构
#endif

#include<iostream>
#include<stdio.h>
using namespace std;
typedef struct TriTree {
	int data;
	struct BiNode* lchild, * parent, * rchild;
}TriTNode, * TriTree;