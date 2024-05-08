#if 0
9 排序
9.1 基本概念和排序方法概述
9.1.1 什么是排序
将一组杂乱无章的数据按一定规律顺次排列起来
即：将无序序列组成一个有序序列（由小到大或由大到小）的运算
个人理解的特点：首先，已有一组杂乱无章的数据。所谓排序是将这组杂乱无章的数据排序成顺序序列。
9.1.2 排序方法的分类
①按数据存储介质：内部排序和外部排序
②按比较器个数：串行排序和并行排序
③按主要操作：比较排序和基数排序
④按辅助空间：原地排序(O(1))和非原地排序(超过O(1))
⑤按稳定性：❤
稳定排序：数值相等的元素，排序以后相对次序不变
非稳定排序：不是稳定排序的方法
--排序的稳定性只对结构类型的数据排序有意义，并不能衡量一个排序算法的优劣
⑥按自然性：自然排序和非自然排序
9.1.3 存储结构—记录序列以顺序表存储
9.2 插入排序
9.2.1 基本思想
每步将一个待排序的对象，按其关键码大小，插入到前面已经排好序的一组对象的适当位置上，直到对象全部插入为止
即边插入边排序，保证子序列中随时都是排好序的
9.2.2 有序插入方法
--在插入a[i]前，数组a的前半段（a[0]-a[i-1]）是有序段，后半段（a[i]-a[n-1]）是停留于输入次序的“无序段”
--插入a[i]使a[0]-a[i-1]有序，也就是要为a[i]找到有序位置j(0<=j<=i)，将a[i]插入在a[j]的位置上
问题：如何找到插入位置？
①顺序法定位插入位置——直接插入排序
②二分法定位插入位置——二分插入排序
③缩小增量多遍插入排序——希尔排序
9.3 交换排序
9.4 选择排序
9.5 归并排序
9.6 基数排序
9.7 外部排序
#endif

#include<iostream>
#include<stdio.h>
#define MAXSIZE 20//设记录不超过20
using namespace std;
typedef int KeyType;//设关键字为整型量（int型）
typedef struct RedType{//定义每个记录（数据元素）的结构
	KeyType key;//关键字
	//InfoType otherinfo;//其他数据项
}RedType;//Record Type
typedef struct SqList{//定义顺序表的结构
	RedType r[MAXSIZE + 1];//存储顺序表的向量
	//r[0]一般作哨兵或缓冲区
	int length;//顺序表的长度
}SqList;
//SqList T;
//RedType R;

//单链表结点申明
typedef struct LNode{
	int data;
	LinkList* next;
}LinkList;

//创建单链表
void Create_L(LinkList& L)
{
	//创建带头结点的单链表
	LinkList *L = (LinkList*)malloc(sizeof(LNode));
	//初始化链表
	L.next = NULL;
	L.data = 0;
}

//单链表插入元素算法——i位置插入e元素
void Insert_L(LinkList& L,int i,int e)
{
	LinkList* p;
	p = L.next;//p指向第一个元素
	LinkList* K = (LinkList*)malloc(sizeof(LNode));
	for (int j = 0; j < e&&p!=NULL; j++)//判断插入位置是否合法
	{
		p = p->next;
	}
	if (p = NULL)//如果p为空
	{
		K->data = e;
		p->next = K;
	}
	else//如果p不为空
	{
		K->data = e;
		K->next = p->next;
		p->next = K;
	}
}

//直接插入排序——采用链表的方式实现（自写）
void InsertSort_L(LinkList& L)
{
	LinkList* p = &L;//p为头指针
	LinkList* q = p->next;//q指向第一个元素
	LinkList* a = q;
	for (q; q != NULL; q = q->next)//从第一个结点开始遍历，q始终指向待排序的元素
	{
		for (a; a != q; a=a->next)//p作遍历找插入位置的作用
		{
			if (a->data > q->data)
				return;
			else//找到插入位置
			{
				delete(q);
				insert(a);
			}
		}
	}
}

//直接插入排序—采用顺序查找法插入位置（从后往前找）
//1、复制插入元素(i位)
//x=a[i];
//2、记录后移，查找插入位置
//for(j=i-1;j>=0&&x<a[j];j--)——效率太低，两次判断
//a[j+1]=a[j];
//3、插入到正确位置
//a[j+1]=x;

//直接插入排序—使用哨兵
//1、复制哨兵  
//L.r[0] = L.r[i];
//2、记录后移，查找插入位置
//for(j=i-1;L.r[0].key<L.r[j].key;--j)——优点：不用每轮都判断j>=0
//L.r[j+1]=L.r[j];
//3、插入到正确位置
//L.r[j+1]=L.r[0];
void InsertSort_S(SqList& L)
{
	int i;//表示无序部分第一个位置
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
}
//时间复杂度结论
//原始数据越接近有序，排序速度越快
//最好情况下 Tb(n)=O(n)
//最坏情况下（输入数据是逆有序的） Tw(n)=O(n^2)
//平均情况下，耗时差不多是最坏情况的一半 Te(n)=O(n^2)
//要提高查找速度
//--减少元素的比较次数
//--减少元素的移动次数

//折半查找法
//算法分析:
//①比较次数与初始排序状态无关。
//②移动次数与直接插入排序相同，依赖于对象的初始排列。
//--减少了比较次数，但没有减少移动次数
//--平均性能优于直接插入排序
//时间复杂度：O(n^2)
//空间复杂度：O(1)
//是一种稳定的排序方法
void BinsertSort(SqList& L)
{
	for (int i = 2; i <= L.length; ++i)//依次插入第2-第n个元素
	{
		L.r[0].key = L.r[i].key;//当前插入元素存到“哨兵”位置
		int low = 1;
		int high = i - 1;//采用二分查找法查找插入位置
		while (low <= high)
		{
			int mid = (low + high) / 2;
			if (L.r[0].key < L.r[mid].key)
				high = mid - 1;
			else
				low = mid + 1;
		}//循环结束，high+1则为插入位置
		for (int j = i - 1; j >= high + 1; --j)
			L.r[j + 1].key = L.r[j].key;//移动元素
		L.r[high + 1].key = L.r[0].key;//插入到正确位置
	}
}

//希尔排序算法（其中某一趟的排序操作）
//算法思想：如何在直接插入排序之前就让这个排序基本有序
void ShellSort(SqList& L, int dlta[], int t)
{
	//按增量序列dlta[0...t-1]对顺序表L作希尔排序
	for (int k = 0; k < t; ++k)
	{
		ShellInsert(L, dlta[k]);//一趟增量为dlta[k]的插入排序
	}
}

void ShellInsert(SqList& L, int dk)//dk为增量
{
	//对顺序表L进行一趟增量为dk的Shell排序，dk为步长因子
	for (int i = dk + 1; i <= L.length; ++i)
	{
		if (L.r[i].key < L.r[i - dk].key)
		{
			L.r[0].key = L.r[i].key;
			for (int j = i - dk; j > 0 && (L.r[0].key < L.r[j].key); j = j - dk)
				L.r[j + dk].key = L.r[j].key;
			L.r[j + dk].key = L.r[0].key;
		}
	}
}

int main(void)
{
	SqList T;
	
}
