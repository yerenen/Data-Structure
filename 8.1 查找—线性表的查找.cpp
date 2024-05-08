/*
* 8.1 查找
* 8.1.1 问题：在哪里找？
* 在查找表找（新的数据结构）
* 查找表是同一类型的数据元素（或记录）构成的集合。由于“集合”中的数据元素之间存在着松散的关系，因此查找表是一种应用灵便的结构（没有严格的前驱和后继关系）
* 8.1.2 问题；什么查找？
* 根据给定的某个值，在查找表中确定一个其关键字等于给定值的数据元素或（记录）
* --关键字：用来标识一个数据元素（或记录）的某个数据项的值
* ----主关键字：可唯一的标识一个记录的关键字是主关键字
* ----次关键字：反之，用以识别若干记录的关键字是次关键字
* 8.1.3 问题：查找成功否？
* --若查找表中存在这样一个记录，则称“查找成功”
* 查找结果给出整个记录的信息，或指示该记录在查找表中的位置
* --否则称“查找不成功”
* 查找结果给出“空记录”或“空指针”
* 8.1.4 问题：查找目的是什么？
* 对查找表经常进行的操作：
* --查询某个“特定的”数据元素是否在查找表中
* --检索某个“特定的”数据元素的各种属性
* --在查找表中插入一个数据元素
* --删除查找表中的某个数据元素
* 8.1.5 问题：查找表怎么分类？
* 查找表可分为两类：
* --静态查找表：
* 仅作“查询”（检索）操作的查找表
* --动态查找表
* 作“插入”和“删除”操作的查找表
* 有时在查询之后，还需要将“查询”结果为“不在查找表中”的数据元素插入到查找表中；或者，从查找表中删除其“查询”结果为“在查找表中”的数据元素，此类表为动态查找表
* 8.1.5 问题：如何评价查找算法？
* 查找算法的评价指标：
* 关键字的平均比较次数，也称为平均查找长度ASL（Average Search Length）
* 8.1.6 问题：查找过程中我们要研究什么？
* 查找的方法取决于查找表的结构，即表中数据元素是依何种关系组织在一起的
* 由于对查找表来说，在集合中查询或检索一个“特定的”数据元素时，若无规律可循，只能对集合中的元素一一加以辨认直至找到为止
* 而这样的“查询”或“检索”是任何计算机应用系统中使用频率很高的操作，因此设法提高查找表的效率，是问题讨论的出发点
* 为提高查找效率，一个办法就是在构造查找表时，在集合中的数据元素之间人为地加上某种确定的约束关系
* 8.2 线性表的查找
* --顺序查找（线性查找）
* 应用范围：
* ①顺序表或线性链表表示的静态查找表
* ②表内元素之间无序
* 优点：算法简单，逻辑次序无要求，且不同存储结构都适用
* 缺点：ASL太长，时间效率太低
* --折半查找（二分或对分查找）
* ①每次将待查记录所在区间缩小一半
* ②必须是有序表
* 优点：效率比顺序查找高
* 缺点：只适用于有序表，且限于顺序存储结构(对线性链表无效)
* --分块查找
* 优点：插入和删除比较容易，无需进行大量移动
* 缺点：要增加一个索引表的存储空间并对初始索引表进行排序运算
* 适用情况：如果线性表既要快速查找又经常动态变化，则可采用分块查找
*/
#include<iostream>
#include<stdio.h>
#define MAXSIZE 10
#define maxsize 3
using namespace std;
typedef int KeyType;
typedef struct ElemType{//查找表数据结构
	KeyType key;//关键字域
	//其他域
}ElemType;
typedef struct SSTable{//顺序表结构类型定义
	ElemType* R;//表基址
	int length;//表长
}SSTable;//Sequential Search Table
SSTable ST;

typedef struct IndexElem{//索引元素数据结构
	KeyType key;//表内元素为KeyType类型
	int low, high;//记录某块中第一个和最后一个元素的位置
}IndexElem;
IndexElem index[maxsize];//定义索引表，maxsize是已定义的常量

