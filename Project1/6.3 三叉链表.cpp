#if 0
��
1.1 ������
1.1.1 ��������洢�ṹ
#endif

#include<iostream>
#include<stdio.h>
using namespace std;
typedef struct TriTree {
	int data;
	struct BiNode* lchild, * parent, * rchild;
}TriTNode, * TriTree;