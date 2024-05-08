#if 0
图（多对多）
1.1 图的定义和术语
--G=(V,E) 
Graph=(Vertex,Edge)
V:顶点（数据元素）的有穷非空集合
E:边的有穷集合（没有要求非空）
--有向图：每条边都是无方向的
--无向图：每条边都是有方向的
--完全图：任意两个点都有一条边相连（无向完全图、有向完全图）
无向完全图：n个顶点，任意两个顶点之间都有边，共有n(n-1)/2条边（Cn2）
有向完全图：n个顶点，任意两个顶点之间都有两条边，共有n(n - 1)条边（2*Cn2）
--稀疏图：有很少边或弧（有向图的边称为弧）的图（标准：e<nlogn）
--稠密图：有较多边或弧的图
--网：边、弧带权的图
--邻接：有边/弧相连的两个顶点之间的关系
存在（vi,vj）,则称vi和vj互为邻接点；
存在<vi,vj>，则称vi邻接到vj，vj邻接于vi
--关联（依附）：边/弧与顶点之间的关系
存在(vi,vj)/<vi,vj>，则称该边/弧关联于vi和vj
--顶点的度：与该顶点相关联的边的数目，记为TD(v)
在有向图中，顶点的度等于该顶点的入度与出度之和
顶点v的入度是以v为终点的有向边的条数，记作ID(v)
顶点v的出度是以v为始点的有向边的条数，记作OD(v)
--路径：接续的边构成的顶点序列
--路径长度：路径上边或弧的数目/权值之和
--回路（环）：第一个顶点和最后一个顶点相同的路径
--简单路径：除路径起点和终点可以相同外，其余顶点均不相同的路径
--简单回路（简单环）：除路径起点和终点可以相同外，其余顶点均不相同的路径
--连通图（强连通图）：在无（有）向图G = （V，{E}）中，若对任何两个顶点v,u都存在从v到u的路径，则称G是连通图（强连通图）
--权和网：图中边或弧所具有的相关数称为权。表明从一个顶点到另一个顶点的距离或耗费。带权的图称为网
--子图：设有两个图G = (V, {E})、G1 = {V1,{E1}},若V1⊆V，E1⊆E，则称G1是G的子图
--连通分量（强连通分量）：无向图G（有向图）的极大连通子图（极大强连通子图）称为G的连通分量（强连通分量）
极大（强）连通子图：该子图是G的（强）连通子图，将G的任何不在该子图中的顶点加入，子图不再（强）连通
--极小连通子图：该子图是G的连通子图，在该子图中删除任何一条边，子图都不再连通
--生成树：包含无向图G所有顶点的极小连通子图
--生成森林：对非连通图，由各个连通分量的生成树的集合
1.2 图的类型定义
ADT Graph{
	数据关系V:具有相同特性的数据元素的集合，称为顶点集
	数据关系R:R = {VR}
		VR = {<V,W>|<v,w>|v,w∈V ^p(v,w),<v,w>表示从v到w的弧，P(v,w)定义了弧<v,w>的信息}
	基本操作P:
		Create_Graph() : 图的创建操作
		初始条件：无
		操作结果：生成一个没有顶点的空图G
		GetVex(G,v)：求图中的顶点V的值
		初始条件：图G存在，v是图中的一个顶点
		操作结果：生成一个没有顶点的空图G
		...
		CreateGraph(&G,V,VR)
		初始条件：V是图的顶点集，VR是图中弧的集合
		操作条件：按V和VR的定义构造图G
		DFSTraverse(G)❤
		初始条件：图G存在
		操作结果：对图进行深度优先遍历
		BFSTraverse(G)❤
		初始条件：图G存在
		操作结果：对图进行广度优先遍历
}ADT Graph
#endif
//1、数组表示法——邻接矩阵❤
// --无向图的邻接矩阵表示法
// 分析1：无向图的邻接矩阵是对称的。
// 分析2：顶点i的度：第i行（列）中1的个数。
// 分析3：完全图的邻接矩阵中，对角元素为0，其余1。
// --有向图的邻接矩阵表示法
// 注：在有向图的邻接矩阵中
// 第i行含义：以结点Vi为尾的弧（即出度边）；
// 第i列含义：以结点Vi为头的弧（即入度边）。
// 分析1：有向图的邻接矩阵可能是不对称的。
// 分析2：顶点的出度=第i行元素之和
//		  顶点的入度=第i列元素之和
// --网（即有权图）的邻接矩阵表示法
//2、链式存储结构——多重链表（邻接表❤，邻接多重表，十字链表）
#include<iostream>
#include<stdio.h>
#define MaxInt 32767//表示极大值，即∞
#define MVNum 100//最大顶点数
using namespace std;
typedef char VerTexType;//设置顶点的数据类型为字符型
typedef int ArcType;//假设边的权值类型为整型
typedef struct AMGraph{
	VerTexType vexs[MVNum];//顶点表
	ArcType arcs[MVNum][MVNum];//邻接矩阵
	int vexnum, arcnum;//图的当前点数和边数
}AMGraph;//Adjacency Matrix Graph邻接矩阵图
int LocateVex(AMGraph G, VerTexType u)
{
	//图G中查找顶点u,存在则返回顶点表中的下标；否则返回-1
	int i = 0;
	while(i < G.vexnum)
	{
		if (u == G.vexs[i])
			return i;
		else
			i++;
	}
}
/*采用邻接矩阵表示法创建无向网*/
/*1、输入总顶点数和总边数
* 2、依次输入点的信息存入顶点表中
* 3、初始化邻接矩阵，使每个权值初始化为极大值
* 4、构造邻接矩阵
*/
int CreateUDN(AMGraph& G)//采用邻接矩阵表示法，创建无向网G
{
	//1、建立顶点表
	printf("请输入图的总顶点数和总边数：\n");
	cin >> G.vexnum >> G.arcnum;//输入总顶点数和总边数
	printf("请依次输入顶点的信息：\n");
	for (int i = 0;i < G.vexnum;++i)
	{
		cin >> G.vexs[i];//依次输入点的信息
	}
	for (int i = 0;i < G.vexnum;++i)//初始化邻接矩阵
	{
		for (int j = 0;j < G.vexnum;++j)
			G.arcs[i][j] = 0;//边的权值均置为0
	}
	//2、构造邻接矩阵
	VerTexType v1, v2;
	ArcType w;
	printf("请输入一条边所依附的顶点以及边的权值：\n");
	for (int k = 0;k < G.arcnum;++k)
	{
		cin >> v1 >> v2 >> w;//输入一条边所依附的顶点以及边的权值
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);//确定v1和v2在G中的位置
		G.arcs[i][j] = w;//边<v1,v2>的权值置为w
		G.arcs[j][i] = G.arcs[i][j];//置<v1,v2>的对称边<v2,v1>的权值为w
	}
	return 0;
}