/*
* 算法8.1：顺序查找（初版）
* 在顺序表ST中查找值为key的数据元素（从最后一个元素开始比较）
*/
int Search_Seq(SSTable ST, KeyType key)
{
	//若成功则返回其位置信息，否则返回0
	for (int i = ST.length;i >= 1;--i)
	{
		if (ST.R[i].key == key)
			return i;
		return 0;
	}
}
/*
* 算法8.1：顺序查找（其他形式）
*/
int Search_Seq2(SSTable ST, KeyType key)
{
	for (int i = ST.length;ST.R[i].key!=key;--i)
	{
		if (i <= 0)
			break;
		if (i > 0)
			return i;
		else
			return 0;
	}
}
/*
* 算法8.1：顺序查找（其他形式）
*/
int Search_Seq2_1(SSTable ST, KeyType key)
{
	int i = ST.length;
	//每执行一次循环都要进行两次比较，是否能改进？
	for (i;ST.R[i].key != key && i > 0;--i);
		if (i > 0)
			return i;
		else
			return 0;
}
/*
* 算法8.2：顺序查找（改进版）
* --改进：把待查关键字key存入表头（“哨兵”、“监视哨”），从后往前逐个比较，可免去查找过程中每一步都要检测是否查找完毕，加快速度
* --时间效率分析：
* 比较次数和key位置有关：
* 查找第i个元素，需要比较n-i+1次
* 查找失败，需比较n+1次
* --时间复杂度：O(n)
* ASL=1/n*[∑(n-i+1)]=(1+2+...+n)/n=(n+1)/2
* --空间复杂度:O(1)
*/
int Search_Seq3(SSTable ST, KeyType key)
{
	ST.R[0].key = key;
	int i = ST.length;
	for (i;ST.R[i].key != key;--i);
	return i;
}
/*
算法8.3 折半查找（非递归算法）
--设表长为n,low、high和mid分别指向待查元素所在区间的上界、下界和中点，key为给定的要查找的值
①初始时，令low=1,high=n,mid=[(low+high)/2]
②让k与mid指向的记录比较
--若key=R[mid].key，则查找成功
--若key<R[mid].key，则high=mid-1
--若key>R[mid].key，则low=mid+1
③重复以上操作，直至low>high时，查找失败
*/

/*
* 折半查找的性能分析—判定树
* --1、查找成功
* 比较次数 = 路径上的结点数 = 结点所在的层次
* 比较次数 <= 树的深度 = [log2n]+1
* --2、查找不成功
* 比较次数 = 路径上的内部结点数
* 比较次数 <= [log2n]+1
* --3、圆形—内结点，代表查找成功的情况
* --4、矩形—外结点，代表查找不成功的情况
* --5、性能分析
* 平均查找长度ASL（成功时）：
* 设表长n=2^n-1，则h=log2(n+1)(此时，判定树为深度=h的满二叉树)，且表中每个记录的查找概率相等：Pi=1/n
* 则：ASL = log2(n+1)-1（n > 50）
*/
int Search_Bin(SSTable ST,KeyType key)
{
	int low = 1;
	int high = ST.length;//置区间初值
	while (low <= high)//当low > high，循环停止
	{
		int mid = (low + high) / 2;//计算中间位置
		if (ST.R[mid].key == key)
			return mid;//找到待查元素
		else if (key < ST.R[mid].key)//没找到，则缩小查找区间
			high = mid - 1;//继续在前半区间进行查找
		else
			low = mid + 1;//继续在后半区间进行查找
	}
	return 0;//顺序表不存在待查元素
}//Search_Bin

/*算法8.3 折半查找——递归算法*/
int Search_Bin2(SSTable ST, KeyType key, int low, int high)
{
	if (low > high)
		return 0;//查找不到时返回0
	int mid = (low + high) / 2;
	if (ST.R[mid].key == key)
		return mid;//找到了
	else if (ST.R[mid].key > key)//没找到
		Search_Bin2(ST, key, mid+1, high);//递归，在前半区域进行查找
	else
		Search_Bin2(ST, key, low , mid-1);
	return -1;
}
/*
* 算法8.4 分块查找（索引顺序查找）
* 条件：
* 1、将表分成几块，且表或者有序，或者分块有序；
* 若i<j，则第j块中所有记录的关键字均大于第i块中的最大关键字
* 2、建立“索引表”（每个结点含有最大关键字域和指向本块第一个结点的指针，且按关键字有序）
* 3、查找过程
* 先确定待查记录所在块（顺序或折半查找），再在块内查找（顺序查找）
*/

/*
* 分块查找的性能分析
* 设一共n个元素，每块内部s个记录，则一共有n/s块
* 查找效率：ASL = L(b)+L(w)
* --L(b):对索引表查找的ASL
* --L(w):对块内查找的ASL
* ASL = log2(n/s+1)+s/2
*/
int main(void)
{
	ST.length = MAXSIZE;
	ElemType R[MAXSIZE];
	for (int i = 1;i < MAXSIZE;i++)
	{
		R[i].key = i;//没搞出来，为啥不能直接给顺序表的数组赋值？
		//懂了，因为顺序表存的是ElemType* R。即ElemType类型的第一个地址（如果ElemType是声明了一个数组）
	}
	ST.R = R;
	cout << ST.R << endl;
	cout << "顺序查找-key为2的值在哪个位置：" << endl;
	cout << Search_Seq3(ST, 2) << endl;
	cout << "折半查找-key为2的值在哪个位置：" << endl;
	cout << Search_Bin2(ST, 2, 0, 9) <<endl;
}