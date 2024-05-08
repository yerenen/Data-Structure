/*
* 7.5 图的应用
* 7.5.2 最短路径
* ①典型用途：
* --交通网络的问题：
* 从甲地到乙地之间是否有公路连通？在有多条通途的情况下，哪一条路最短？
* --交通网络用有向网表示：
* 顶点：地点
* 弧：表示两个地点有路连通
* 弧上的权值：表示两地之间的距离、交通费或途中所花费时间等
* --如何能使一个地点到另一个地点的运输时间最短或运费最省？这就是一个求两个地点之间的最短路径问题。
* ②问题抽象：
* 在有向网中A点（源点）到达B点（终点）的多条路径中，寻找一条各边权值之和最小的路径，即最短路径
* ③最短路径与最小生成树的区别：
* 最短路径与最小生成树不同，路径上不一定包含n个顶点，也不一定包含n-1条边
* ④问题类型
* --第一类问题：单源最短路径——Dijkstra(迪杰斯特拉)算法
* --第二类问题：所有顶点间的最短路径——Floyd（弗洛伊德）算法
*/
#include<iostream>
#include<stdio.h>
#define MVNum 100
#define INFINITY 99999
using namespace std;
typedef int VertexType;
typedef struct AMGraph{
	VertexType vertices[MVNum];//顶点表
	int AMGraph[MVNum][MVNum];//邻接矩阵
	int arcnum, vexnum;//边数和顶点数
}AMGraph;
/*寻找图中顶点u的位置：*/
int LocateVex(AMGraph G,VertexType u)
{
	int i = 0;
	while (i < G.vexnum)
	{
		if (G.vertices[i] == u)
			return i;
		else
			i++;
	}
}

#if 0
第一个版本思想：
求单源最短路径算法——Dijkstra算法
1、每次从未标记的节点中选择距离出发点最近的节点，标记、收录到最优路径集合中
2、计算刚加入节点A的邻近节点B的距离（不包含标记的节点）
若（节点A的距离 + 节点A到节点B的边长） < 节点B的距离，就更新节点B的距离和前面点

	第二个版本思想：
	求单源最短路径算法——Dijkstra算法
	1、初始化：先找出从源点Vo到各终点Vk的直达路径(Vo, Vk), 即通过一条弧到达的路径
	2、选择：从这些路径中找出一条长度最短的路径(Vo, u)
	--此处路径最短的顶点用u表示
	--其余未能通过直达到达的顶点路径记为∞
	3、更新：然后对其余各条路径进行适当调整
	--若在图中存在弧(u, Vk), 且(Vo, u) + (u, Vk) < (Vo, Vk), 则以路径(Vo, u, Vk)代替(Vo, Vk)
	--将找到最短路径的顶点放在S集合，其他顶点在T集合：T：V - S
	4、在调整后的各条路径中，再找长度最短的路径，依此类推

	Dijkstra算法：按路径长度递增次序产生最短路径
	1、把V分成两组：
	（1）S：已求出最短路径的顶点的集合
	（2）T = V - S：尚未确定最短路径的顶点集合
	2、将T中顶点按最短路径递增的次序加到S中
	保证：
	（1）从源点Vo到S中各顶点的最短路径长度都不大于从Vo到T中任何顶点的最短路径长度（即需保证Vo通过S各顶点到达T的长度是最小的）
	（2）每个顶点对应一个距离值：
	--S中顶点：从Vo到此顶点的最短路径长度
	--T中顶点：从Vo到此顶点的只包括S中顶点作中间顶点的最短路径长度