bool visited[MVNum]; /* 访问标志的数组 */

/*采用邻接矩阵表示图的深度优先搜索遍历*/
void DFS(AMGraph G, int v)//图G为邻接矩阵类型，从图G的位置为v的顶点开始访问
{
	cout << G.vexs[v];//这里打印的是第v个顶点
	visited[v] = true;//访问第v个顶点
	for (int w = 0;w < G.vexnum;w++)//依次检查邻接矩阵v所在的行
	{
		if ((G.arcs[v][w] != 0) && (!visited[w]))//找当前顶点的弧存在的且邻接矩阵中的值不为0、没有被访问过的顶点
			DFS(G, w);
		//w是v的邻接点，如果w未访问，则递归调用DFS
	}
}


typedef int VRType;
//记录从顶点集U到V-U的代价最小的边的辅助数组定义：（为什么需要辅助数组不是很理解）
typedef struct closedge{
	VerTexType adjvex;
	VRType lowcost;
}closedge[MVNum];

//最小生成树——Prim算法
/*void MiniSpanTree_PRIM(AMGraph G, VerTexType u)
{
	//用Prim算法从第u个顶点出发构造网G的最小生成树T，输出T的各条边
	int k = LocateVex(G, u);
	for (int j = 0;j < G.vexnum;j++)//辅助数组初始化
	{
		if (j != k)
			//{adjvex,lowcost}
			closedge[k].lowcost = 0;
	}
}
*/
int main(void)
{
	AMGraph G;
	CreateUDN(G);
	//顺序输出邻接矩阵的值
	DFS(G, 0);
}
/*无向网->无向图：
* --初始化邻接矩阵时，w均为0
* --构造邻接矩阵时，w为1
* 无向网->有向网：
* --邻接矩阵是非对称矩阵，仅为G.arcs[i][j]赋值，无需为G.arcs[j][i]赋值
*/

