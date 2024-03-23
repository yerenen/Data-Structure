/*线性表*/
/*链栈——链式存储结构*/
/*链栈是运算受限的单链表，只能在链表头部进行操作*/
#include<iostream>
#include<stdio.h>
using namespace std;
typedef struct StackNode {
	int data;
	struct StackNode* next;
}StackNode,*LinkStack;
/*链栈算法一：链栈的初始化*/
int InitStack(LinkStack& S)
{
	//构造一个空栈，栈顶指针置为空
	S = NULL;
	return 0;
}
/*链栈算法二：判断链栈是否为空*/
int StackEmpty(LinkStack S)
{
	if (S == NULL)
		return 0;
	else
		return 1;
}
/*链栈算法三：链栈的入栈*/
int Push(LinkStack& S, int e)
{
	LinkStack p = new StackNode;//生成新结点p
	p->data = e;//将新结点数据域置为e
	p->next = S;//将新结点插入栈顶
	S = p;//修改栈顶指针
	return 0;
}
/*链栈算法四：链栈的出栈*/
int Pop(LinkStack& S, int& e)
{
	if (S == NULL)
		return 0;
	e = S->data;
	LinkStack p = S;
	S = S->next;
	delete p;
	return 0;
}
/*链栈算法五：取栈顶元素*/
int GetTop(LinkStack S)
{
	if (S != NULL)
		return S->data;
}
void scanStack(LinkStack S)
{
	while (S)
	{
		cout << S->data << endl;
		S = S->next;
	}
}
int main()
{
	int e;
	LinkStack S;
	InitStack(S);
	cout<<"是否栈空，栈空返回0，不空返回1：" << StackEmpty(S) << endl;
	Push(S, 1);
	Push(S, 2);
	Push(S, 3);
	scanStack(S);
	Pop(S,e);
	cout << "弹出栈顶元素后：" << endl;
	scanStack(S);
}
/*栈与递归*/
/*1、递归的定义*/
/*若一个对象部分地包含它自己，或用它自己给自己定义，则称这个对象是递归的；*/
/*若一个过程直接或间接地调用自己，则称这个过程是递归的过程。例如：递归求n的阶乘。*/
/*2、以下三种情况常常用到递归方法：*/
/*①递归定义的数学函数：*/
/*②具有递归特性的数据结构：二叉树，广义表...*/
/*③可递归求解的问题：迷宫问题，Hanoi塔问题...*/
/*3、分治法求解递归问题算法的一般形式：*/
/*void p（参数表）*/
/*{
if(递归结束条件) 可直接求解步骤;——基本项*/
/*else p（较小的参数）;}——归纳项*/