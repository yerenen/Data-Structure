//题7：试写出把图的邻接矩阵表示转换为邻接表表示的算法
#include<iostream>
#include<stdio.h>
#define MVNum 100
using namespace std;
typedef int VerTexType;
typedef int weight;
typedef struct AMGraph{
	VerTexType vertics[MVNum];//顶点表
	weight arc[MVNum][MVNum];//边表
	int arcnum, vexnum;//边数和顶点数
}AMGraph;
typedef struct ArcNode {//边表
	VerTexType adjvex;//边对应的顶点
	ArcNode* nextarc;
}ArcNode;
typedef struct VNode{//顶点表
	VerTexType vex;//顶点
	ArcNode* firstarc;
}VNode;
typedef struct ALGraph{//图
	VNode vertics[MVNum];
	int vexnum, arcnum;
}ALGraph;
AMGraph G;
//容易写出问题
//必须加一个边数的限制
int LocateVex(AMGraph &G,VerTexType &a)
{
	int i = 0;
	while (i < G.arcnum)
	{
		if (G.vertics[i] == a)
			return i;
		else
			i++;
	}
}
void Create_AMGraph(AMGraph& G)
{
	cout << "请输入顶点数和边数：" << endl;
	cin >> G.vexnum >> G.arcnum;
	//初始化顶点表
	for (int i = 0; i < MVNum; i++)
	{
		G.vertics[i] = 0;
	}
	//初始化边表
	for (int i = 0; i < MVNum; i++)
	{
		for (int j = 0; j < MVNum; j++)
		{
			G.arc[i][j] = 0;
		}
	}
	//给顶点表赋值
	cout << "请输入顶点表值：" << endl;
	for (int i = 0; i < G.vexnum; i++)
	{
		cin >> G.vertics[i];
	}
	//构造邻接矩阵
	//这里容易写出问题
	//2、构造邻接矩阵
	VerTexType v1, v2;
	int w;
	printf("请输入一条边所依附的顶点以及边的权值：\n");
	for (int k = 0; k < G.arcnum; ++k)
	{
		cin >> v1 >> v2 >> w;//输入一条边所依附的顶点以及边的权值
		int n = LocateVex(G, v1);
		int f = LocateVex(G, v2);//确定v1和v2在G中的位置
		G.arc[n][f] = w;//边<v1,v2>的权值置为w
		G.arc[f][n] = G.arc[n][f];//置<v1,v2>的对称边<v2,v1>的权值为w
	}
}
//自写
void transferAMG(AMGraph& G, ALGraph& M)
{
	//邻接表的初始化
	for (int i = 0; i < MVNum; i++)
	{
		M.vertics[i].vex = 0;
		M.vertics[i].firstarc = NULL;
	}
	M.arcnum = 0;
	M.vexnum = 0;
	//转化开始
	M.arcnum = G.arcnum;
	M.vexnum = G.vexnum;
	//邻接表的赋值——开始转化顶点表
	for (int i = 0; i < G.vexnum; i++)
	{
		M.vertics[i].vex = G.vertics[i];//顶点表的赋值
	}
	//开始转化边表
	for (int j = 0; j < G.vexnum; j++)
	{
		for (int k = 0; k < G.vexnum; k++)
		{
			if (G.arc[j][k] != 0 && M.vertics[j].firstarc==NULL)
			{
				ArcNode* p = new ArcNode;
				p->adjvex = k;
				M.vertics[j].firstarc = p;
				p->nextarc = NULL;
			}
			else if (M.vertics[j].firstarc != NULL)
			{
				//判断边到什么时候没有边，在后面接着接
				ArcNode* q = M.vertics[j].firstarc;
				while (q != NULL)
					q = q->nextarc;
				ArcNode* p = new ArcNode;
				p->adjvex = k;
				q = p;
				q->nextarc = NULL;
			}
		}
	}
}
int main(void)
{
	AMGraph G;
	ALGraph M;
	Create_AMGraph(G);
	//cout << G.arc[0][1];
	transferAMG(G, M);
	cout << M.vertics[1].firstarc->nextarc->adjvex;
}