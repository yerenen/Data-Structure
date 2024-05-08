#if 0
9 排序
9.3 交换排序
9.3.1 基本思想
两两比较，如果发生逆序则交换，直到所有记录都排好序为止。
9.3.2 常见的交换排序方法
--冒泡排序（O（n^2））
--快速排序（O（nlog2n））
9.3.3 冒泡排序
9.3.3.1 基本思想
每趟不断将记录两两比较，并按“前小后大”规则交换
9.3.4 快速排序——改进的交换排序
9.3.4.1 基本思想(递归)
①任取一个元素（如：第一个）为中心（pivot）
②所有比它小的元素一律往前放，比它大的元素一律后放
③形成左右两个子表
④对各子表重新选择中心元素并以此规则调整
⑤直到每个子表的元素只剩一个
9.3.4.2 特点
①每一趟的子表的形成是采用从两头向中间交替式逼近法
②由于每趟中对各子表的操作都相似，可采用递归算法
#endif

#include<iostream>
#include<stdio.h>
#define MAXSIZE 20//设记录不超过20
using namespace std;
typedef int KeyType;//设关键字为整型量（int型）
typedef struct RedType {//定义每个记录（数据元素）的结构
	KeyType key;//关键字
	//InfoType otherinfo;//其他数据项
}RedType;//Record Type
typedef struct SqList {//定义顺序表的结构
	RedType r[MAXSIZE + 1];//存储顺序表的向量
	//r[0]一般作哨兵或缓冲区
	int length;//顺序表的长度
}SqList;
//SqList T;
//RedType R;

//冒泡排序算法（优化前）
//优点：每趟结束时，不仅能挤出一个最大值到最后面位置，还能同时部分理顺其他元素；
//如何提高效率？
//一旦某一趟比较时不出现记录交换，说明已排好序了，就可以结束本算法
void bubble_sort(SqList& L)
{
	int n = L.length;
	int m, i, j;
	RedType x;//交换时临时存储
	for (int m = 1; m <= n - 1; m++)//总共m趟
	{
		for (int j = 1; j <= n - m; j++)
		{
			if (L.r[j].key > L.r[j + 1].key)//发生逆序
			{
				x = L.r[j];//交换
				L.r[j] = L.r[j + 1];
				L.r[j + 1] = x;
			}//endif
		}//for
	}
}

//冒泡排序算法（优化后）
//1、时间复杂度：
//①最好情况（排序本就是正序）：
//比较次数：n-1
//移动次数：0
//时间复杂度：O(n)
//②最坏情况（排序是逆序）：
//比较次数：n(n-1)/2
//移动次数：3n(n-1)/2
//时间复杂度：O(n^2)
//③平均时间复杂度：O(n^2)
//辅助空间：S(n) = O(1)
//2、特点：冒泡排序是稳定的
void bubble_sort_best(SqList& L)//改进后的冒泡排序算法
{
	int n = L.length;
	int m, i, j, flag = 1;//flag作为是否有交换的记录
	RedType x;
	for (int m = 1; m <= n - 1 && flag == 1; m++)
	{
		flag = 0;
		for (int j = 1; j <= m; j++)
		{
			if (L.r[j].key > L.r[j + 1].key) {//发生逆序
				flag = 1;//发生交换，flag置为1，若本趟没发生交换，flag保持为0
				x = L.r[j];
				L.r[j] = L.r[j + 1];
				L.r[j + 1] = x;//交换
			}//endif
		}//for
	}
}

//找中心点的位置
int Partition(SqList &L, int low, int high)
{
	L.r[0] = L.r[low];
	int pivotkey = L.r[low].key;
	while (low < high)
	{
		while (low < high && L.r[high].key >= pivotkey)//如果high指针指向的值大于pivotkey
			--high;//元素可以不用动，high指针左移
		L.r[low] = L.r[high];//直到遇到high指针指向的值小于pivot，则赋给low指针
		while (low < high && L.r[low].key <= pivotkey)
			++low;
		L.r[high] = L.r[low];
	}
	L.r[low] = L.r[0];
	return low;
}

//对顺序表L快速排序
//快速排序算法分析
//①时间复杂度：平均时间复杂度为O(nlog2n)
//Qsort()：O(log2n)
//Partition()：O(n)
//②空间复杂度
//快速排序不是原地排序
//在平均情况下：需要用O(logn)的栈空间
//最坏情况下：栈空间可达O(n)
//③稳定性
//快速排序是一种不稳定的排序方法
//④划分元素的选取是影响时间性能的关键
//输入数据次序越乱，所选划分元素的值的随机性越好，排序速度越快，快速排序不是自然排序方法
//改变划分元素的选取方法，至多只能改变算法平均情况下的世界性能，无法改变最坏情况下的时间性能。即最坏情况下，快速排序的时间复杂度总是O(n^2)
void QSort(SqList& L, int low, int high)
{
	if (low < high) {//长度大于1
		int pivotloc = Partition(L, low, high);
		//将L.r[low...high]一分为二，pivotloc为枢轴元素排好序的位置
		QSort(L, low, pivotloc - 1);//对低子表递归排序
		QSort(L, pivotloc + 1, high);//对高子表递归排序
	}//endif
}//QSort

int main(void)
{
	SqList L;
	int n = MAXSIZE;
	//对顺序表初始化
	for (int i = 1; i < MAXSIZE+1; i++)
	{
		L.r[i].key = n;
		n--;
	}
	L.length = MAXSIZE + 1;
	//输出初始顺序表
	cout << "初始顺序表为：" << endl;
	for (int i = 1; i < MAXSIZE + 1; i++)
	{
		cout << L.r[i].key << " ";
	}
	cout << endl;
	//快速排序
	QSort(L, 1, L.length);
	cout << "使用快速排序后顺序表为：" << endl;
	for (int i = 1; i < MAXSIZE + 1; i++)
	{
		cout << L.r[i].key<<" ";
	}
	cout << endl;
	//冒泡排序（优化前）
	bubble_sort(L);
	cout << "使用冒泡排序后顺序表为：" << endl;
	for (int i = 1; i < MAXSIZE + 1; i++)
	{
		cout << L.r[i].key << " ";
	}
	cout << endl;
	//冒泡排序（优化后）
	bubble_sort_best(L);
	cout << "使用优化后的冒泡排序后顺序表为：" << endl;
	for (int i = 1; i < MAXSIZE + 1; i++)
	{
		cout << L.r[i].key << " ";
	}
	return 0;
}