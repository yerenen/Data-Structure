#if 0
树
1.3 哈夫曼树（最优二叉树）
1.3.1 哈夫曼树的基本概念
--路径：从树中一个结点到另一个结点之间的分支构成这两个结点间的路径。
--结点的路径长度：两结点间路径上的分支数。
--树的路径长度：从树根到每一个节点的路径长度之和。记作：TL
结论：结点数目相同的二叉树中，完全二叉树是路径长度最短的二叉树。
--权（Weight）：将树中结点赋给一个有着某种含义的数值，则这个数值称为该结点的权。
--结点的带权路径长度：从根结点到该结点之间的路径长度与该结点的权的乘积。
--树的带权路径长度（WPL）：树中所有叶子结点的带权路径长度之和。
哈夫曼树：最优树（带权路径长度（WPL）最短的树）
“带权路径长度最短”是在“度相同”的树中比较而得的结果，因此有最优二叉树、最优三叉树之称等。
因为构造这种树的算法是由哈夫曼教授于1952年提出，所以被称为哈夫曼树，相应的算法被称为哈夫曼算法。
1.3.2 构造哈夫曼树
哈夫曼算法口诀：
--构造森林全是树
--选用两小造新树
--删除两小添新人
--重复2, 3剩单根
特点：包含n个叶子结点的哈夫曼树中共有2n - 1个结点；
哈夫曼树的结点度数为0或2，没有度为1的结点；
包含n棵树的森林要经过n - 1次合并才能形成哈夫曼树，共产生n - 1个新结点。
1.3.3 总结
--在哈夫曼算法中，初始时有n棵二叉树，要经过n - 1次合并最终形成哈夫曼树。
--经过n - 1次合并产生n - 1个新结点，且这n - 1个新结点都是具有两个孩子的分支节点。
--可见：哈夫曼树中共有2n - 1个结点，且其所有的分支节点的度均不为1。
#endif
/*顺序存储结构——一维结构数组*/
#include<iostream>
#include<stdio.h>
using namespace std;
typedef struct {
	int weight;
	int parent, lch, rch;
}HTNode,*HuffmanTree;
/*在哈夫曼树中挑选最小的两个数值*/
void Select(HuffmanTree HT, int &s1, int &s2)
{
	int e = INT_MAX;
	int i = 1;
	s1 = 1;//计数器
	while(i<=HT[0].weight)
	{
		if (HT[i].parent != 0)
			i++;
		else
		{
			if (e < HT[i].weight)//如果e小于HT[i].weight，则不需要动
				i++;
			else
			{
				e = HT[i].weight;
				s1 = i;
				i++;
			}
		}
	}
	int f = INT_MAX;
	int j = 1;
	s2 = 1;
	while (j <= HT[0].weight)
	{
		if (j == s1 || HT[j].parent != 0)
			j++;
		else
		{
			if (f < HT[j].weight)//如果f小于HT[j].weight，则不需要动
				j++;
			else 
			{
				f = HT[j].weight;
				s2 = j;
				j++;
			}
		}	
	}
}
/*构造哈夫曼树*/
//1、申请一片数组存储空间（初始元素有n个，最终数组一共2n-1个元素，所以申请2n个元素数的空间。其中0位数组不用，我是拿来存放数组长度）
//2、初始化数组，将2n-1个元素的lch,rch,parent置为0
//3、输入前n个元素的weight值
//4、合并产生n-1个结点——构造Huffman树（其中注意每次选择的是双亲域为0且权值最小的两个结点，此处Select函数易错，且数组长度HT[0].weight可以在此处随着for循环函数递增）
void CreatHuffmanTree(HuffmanTree &HT, int n)
{
	int s1 = 0;
	int s2 = 0;
	if (n <= 1)
		return;
	int m = 2 * n - 1;//数组共2n-1个元素
	HT = new HTNode[m + 1];//申请一片存储空间：0号单元未用，HT[m]表示根结点
	if (HT == nullptr) {
		// 内存分配失败，处理错误
		cout << "Error: Memory allocation failed." << endl;
		return; // 或者抛出异常等其他处理
	}
	for (int i = 1;i <= m;++i)//初始化：将2n-1个元素的lch,rch,parent置为0
	{
		HT[i].lch = 0;
		HT[i].rch = 0;
		HT[i].parent = 0;
	}
	for (int i = 1;i <= n;++i)
	{
		cin >> HT[i].weight;//输入前n个元素的weight值
	}
	HT[0].weight = n;//自己定义：哈夫曼树的第0位存哈夫曼树的长度
	for (int i = n + 1;i <= m;i++)//合并产生n-1个结点——构造Huffman树
	{
		Select(HT, s1, s2 );//在HT[k]（1<=k<=i-1）中选择两个其双亲域为0，且权值最小的结点，并返回它们在HT中的序号s1和s2
		HT[s1].parent = i;
		HT[s2].parent = i;//表示从F中删除s1,s2
		HT[i].lch = s1;
		HT[i].rch = s2;//s1,s2分别作为i的左右孩子
		HT[i].weight = HT[s1].weight + HT[s2].weight;//i的权值为左右孩子权值值和
		HT[0].weight++;
	}
}
void scanHuffmanTree(HuffmanTree HT)
{
	for (int i = 1;i <= HT[0].weight;i++)
	{
		cout << HT[i].weight<<",";
	}
}
int main(void)
{
	int s1 = 0;
	int s2 = 0;
	HuffmanTree HT;
	cout << "请输入前n个元素的weight值：" << endl;
	CreatHuffmanTree(HT, 5);
	cout << "返回前n个元素最小的两个权值对应的数组位序：" << endl;
	Select(HT, s1, s2);
	cout << s1 << s2 << endl;
	cout << "遍历哈夫曼树：" << endl;
	scanHuffmanTree(HT);
	cout << endl;
	cout << "哈夫曼树数组长度为：" << endl;
	cout << HT[0].weight << endl;
}