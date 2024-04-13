/*线性表*/
/*顺序栈——顺序存储结构*/
/*存储方式：同一般线性表的顺序存储结构完全相同*/
/*利用一组地址连续的存储单元依次存放自栈底到栈顶的数据元素。栈底一般在低地址端*/
/*--附设top指针，指示栈顶元素在顺序栈中的位置*/
/*--另设base指针，指示栈底元素在顺序栈中的位置*/
#include<iostream>
#include<stdio.h>
#define MAXSIZE 100
using namespace std;
typedef struct {
	int *base;//栈底指针
	int *top;//栈顶指针
	int stacksize;//栈可用最大容量
}SqStack;
/*顺序栈算法一：顺序栈的初始化*/
int InitStack(SqStack& S)//构造一个空栈
{
	S.base = new int[MAXSIZE];//或S.base=(SElemtype*)malloc(MAXSIZE *sizeof(SElemtype));
	if (!S.base)exit(OVERFLOW);//存储分配失败
	S.top = S.base;//栈顶指针等于栈底指针
	S.stacksize = MAXSIZE;
	return 0;
}
/*顺序栈算法二：判断顺序栈是否为空*/
int Is_Empty(SqStack& S)
{
	//若栈空，则返回TRUE；否则返回FALSE
	if (S.top == S.base)
		return 0;
	else
		return 1;
}
/*顺序栈算法三：求顺序栈长度*/
int StackLength(SqStack S)
{
	return S.top - S.base;
}
/*顺序栈算法四：清空顺序栈*/
int ClearStack(SqStack &S)//有问题，是否需要带引用符
{
	if (S.base)//判断栈是否存在
		S.top = S.base;
	return 0;
}
/*顺序栈算法五：销毁顺序栈*/
int DestroyStack(SqStack& S)
{
	if (S.base) {//如果栈存在且不为空
		delete S.base;//删除栈底指针
		S.stacksize = 0;//将栈的个数设置为0
		S.base = S.top = NULL;//top指针和base指针均设置为空（不是已经删除栈底指针了吗，为什么还要置空）
	}
	return 0;
}
/*顺序栈算法六：顺序栈的入栈*/
/*算法思想：
* ①判断是否栈满，若满则出错（上溢）
* ②元素e压入栈顶
* ③栈顶指针加一*/
int Push(SqStack& S, int e)
{
	if (S.top - S.base == S.stacksize)//栈满
		return 1;
	*S.top++ = e;//将e赋给top指针所指的空间，然后top指向下一空间
	return 0;
}
/*顺序栈算法七：顺序栈的出栈*/
/*算法思想：
* ①判断是否栈空，若空则出错（下溢）
* ②获取栈顶元素e
* ③栈顶指针减一*/
int pop(SqStack& S, int& e)
{
	//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
	if (S.top == S.base)//等价于if(StackEmpty(S))
		return 1;
	else
	{
		e = *--S.top;//指针先下移，然后再取指针当初所取的元素的值赋值给e
		return 0;
	}
}
void ScanSqStack(SqStack S)//遍历栈
{
	int e = StackLength(S);
	if (e > 0)
	{
		for (int i = 0;i < e;i++)
		{
			cout << S.base[i] << endl;
		}
	}
	else
	{
		cout << "顺序栈为空" << endl;
	}
}
int main()
{
	int e;
	SqStack S;
	InitStack(S);//初始化栈
	Push(S, 1);//入栈
	Push(S, 2);
	Push(S, 3);
	Push(S, 4);
	Push(S, 5);
	ScanSqStack(S);
	cout<<"栈长度为" << StackLength(S) << endl;
	pop(S,e);//出栈
	ScanSqStack(S);//遍历栈
	cout << "栈长度为" << StackLength(S) << endl;
	ClearStack(S);
	cout<<"判断是否栈空，如果栈空返回0，如果栈不空返回1：" << Is_Empty(S) << endl;
	DestroyStack(S);
	ScanSqStack(S);//遍历栈
}