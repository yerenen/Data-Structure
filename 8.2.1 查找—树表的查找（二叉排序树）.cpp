/*
* 8 查找
* 8.2 树表的查找
* 8.2.1 为什么会研究树表的查找
* 当表插入、删除操作频繁时，为了维护表的有序性，需要移动表中很多记录。
* 如何保持二分查找的效率，并且使删除、插入操作便捷
* ——改用动态查找表（几种特殊的树）
* 8.2.2 查找结构
* 表结构在查找过程中动态生成，对于给定值key：
* 若表中存在，则成功返回
* 否则，插入关键字等于key的记录
* 8.2.3 树表需要研究的内容
* 二叉排序树
* 平衡二叉树
* 红黑树
* B-树
* B+树
* 键树
* 8.2.4 二叉排序树
* 二叉排序树（Binary Sort Tree）又称为二叉搜索树、二叉查找树
* --定义：
* 二叉排序树或是空树，或是满足如下性质的二叉树：
* （1）若其左子树非空，则左子树上所有结点的值均小于根结点的值
* （2）若其右子树非空，则右子树上所有节点的值均大于根结点的值
* （3）其左右子树本身又各是一棵二叉排序树
* --思考：
* 中序遍历二叉排序树
* 结果有什么规律？
* --性质：
* 中序遍历非空的二叉排序树所得到的数据元素序列是一个按关键字排列的递增有序序列
* --操作：查找
* 若查找的关键字等于根结点，成功
* 否则：
* 若小于根结点，查其左子树
* 若大于根结点，查其右子树
* 在左右子树上的操作类似
* --问题：如何提高形态不均衡的二叉排序树的查找效率？
* 解决办法：做“平衡化”处理，即尽量让二叉树的形状均衡！
* （下一节）
*/
#include<iostream>
#include<stdio.h>
using namespace std;
typedef int KeyType;
typedef int InfoType;
typedef struct ElemType{//查找表
	KeyType key;//关键字项
	InfoType otherinfo;//其他数据域
}ElemType;
typedef struct BSTNode{//二叉链表
	ElemType data;//数据域
	struct BSTNode* lchild, * rchild;//左右孩子指针
}BSTNode,*BSTree;
BSTree T;//定义二叉排序树T
/*
* 算法8.5 二叉排序树的递归查找
* --算法思想：
* （1）若二叉排序树为空，则查找失败，返回空指针
* （2）若二叉排序树非空，将给定值key与根结点的关键字T->data.key作比较：
* ①若key等于T->data.key，则查找成功返回根结点地址
* ②若key小于T->data.key，则进一步查找左子树
* ③若key大于T->data.key，则进一步查找右子树
* --查找分析：
* （1）二叉排序树上查找某关键字等于给定值的结点过程，其实就是走了一条从根到该结点的路径
* 比较的关键字次数 = 此结点所在层次数
* 最多的比较次数 = 树的深度
* （2）含有n个结点的二叉排序树的平均查找长度和树的形态有关
* ①最好情况：
* ASL = log2(n+1)-1
* 树的深度：[log2n]+1与折半查找中的判定树相同
* (形态比较均衡)查找效率:O(log2n)
* ②最坏情况：
* ASL = (n+1)/2
* 树的深度：n
* （插入的n个元素从一开始就有序，变成单支树的形态）查找效率与顺序查找情况相同：O(n)
*/
BSTree SearchBST(BSTree T, KeyType key)
{
	if ((!T) || key == T->data.key)
		return T;
	else if (key < T->data.key)
		return SearchBST(T->lchild, key);//在左子树中继续查找
	else
		return SearchBST(T->rchild, key);//在右子树中继续查找
}//SearchBST
/*算法8.6：二叉排序树的操作-插入*/
int BSTInsert(BSTree& T, KeyType key)
{
	if (T == NULL)//当前为空指针，说明找到插入位置，创建新结点进行插入
	{
		T = (BSTNode*)malloc(sizeof(BSTNode));//创建新结点
		T->lchild = T->rchild = NULL;
		T->data.key = key;//将待插关键字存入新结点中；插入成功，返回1
		return 1;
	}
	else//如果结点不空
	{
		if (key == T->data.key)//关键字已存在于树中，插入失败，返回0
		{
			return 0;
		}
		else if (key < T->data.key)
			return BSTInsert(T->lchild, key);
		else
			return BSTInsert(T->rchild, key);
	}
}
/*算法8.7：二叉排序树的操作-删除*/
//从二叉排序树中删除一个结点，不能把该结点为根的子树都删去，只能删掉该结点，并且还应保证删除后所得的二叉树仍然满足二叉排序树的性质不变
//由于中序遍历二叉排序树可以得到一个递增有序的序列。那么，在二叉排序树中删去一个结点相当于删去有序序列的一个结点
//--将因删除结点而断开的二叉链表重新链接起来
//--防止重新链接后树的高度增加
//①被删除的结点是叶子结点：直接删去该结点
//②被删除的结点只有左子树或者只有右子树，用其左子树或者右子树替换它（结点替换）
//③被删除的结点既有左子树，也有右子树
/*代码考察可能性不高，会手工操作即可*/

/*算法8.8：二叉排序树的操作-构造*/
void CreateBST(BSTree& T, ElemType key[], int n)
{
	int i;
	T = NULL;//将树清空
	for (int i = 0;i < n;i++)//调用插入函数，逐个插入关键字
	{
		BSTInsert(T, key[i].key);
	}
}
int main(void)
{
	BSTree T;
	int n = 5;
	ElemType key[5];
	CreateBST(T, key, n);
}
/*
体检
offer
盖章
资料
光大
材料-身份证1:1（正反）+学位证+户口本个人页+学历证+离职证明
填写资料
合同
6.5k 1k 1k 300-600 住宿
背调
5.10日
*/