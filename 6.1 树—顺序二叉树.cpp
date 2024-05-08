#if 0
树
1.1 二叉树
1.1.1 二叉树的顺序存储
--缺点：
最坏情况：深度为k的且只有k个结点的单支树需要长度为2(k) - 1的一维数组。（单叉树）
--特点：
结点之间的关系蕴含在其存储位置中浪费空间，适于存满二叉树和完全二叉树。
#endif

#include<iostream>
#include<stdio.h>
using namespace std;
#define MAXSIZE 100//二叉树的最大结点数
typedef int TElemType;//树结点的数据类型，目前暂定为整型
typedef TElemType SqBiTree[MAXSIZE];//0号单元存储根结点
SqBiTree T;
TElemType Nil = 0;

//构造初始化二叉树
//因为T是固定数组不会改变，所以此处不需要&
void InitBiTree(SqBiTree T)
{
	int i;
	for (int i = 0;i < MAXSIZE;i++)
	{
		T[i] = Nil;
	}
}

int main(void)
{
	SqBiTree T;
	InitBiTree(T);
	for (int i = 0;i < MAXSIZE;i++)
	{
		cout << T[i] << endl;
	}
}