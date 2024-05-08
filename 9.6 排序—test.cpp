#include<iostream>
#include<stdio.h>
#define MAXSIZE 100
using namespace std;
typedef int KeyType;
typedef struct {
	KeyType key;
}RedType;
typedef struct SqList{
	RedType r[MAXSIZE+1];
	int length;
}SqList;

//题：找出数组中未出现的最小正整数(自写)
//考点：排序
//时间复杂度：O(n^2)
//空间复杂度：O(1)
//此处使用的是直接插入排序，算法稳定
int Search_Min(SqList &L)
{
	//给数组排成正序
	//int i;//表示无序部分第一个位置
	int j;//表示插入位置过程中寻找的下标
	for (int i = 2; i <= L.length; ++i)
	{
		if (L.r[i].key < L.r[i - 1].key)//若无序部分第二个元素比第一个元素小，需将L.r[i]插入有序子表
		{
			L.r[0] = L.r[i];//复制为哨兵
			for (j = i - 1; L.r[0].key < L.r[j].key; --j)
			{
				L.r[j + 1] = L.r[j];//记录后移
			}
			L.r[j + 1] = L.r[0];//插入到正确位置
		}
	}
	//从正序数组中找最小正整数
	int k = 1;
	for (int n = 1; n < L.length+1; n++)
	{
		if (L.r[n].key == k && L.r[n].key >0)
			k++;
	}
	return k;
}

//题：找出数组中未出现的最小正整数(题解)
//考点：排序
//时间复杂度：O(n)
//空间复杂度：O(n)
//空间换时间
int R[MAXSIZE];//辅助数组
int Search_Min_Stan(SqList& L)
{
	int i = 0;
	for (int i = 1; i <= L.length; i++)
	{
		if (L.r[i].key > 0 && L.r[i].key <= L.length)
			R[i] = i;
	}
	for (int i = 1; i <= L.length; i++)
	{
		if (L.r[i].key == 0)
			return i;
	}
	return i + 1;
}

int main(void)
{
	SqList L;
	//初始化顺序表
	for (int i = 0; i < MAXSIZE+1; i++)
	{
		L.r[i].key = 0;
	}
	L.length = 0;
	//给顺序表赋值
	cout << "请输入顺序表长度：" << endl;
	cin >> L.length;
	cout << "请输入顺序表元素：" << endl;
	for (int i = 1; i < L.length+1; i++)
	{
		cin >> L.r[i].key;
	}
	cout << "题解：" << Search_Min_Stan(L) << endl;//题解有问题
	cout << "自解：" << Search_Min(L) << endl;//题解
}