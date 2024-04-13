/*线性表*/
/*顺序表——顺序存储结构*/
#include<iostream>
using namespace std;
#define maxsize 100
typedef struct //定义顺序表的结构体
{
	int data[maxsize];//存放顺序表元素的数组，默认是int型，可根据题目要求将int换成其他类型
	int length;//存放顺序表的长度
}Sqlist;
/*
顺序表的基本操作：
1、InitList(&L);//初始化操作，建立一个空的线性表；（因为涉及原表数据需要作改动，所以使用引用的方法&L）
2、DestroyList(&L);//销毁已存在的线性表L（引用原表）
3、ClearList(&L);//将线性表清空（问：为什么会涉及引用？和销毁表有什么区别吗？）
4、ListInsert(&L,i,e);//在线性表L的i位置插入e元素（问：为什么此处e不用引用）
5、ListDelete(&L,i,&e);//删除线性表L的i位置的e元素,返回e(问：为什么e也要引用？，元素直接删除不就行了，引用是为了干啥)
6、IsEmpty(L);//bool类型的函数，如果L为空则返回true，否则返回false
7、ListLength(L);//返回线性表L的元素个数
8、LocateElem(L,e);//按值查找，在L中查找与给定值e相等的元素，若成功返回该元素在表中的序号，否则返回0
9、GetElem(L,i,&e);//按位查找，将L中的第i个位置元素返回给e
*/

/*
顺序表的删除：
线性表的删除操作是指将表的第i(1<=i<=n)个结点删除使长度为n的线性表(a1,...,ai-1,ai,ai+1,...,an)变成长度为n-1的线性表(a1,...,ai-1,ai+1,...,an)
算法思想：
①判断删除位置i是否合法（合法值为1<=i<=n）
②将与删除的元素保留在e中
③将第i+1至第n位的元素依此向前移动一个位置
④表长减一，删除成功返回OK
*/
/*
int ListDelete(Sqlist &L, int i,int &e)//操作：删除算法
{
	if ((i<1)||(i>L.length))//判断删除位置是否合法
		return false;
	e=L.data[i-1];
	for (int j = i;j < L.length;j++)
	{
		L.data[j-1] = L.data[j];
	}
	L.length--;
	return true;
}
*/
/*int ListDelete(Sqlist L, int i, int& e)//操作：删除操作
{
	if ((i < 1) || (i > L.length))//1、判断删除位置i是否合法
		return false;
	e = L.data[i];
	for (int j=i;j <= L.length-1;j++)//2、将第i+1至第n位的元素依次向前移动一个位置
	{
		e = L.data[i];
		L.data[j-1] = L.data[j];
		L.length--;//3、表长减一，删除成功返回OK
	}
	return e;
}
//时间复杂度：n-1/2(O(n))
*/

/*
顺序表的插入：
线性表的插入运算是指在表的第i（1<=i<=n+1）个位置上，插入一个新结点e，使长度为n的线性表（a1,...,ai-1,ai,...,an）变成长度为n+1的线性表（a1,...,ai-1,e,ai,...,an）变成长度为n+1的线性表(a1,...,ai-1,e,ai,...,an)
算法思想：
①判断插入位置i是否合法
②判断顺序表的存储空间是否已满，若已满返回ERROR
③将第n至第i位的元素依次向后移动一个位置，空出第i个位置
*/
int ListInsert(Sqlist& L, int i, int e)//操作：插入操作——在i位置插入e元素（问：i，e是否都是用户给出的数值？）
{
	if (i<1 || i>L.length + 1)//判断插入位置是否合法
		return false;
	if (L.length == maxsize)//判断存储空间是否为满
		return false;
	for (int j = L.length - 1;j >= i - 1;j--)//注意此处j为L.length-1,且插入是倒着插
		L.data[j + 1] = L.data[j];
	L.data[i - 1] = e;
	L.length++;
	return true;
}
int InitList(Sqlist& L) //构造一个空的顺序表L;
{
	L.length = 0;
	return true;
}
int ListDelete(Sqlist& L, int i, int& e)//操作：删除算法
{
	if ((i < 1) || (i > L.length))//判断删除位置是否合法
		return false;
	e = L.data[i - 1];
	for (int j = i;j < L.length;j++)
	{
		L.data[j - 1] = L.data[j];
	}
	L.length--;
	return true;
}
int GetElem(Sqlist L, int i, int& e) //操作：按位查找——在线性表中查找i位置的元素，返回给e，注意此处的引用符号&的实际使用方法
{
	e = L.data[i - 1];//注意这里返回的是数组的i-1
	return e;
}
int LocateElem(Sqlist L, int e)//操作：按值查找——在线性表L中查找值为e的数的位置
{
	int i;
	for (i = 0;i < L.length;i++)
	{
		if (L.data[i] == e)
			return i + 1;
	}
	return -1;
}
int Getlength(Sqlist L)//操作：获得线性表的长度
{
	return(L.length);
}
int main()
{
	Sqlist L;
	int e;
	/*
	int a = 0;
	int i = 0;
	L.length = 10;
	std::cout << "第一次赋值操作后：";
	for (int i = 0;i < 10; i++) //线性表的数组赋值
	{
		L.data[i] = i;
		std::cout << L.data[i];
	}
	ListInsert(L,2,6);
	std::cout << "第一次数组长度为："<<L.length<<endl;
	std::cout << "第一次插入操作后：" ;
	for (int i = 0;i < 10; i++) //线性表的数组赋值
	{
		std::cout<< L.data[i];
	}
	std::cout << "第二次数组长度为：" <<L.length<<endl;
	ListDelete(L, 3);
	std::cout << "第一次删除操作后：";
	for (int i = 0;i < 10; i++) //线性表的数组赋值
	{
		std::cout<< L.data[i];
	}
	std::cout << "第三次数组长度为：" <<L.length<<endl;
	*/
	InitList(L);
	std::cout << "第一次初始化操作后数组长度为：" << Getlength(L) << endl;
	ListInsert(L, 1, 1);
	ListInsert(L, 2, 2);
	ListInsert(L, 3, 3);
	ListInsert(L, 4, 4);
	ListInsert(L, 5, 5);
	for (int i = 0;i < L.length; i++) //线性表的数组赋值
	{
		std::cout << L.data[i];
	}
	std::cout << "第一次插入操作后数组长度为：" << Getlength(L) << endl;
	ListDelete(L, 1, e);
	for (int i = 0;i < L.length; i++) //线性表的数组赋值
	{
		std::cout << L.data[i];
	}
	std::cout << "第二次删除操作后数组长度为：" << Getlength(L) << endl;
	std::cout << "第二次删除操作中被删除的元素为" << e << endl;
	std::cout << "按位查找第2位的e元素值为：" << GetElem(L, 2, e) << endl;
	std::cout << "按值查找元素值为3的数字在数组中的位数为：" << LocateElem(L, 3) << endl;
	return 0;
}
