#if 0
9 排序
9.4 选择排序
每一趟在待排序元素中选取关键字最小（或最大）的元素加入有序子序列
9.4.1 简单选择排序
9.4.1.1 基本思想
在待排序的数据中选出最大（小）的元素放在其最终的位置
9.4.1.2 基本操作（此处找最小）
①首先通过n-1次关键字比较，从n个记录中找出关键字最小的记录，将它与第一个记录交换
②再通过n-2次比较，从剩余的n-1个记录中找出关键字次小的记录，将它与第二个记录交换
③重复上述操作，共进行n-1趟排序后，排序结束
9.4.2 堆排序(Heap)
9.4.2.1 堆的定义
--若n个元素的序列{a1,a2,...,an}满足
a(i)<=a(2i)       或        a(i)>=a(2i)
a(i)<=a(2i+1)               a(i)>=a(2i+1)
则分别称该序列{a1,a2,...,an}为小根堆和大根堆
--从堆的定义可以看出，堆实质是满足如下性质的完全二叉树：
二叉树中任一叶子结点均小于（大于）它的孩子结点
--大根堆：完全二叉树中，根>=左、右
--小根堆：完全二叉树中，根<=左、右
9.4.2.2 堆排序
若在输出堆顶的最小值（最大值）后，使得剩余n-1个元素的序列重又建成一个堆，则得到n个元素的次小值（次大值）...如此反复，便能得到一个有序序列，这个过程称之为堆排序。
9.4.2.3 实现堆排序需解决的两个问题
①如何由一个无序序列建成一个堆？
②如何在输出堆顶元素后，调整剩余元素为一个新的堆？
9.4.2.4 堆调整——如何在输出堆顶元素后，调整剩余元素为一个新的堆？
①小根堆
a.输出堆顶元素后，以堆中最后一个元素替代之
b.然后将根结点值与左、右子树的根结点值进行比较，并与其中小者进行交换
c.重复上述操作，直至叶子结点，将得到新的堆，称这个从堆顶至叶子的调整过程为“筛选”
②大根堆（类似小根堆）
9.4.2.5 堆建立——如何由一个无序序列建成一个堆
显然：
单结点的二叉树是堆；
在完全二叉树中所有以叶子结点（序号i>n/2）为根的子树是堆
9.4.2.6 算法效率分析
结论1：一个结点，每“下坠”一层，最多只对比关键字两次
若树高为h，某结点在第i层，则将这个结点向下调整最多只需要“下坠”h-i层，关键字对比次数不超过2(h-i)层
n个结点的完全二叉树树高h = log2n + 1
第i层最多有2^(i-1)个结点，而只有第1-(h-1)层的结点才有可能需要“下坠”调整
将整棵树调整为大根堆，关键字对比次数不超过4n
结论2：建堆的过程，关键字对比次数不超过4n，建堆时间复杂度=O(n)
9.4.2.7 稳定性分析
堆排序是不稳定的
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

//简单排序算法
//时间复杂度：O(n^2)
//--记录移动次数
//①最好情况：0
//②最坏情况：3(n-1)
//--比较次数：无论待排序处于什么状态，选择排序所需进行的“比较”次数都相同
//--算法稳定性：
//简单选择排序是不稳定排序(但可以在算法基础上把它变成稳定排序)
//空间复杂度：O(1)
void SelectSort(SqList& L)
{
	for (int i = 1; i < L.length; ++i)
	{
		int k = i;//k记录顺序表最小值所在位置
		for (int j = i + 1; j <= L.length; j++)
		{
			if (L.r[j].key < L.r[k].key)//记录最小值位置
				k = j;//更新k
		}
		if (k != i)//说明最小值不在第一位
		{
			int temp = L.r[k].key;//临时值
			L.r[k].key = L.r[i].key;//交换值
			L.r[i].key = temp;
		}
	}
}

