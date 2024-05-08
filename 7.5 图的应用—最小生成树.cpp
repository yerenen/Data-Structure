/*
* 7.5 图的应用
* 7.5.1 最小生成树
* --生成树：连通且边数最少达到没有回路
* --最小生成树：给定一个无向网络，在该网的所有生成树中，使得各边权值之和最小的那颗生成树称为该网的最小生成树，也叫最小代价生成树。
* --最小生成树的典型应用：
* 想在n个城市建立通信网，则n个城市应铺n-1条线路；
* 但因为每条线路都会有对应的经济成本，而n个城市最多有n(n-1)/2条线路，那么，如何选择n-1条线路，使得总费用最少？此处的费用可理解为权值。
* --抽象出的数学模型：（显然此处的连通网是一个生成树）
* 顶点——表示城市，有n个
* 边——表示线路，有n-1条
* 边的权值——表示线路的经济代价
* 连通网——表示n个城市间通信网*/

/*思路：尝试用邻接矩阵构造无向网，再遍历构造最小生成树*/
#include<iostream>
#include<stdio.h>
#define MVNum 100

typedef char VerTexType;
using namespace std;
typedef struct AMGraph{//邻接矩阵结构体
	VerTexType vertices[MVNum];//顶点表
	int Graph[MVNum][MVNum];//权值表
	int vexnum,arcnum;
}AMGraph;

//在邻接矩阵中找到顶点在顶点表中对应的位序
int LocateVex(AMGraph G,VerTexType u)
{
	for (int i = 0;i < G.vexnum;i++)
	{
		if (G.vertices[i] == u)
			return i;
	}
}
//构造最小生成树Minimun Spanning Tree
//MST性质：
//在生成树的构造过程中，图中n个顶点分属两个集合：
//已落在生成树上的顶点集：U
//尚未落在生成树上的顶点集：V-U
//接下来则应在所有连通U中顶点和V-U中顶点的边中选取权值最小的边。

//构造最小生成树方法一：Prim算法（从一个集合包括一个顶点开始，找权值最小的边，将邻接点包括进点集合，依次遍历）
//算法思想：
//设N={V，E}是连通网，TE是N上最小生成树中边的集合
//初始令U={u0},(u0∈V)，TE={}
//在所有u∈U，v∈V-U的边（u,V）∈E中，找一条代价最小的边（u0,v0）
//将(u0,v0)并入集合TE，同时v0并入U
//重复上述操作直至U=V为止，则T=(V,TE)为N的最小生成树
//--特点：
//--选择点
//--时间复杂度：O(n^2)
//--适合稠密图

void Prim(AMGraph G,VerTexType v0,int &sum)
{
	int lowcost[MVNum], vest[MVNum], v;//vest为最小生成树的数组
	int i, j, k, min;
	v = LocateVex(G,v0);//从v0顶点开始生成最小生成树
	for (int i = 0;i < G.vexnum;++i)//初始化lowcost数组和vest数组
	{
		lowcost[i] = G.Graph[v][i];
		vest[i] = 0;
	}
	vest[v] = 1;//将v0并入树中
	sum = 0;//sum清零用来累计树的权值
	for (int i = 0;i < G.vexnum - 1;++i)
	{
		min = INT_MAX;//最大值常量
		/*这个循环用于选出候选边中的最小值*/
		for (int j = 0;j < G.vexnum;++j)
		{
			if (vest[j] == 0 && lowcost[j] < min)//选出当前生成树到其余顶点最短边中的最短的一条
			{
				min = lowcost[j];
				k = j;
			}
		}
		vest[k] = 1;
		v = k;
		sum += min;//这里用sum记录最小生成树的权值
		/*下面这个循环以刚并入的顶点v为媒介更新候选边*/
		for (j = 0;j < G.vexnum;++j)
		{
			if (vest[j] == 0 && G.Graph[v][j] < lowcost[j])
				lowcost[j] = G.Graph[v][j];
		}
	}
}

//构造最小生成树方法二：Kruskal算法（一个集合包括所有顶点但是没有边，依次遍历找权值最小的边，前提条件是不能形成环）
//算法思想：
//设连通网N=(V,E),令最小生成树初始状态为只有n个顶点而无边的非连通图T=（V，{}），每个顶点自成一个连通分量
//在E中选取代价最小的边，若该边依附的顶点落在T中不同的连通分量上（即：不能形成环），则将此边加入到T中；否则，舍去此边，选取下一条代价最小的边
//依次类推，直至T中所有顶点都在同一连通分量上为止
//--特点：
//--选择边
//--时间复杂度：O(eloge)（e为边数）
//--适合稀疏图
typedef struct Road{//为什么此处还要定义这样结构体，有什么用吗？
	int a, b;//边的两个顶点
	int w;//权值
}Road;
Road road[MVNum];
int v[MVNum];//定义并查集数组
int getRoot(int a)//在并查集中查找根结点的函数：通过树中一个结点，可以找到其双亲结点，进而找到根结点（树的双亲存储结构）
{
	while (a != v[a])
		a = v[a];
	return a;
}
void Kruskal(AMGraph G, int& sum, Road road[])
{
	int i;
	int N, E, a, b;
	N = G.vexnum;//顶点数目
	E = G.arcnum;//边数目
	sum = 0;
	for (int i = 0;i < N;++i)
	{
		v[i] = i;
	}
	sort(road, E);//对road数组中的E条边按其权值从小到大排序（sort函数？）
	for (int i = 0;i < E;++i)
	{
		a = getRoot(road[i].a);//获取边i的顶点a
		b = getRoot(road[i].b);//获取边i的顶点b
		if (a != b)//如果两个顶点的根节点不相同，说明加入这条边不会形成环，可以将这条边加入最小生成树中。
		{
			v[a] = b;
			sum += road[i].w;//求生成树的权值，这句并不是本算法的固定写法，也可以改成其他的。例如，将生成树的各边输出，或者存放在数组里
		}
	}
}

void CreateAMGraph(AMGraph& G)
{
	cout << "请输入邻接矩阵的顶点个数和边个数：" << endl;
	cin >> G.vexnum >> G.arcnum;
	for (int i = 0;i < G.vexnum;i++)
	{
		G.vertices[i] = 0;//初始化顶点表
	}
	cout << "请输入邻接矩阵的顶点：" << endl;
	for (int i = 0;i < G.vexnum;i++)
	{
		cin >> G.vertices[i];//依次输入邻接矩阵的顶点
	}
	for(int i=0;i<G.vexnum;i++)//初始化邻接矩阵
		for (int j = 0;j < G.vexnum;j++)
		{
			G.Graph[i][j] = 0;
		}
	//2、构造邻接矩阵
	VerTexType v1, v2;
	int w;
	printf("请输入一条边所依附的顶点以及边的权值：\n");
	for (int k = 0;k < G.arcnum;++k)
	{
		cin >> v1 >> v2 >> w;//输入一条边所依附的顶点以及边的权值
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);//确定v1和v2在G中的位置
		G.Graph[i][j] = w;//边<v1,v2>的权值置为w
		G.Graph[j][i] = w;//置<v1,v2>的对称边<v2,v1>的权值为w
	}
}

int main(void)
{
	VerTexType v0;
	int sum;
	AMGraph G;
	CreateAMGraph(G);
	cout << "请输入需要开始的顶点：" << endl;
	cin >> v0;
	Prim(G, v0, sum);//Prim算法
	cout << sum;
}
//最小生成树可能不唯一
//注意：Prim算法和Kruskal算法都是针对无向图的（为什么只针对无向图）