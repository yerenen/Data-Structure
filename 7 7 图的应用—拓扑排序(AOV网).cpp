/*
* 7.5 图的应用
* 7.5.3 拓扑排序
* ①有向无环图及其应用
* 有向无环图：无环的有向图，简称DAG图（Directed Acycline Graph）
* --有向无环图常用来描述一个工程或系统的进行过程。（通常把计划、施工、生产、程序流程当成是一个工程）
* --一个工程可以分为若干个子工程，只要完成了这些子工程（活动），就可以导致整个工程的完成
* ②AOV网（Activity on Vertex network）——解决拓扑排序问题：
* 用一个有向图表示一个工程的各子工程及其相互制约的关系，其中以顶点表示活动，弧表示活动之间的优先制约关系，称这种有向图为顶点表示活动的网，简称AOE网
* ③AOE网（Activity On Edge）——解决关键路径问题：
* 用一个有向图表示一个工程的各子工程及其相互制约的关系，以弧表示活动，以顶点表示活动的开始或结束事件，称这种有向图为边表示活动的网，简称为AOE网
* ④AOV网的特点：
* --若从i到j有一条有向路径，则i是j的前驱；j是i的后继
* --若<i,j>是网中有向边，则i是j的直接前驱；j是i的直接后继
* --AOV网中不允许有回路，因为如果有回路存在，则表明某项活动以自己为先决条件，显然这是荒谬的
* ⑤问题：如何判别AOV网中是否存在回路？
* 用拓扑排序解决
* --在AOV网没有回路的前提下，我们将全部活动排列成一个线性序列，使得若AOV网中有弧<i,j>存在，则在这个序列中，i一定排在j的前面，具有这种性质的线性序列称为拓扑有序序列，相应的拓扑有序排序的算法称为拓扑排序
* --一个AOV网的拓扑序列不是唯一的
* ⑥拓扑排序的方法：
* --在有向图中选一个没有前驱的顶点且输出之
* --从图中删除该顶点和所有以它为尾的弧
* --重复上述两步，直至全部顶点均已输出；或者当图中不存在无前驱的顶点为止
* ⑦拓扑排序的一个重要应用：
* 检测AOV网中是否存在环的方法：
* 对有向图构造其顶点的拓扑有序序列，若网中所有顶点都在它的拓扑有序序列中，则该AOV网必定不存在环
*/
//用邻接表表示拓扑排序
#include<iostream>
#include<stdio.h>
#define MVNum 100
using namespace std;
typedef char VertexType;
typedef struct ArcNode{//边结构
	int adjvex;
	ArcNode* nextarc;
}ArcNode;
typedef struct VNode {//顶点结构
	VertexType data;
	ArcNode* firstarc;
	int count;//计数有多少个入度
}VNode;
typedef struct DAGraph{//图
	VNode vertices[MVNum];//顶点数组
	int arcnum, vexnum;
}DAGraph;
DAGraph G;
//在顶点表中查找顶点的位置
int LocateVex(DAGraph G, VertexType u)
{
	int i = 0;
	while (G.vertices[i].data != u)
	{
		i++;
	}
	return i;
}
//拓扑排序算法
//时间复杂度:O（n+e）
//1、设置辅助栈：为了记录当前图中入度为0的顶点
//2、设置?>计数器n：用来记录已经输出的顶点（为啥不用数组记录）
int TopSort(DAGraph *G)
{
	int i, j, n = 0;
	//定义并初始化栈
	int Stack[MVNum];
	int top = -1;
	ArcNode* p;
	//这个循环将图中入度为0的顶点入栈（一个for循环）
	for (i = 0;i < G->vexnum; ++i)//图中顶点从0开始编号
	{
		if (G->vertices[i].count == 0)
			Stack[++top] = i;
	}
	//关键操作开始（两个while循环）
	while (top != -1)//如果栈中元素不为空
	{
		i = Stack[top--];//顶点出栈
		++n;
		cout << i << "";//输出当前顶点
		p = G->vertices[i].firstarc;
		//这个循环实现了将所有由此顶点引出的边所指向的顶点的入度都减少1，并将这个过程中入度变为0的顶点入栈（不用删除节点，只是从count角度来模拟这个过程）
		while (p != NULL)
		{
			j = p->adjvex;
			--(G->vertices[j].count);//减少入度（❤更新度）
			if (G->vertices[j].count == 0)
				Stack[++top] = j;//将此时入度为0的顶点入栈（❤更新栈）
			p = p->nextarc;
		}	
	}
	//关键操作结束
	if (n == G->vexnum)//意为所有顶点都遍历过了
		return 1;
	else
		return 0;
}
//构造有向无环图（应用——AOV网）
void Create_DAG(DAGraph& G)
{
	printf("请输入边数和顶点数：");
	cin >> G.vexnum >> G.arcnum;
	//初始化顶点数组
	for (int i = 0;i < MVNum;i++)
	{
		G.vertices[i].data = 0;
		G.vertices[i].count = 0;
		G.vertices[i].firstarc = NULL;
	}
	printf("请输入顶点：");
	for (int i = 0;i < G.vexnum;i++)
	{
		cin >> G.vertices[i].data;
	}
	//初始化邻接表
	for (int k = 0;k < G.arcnum;++k)
	{
		int i, j;
		VertexType v1, v2;
		printf("请输入一条边依附的两个顶点：\n");
		cin >> v1 >> v2;//输入一条边依附的两个顶点
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		ArcNode* p1 = new ArcNode;//生成一个新的边结点*p1
		p1->adjvex = j;//邻接点序号为j
		p1->nextarc = G.vertices[i].firstarc;//这句有什么用吗？
		G.vertices[i].firstarc = p1;//将新结点*p1插入顶点Vi的边表头部（头插法）
		G.vertices[j].count++;//count是为了计算顶点的入度，方便拓扑排序
	}
}
int main(void)
{
	DAGraph G;
	DAGraph* p = &G;
	Create_DAG(G);
	cout << "拓扑排序后的结果为："<< endl;
	TopSort(p);
}