//堆排序中堆调整的算法❤——大根堆
//可以看出：对一个无序序列反复“筛选”就可以得到一个堆：
//即：从一个无序序列建堆的过程就是一个反复“筛选”的过程
void HeapAdjust(SqList &L, int k, int len)
{
	L.r[0] = L.r[k];//R[0]暂存子树的根结点
	for (int i = 2 * k; i <= len;i = i * 2)//沿key较大的孩子结点向下筛选
	{
		if (i < len && L.r[i].key < L.r[i + 1].key)
			i++;//取key较大的子节点的下标
		if (L.r[0].key >= L.r[i].key)
			break;//筛选结束
		else//如果有较大的值在子结点
		{
			L.r[k].key = L.r[i].key;//将R[i]调整到双亲结点上
			k = i;//修改k值，以便继续向下筛选
		}
	}//for
	L.r[k] = L.r[0];//将筛选结点的值放入最终位置
}//HeadAdjust

//建立大根堆
//时间复杂度：O(n)
void BuildMaxHeap(SqList &L, int len)
{
	for (int i = len / 2; i > 0; i--)//从后往前调整所有非终端结点
	{
		HeapAdjust(L, i, len);
	}
}

//交换两个元素
void swap(int &i, int &e)
{
	int temp = e;
	e = i;
	i = temp;
}

//堆排序的完整逻辑
//堆排序的时间复杂度 = O(n) + O(nlog2n) = O(nlog2n)
//堆排序的空间复杂度 = O(1)
void HeapSort(SqList &L, int len)
{
	BuildMaxHeap(L, len);//初始建堆   
	for (int i = len; i > 1; i--)//n-1趟的交换和建堆过程
	{
		swap(L.r[i].key, L.r[1].key);//堆顶元素和堆底元素交换
		HeapAdjust(L, 1, i - 1);//把剩余的待排序元素整理成堆排序
	}
}

//堆排序的插入操作（自写）
//时间复杂度：O(log2n)]=
void Insert_Heap(SqList& L, int e)
{
	if (L.length >= MAXSIZE + 1)//判断插入位置是否合法
		return;
	else
	{
		L.r[L.length + 1].key = e;//插入元素，产生无序序列
		L.length++;
		HeapSort(L,L.length);
	}
}

int LocateNum(SqList& L, int e)
{
	int i = 1;
	while (L.r[i].key != e)
		i++;
	return i;
}

//堆排序的删除操作（自写）
//时间复杂度：O(log2n)
void Delete_Heap(SqList& L, int e)//删除顺序表为e的元素
{
	int i = LocateNum(L, e);
	if (L.length < 0)//判断删除是否合法
		return;
	else
	{
		L.r[i] = L.r[L.length];
		L.length--;
		HeapSort(L,L.length);
	}
}

int main(void)
{
	int e,n;
	SqList L;
	//初始化顺序表
	for (int i = 0; i < MAXSIZE+1; i++)
	{
		L.r[i].key = 0;
	}
	//给顺序表赋值
	cout << "请输入顺序表长度：" << endl;
	cin >> L.length;
	cout << "请输入所需排序的元素：" << endl;
	for (int i = 1; i < L.length+1; i++)
	{
		cin >> L.r[i].key;
	}
	cout << "简单选择排序后的结果：" << endl;
	SelectSort(L);
	for (int i = 1; i < L.length + 1; i++)
	{
		cout << L.r[i].key<<" ";
	}
	cout << endl;
	cout << "堆排序后的结果：" << endl;
	HeapSort(L, L.length);
	for (int i = 1; i < L.length + 1; i++)
	{
		cout << L.r[i].key << " ";
	}
	cout << endl;
	cout << "请输入顺序表所需插入元素：" << endl;
	cin >> e;
	Insert_Heap(L, e);
	cout << "堆排序插入元素后的结果：" << endl;
	for (int i = 1; i < L.length + 1; i++)
	{
		cout << L.r[i].key << " ";
	}
	cout << endl;
	cout << "请输入顺序表所需删除的元素位序：" << endl;
	cin >> n;
	Delete_Heap(L, n);
	cout << "堆排序删除元素后的结果：" << endl;
	for (int i = 1; i < L.length + 1; i++)
	{
		cout << L.r[i].key << " ";
	}
	return 0;
}