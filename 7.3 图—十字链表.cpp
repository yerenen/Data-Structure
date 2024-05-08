/*
* 图的存储结构
* --十字链表
* 在邻接表的基础上为了解决有向图求结点的度困难的缺点
*/
#include<iostream>
#include<stdio.h>
#define MVNum 100
using namespace std;

typedef int VerTexType;
typedef int InfoType;
typedef struct ArcNode{//边结点
	int tailvex, headvex;//该弧的尾和头顶点的位置
	ArcNode* hink,*tlink;//分别为弧头相同和弧尾相同的弧的链域
	InfoType info;//该弧相关信息
}ArcNode;
typedef struct VNode{//顶点结点
	VerTexType data;
	ArcNode* firstin,*firstout;//分别指向该顶点第一条入弧和出弧
}VNode;
typedef struct OLGraph{//图
	VNode vertices[MVNum];//表头向量
	int vexnum, arcnum;//有向图的当前顶点数和弧数
}OLGraph;
void CreateDG(OLGraph& G)//构造十字链表
{

}
int main(void)
{

}
