/*线性表*/
/*线性表的应用*/
#include<stdio.h>
#include<iostream>
using namespace std;
#define maxsize 100
typedef struct {
	int data[maxsize];
	int length;
}Sqlist;
/*应用一：假设利用两个线性表La和Lb分别表示两个集合A和B，现要求一个新的集合A=AUB*/
//算法步骤：
//依次取出Lb中的每个元素，执行以下操作：
//①在La中查找该元素
//②如果找不到，则将其插入La的最后
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
int InitList(Sqlist& L) //构造一个空的顺序表L;
{
	L.length = 0;
	return true;
}
/*我解,我解就是解不出来*/
void merge(Sqlist &L,Sqlist J) 
{
	int i=0;
	int j=0;
	for (int i = 0;i < L.length;i++)//遍历数组L
	{
		while (j < J.length)
		{
			while (L.data[i] != J.data[j])//
			{
				L.data[L.length++] = J.data[j++];
			}
		}
	}
}
/*题解*/
/*调试的结果：感觉数值就没成功合并？？？*/
void union_L(Sqlist& La, Sqlist Lb)
{
	int e;
	int La_len = La.length;
	int Lb_len = Lb.length;
	for (int i = 1;i <= Lb.length;i++)
	{
		GetElem(Lb, i, e);//将线性表Lb中每个值顺序取出来看看是什么值
		if (!LocateElem(La, e))//按值查找，看La线性表中是否有这个元素
			ListInsert(La, ++La_len, e);//如果La线性表中没有e元素，则将其插入数组
	}
}
/*应用二：已知线性表La和Lb中的数据元素按值非递减（递增?）有序排列，现要求将La和Lb归并为一个新的线性表Lc，且Lc中的数据元素仍按值非递减有序排列*/
//算法步骤：
//①创建一个空表Lc
//②依次从La或Lb中“摘取”元素值较小的结点插入到Lc表的最后，直至其中一个表变空为止
//③继续将La或Lb其中一个表的剩余结点插入在Lc表的最后
/*题解——有序表合并：用顺序表实现,双指针实现*/
/*
void MergeList_Sq(Sqlist LA, Sqlist LB, Sqlist& LC)
{
	pa = LA.elem;
	pb = LB.elem;//指针pa和pb的初值分别指向两个表的第一个元素
	LC.length = LA.length + LB.length;//新表长度为待合并两表的长度之和
	LC.elem = new ElemType[LC.length];//为合并后的新表分配一个数组空间
	pc = LC.elem;//指针pc指向新表的第一个元素
	pa_last = LA.elem + LA.length - 1;//指针pa_last指向LA表的最后一个元素
	pb_last = LB.elem + LB.length - 1;//指针pb_last指向LB表的最后一个元素
	while(pa<=pa_last&&pb<=pb_last){//两个表都非空
		if (*pa <= *pb)//依次“摘取”两表中值较小的结点
			*pc++ = *pa++;
		else
			*pc++ = *pb++;
	}
	while (pa <= pa_last)//LB表已到达表尾，将LA中剩余元素加入LC
		*pc++ = *pa++;
	while (pb <= pb_last)//LA表已到达表尾，将LB中剩余元素加入LC
		*pc++ = *pb++;
}
*/
void merge_L(Sqlist La, Sqlist Lb,Sqlist &Lc)
{
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < La.length && j < Lb.length)
	{
		if (La.data[i] < Lb.data[j])
		{
			Lc.data[k++] = La.data[i++];
		}
		else
		{
			Lc.data[k++] = Lb.data[j++];
		}
	}
	while (i < La.length)
	{
		Lc.data[k++] = La.data[i++];
	}
	while (j < Lb.length)
	{
		Lc.data[k++] = Lb.data[j++];
	}
	Lc.length = La.length + Lb.length;
}
int main()
{
	Sqlist J;
	Sqlist L;
	Sqlist K;
	InitList(L);
	InitList(J);
	InitList(K);
	ListInsert(L, 1, 2);
	ListInsert(L, 2, 4);
	ListInsert(L, 3, 6);
	ListInsert(J, 1, 1);
	ListInsert(J, 2, 3);
	ListInsert(J, 3, 5);
	//union_L(L, J);
	/*for (int i = 0;i < L.length;i++)
	{
		cout << L.data[i] << endl;
	}*/
	merge_L(L, J, K);
	for (int i= 0;i < K.length;i++)
	{
		cout << K.data[i] << endl;
	}
	cout << "K线性表的长度为" <<K.length<< endl;
	return 0;
}