#endif
/*Dijkstra算法*/
/*时间复杂度：O(n^2)*/
VertexType dist[MVNum];//辅助数组dist
VertexType path[MVNum];//辅助数组path
int set[MVNum];//辅助数组set
void Dijkstra(AMGraph G, VertexType v, VertexType dist[], VertexType path[])//从图的v顶点开始遍历查找最小路径
{
	int min, i, j, u;
	int m = LocateVex(G, v);
	//开始对各数组进行初始化
	for (int i = 0;i < G.vexnum;i++)
	{
		dist[i] = G.AMGraph[m][i];
		set[i] = 0;
		if (G.AMGraph[m][i] < INFINITY)
			path[i] = v;
		else
			path[i] = -1;
	}
	set[m] = 1;
	path[m] = -1;
	/*初始化操作结束*/
	/*关键操作开始*/
	for (i = 0;i < G.vexnum - 1;i++)
	{
		min = INFINITY;
		/*这个循环每次从剩余顶点中选出一个顶点，
		通往这个顶点的路径在所有剩余顶点的路径中是长度最短的*/
		for (j = 0;j < G.vexnum;++j)
		{
			if (set[j] == 0 && dist[j] < min)//如果j在S顶点集里并且dist[j]<min
			{
				u = j;
				min = dist[j];
			}
		}
		set[u] = 1;//将选出的顶点并入最短路径
		/*这个循环以刚并入的顶点作为中间点，对所有通往剩余顶点的路径进行检测*/
		for (j = 0;j < G.vexnum;++j)
		{
			//这个if语句是为了判断顶点u的加入是否会出现通往顶点j的更短路径，如果出现，则改变原来路径及其长度，否则什么都不做
			if (set[j] == 0 && dist[u] + G.AMGraph[u][j] < dist[j])
			{
				dist[j] = dist[u] + G.AMGraph[u][j];
				path[j] = u;
			}
		}
		/*关键操作结束*/
	}
}

#if 0
求所有顶点间的最短路径
方法一：每次以一个顶点作为源点，重复执行Dijkstra算法n次
方法二：Floyd算法

算法思想：
逐个顶点试探
从Vi到Vj的所有可能存在的路径中
选出一条长度最短的路径
#endif
/*Floyd算法*/
/*时间复杂度：O(n^3)*/
int Path[MVNum][MVNum];//辅助数组
int A[MVNum][MVNum];
void Floyd(AMGraph* G, int Path[][MVNum], int A[][MVNum])
{
	//图g的边矩阵中，用INF来表示两点之间不存在边
	int i, j, k;
	//此处双循环对数组A[][]和Path[][]初始化
	for (int i = 0;i < G->vexnum;++i)
	{
		for (int j = 0;j < G->vexnum;++j)
		{
			A[i][j] = G->AMGraph[i][j];
			Path[i][j] = -1;
		}
		//下面三个循环为算法的主要操作，完成了以k为中间点对所有的顶点对(i,j)进行扫描和修改
		for(k=0;k<G->vexnum;++k)
			for(i=0;i<G->vexnum;++i)
				for(j=0;j<G->vexnum;++j)
					if (A[i][j] > A[i][k] + A[k][j])
					{
						A[i][j] = A[i][k] + A[k][j];
						Path[i][j] = k;
					}
	}
}

/*构造有向网*/
void Create_AMGraph(AMGraph& G)
{
	printf("请输入顶点数和边数：");
	cin >> G.vexnum >> G.arcnum;
	//初始化顶点表
	for (int i = 0;i < G.vexnum;i++)
	{
		G.vertices[i] = 0;
	}
	printf("请输入各顶点值：");
	for (int i = 0;i < G.vexnum;i++)
	{
		cin >> G.vertices[i];
	}
	//初始化邻接矩阵
	for (int i = 0;i < G.vexnum;i++)
	{
		for (int j = 0;j < G.vexnum;j++)
		{
			G.AMGraph[i][j] = INFINITY;
		}
	}
	VertexType u, w;
	int r;
	printf("请输入各有向边及边权值：");
	for (int i = 0;i < G.arcnum;i++)
	{
		cin >> u >> w >> r;
		int k = LocateVex(G, u);
		int l = LocateVex(G, w);
		G.AMGraph[k][l] = r;
	}
}
int main(void)
{
	AMGraph G;
	//创建有向网
	Create_AMGraph(G);
	VertexType T = 0;
	Dijkstra(G, T, dist, path);
	for (int i = 0;i < G.vexnum;i++)
	{
		cout << dist[i] << endl;
	}
	Floyd(G, Path, A);
}