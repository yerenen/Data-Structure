/*
* 邻接表表示法（链式）
* 顶点：按编号顺序将顶点数据存储在一维数组中；
* 关联同一顶点的边（以顶点为尾的弧）：用线性链表存储；
* 1、无向图
* --特点：
* 邻接表不唯一
* 若无向图中有n个顶点，e条边，则其邻接表需要n个头结点个2e个表结点。适宜存储稀疏图
* 无向图中顶点Vi的度为第i个单链表中的结点数
* --所需空间
* O(n+2e)
* 2、有向图
* --特点(找出度容易，找入度难)
* 顶点Vi的出度为第i个单链表中的结点个数
* 顶点Vi的入度为整个单链表中临界点域值为i-1的结点个数
* --所需空间
* O(n+e)\
*/
#include<iostream>
#include<stdio.h>
using namespace std;

#define MVNum 100//最大顶点数
typedef char VerTexType;
typedef int OtherInfo;

//边结点
struct ArcNode;//提前声明ArcNode结构体（※）

//顶点结构体
typedef struct VNode{
	VerTexType data;//顶点信息
	ArcNode* firstarc;//指向第一条依附该顶点的边的指针
}VNode,AdjList[MVNum];//AdjList表示邻接表类型

//边结点
typedef struct ArcNode{//边结点
	int adjvex;//该弧所指向的顶点的位置
	ArcNode* nextarc;//指向下一条边的指针
	OtherInfo info;//和边相关的信息
}ArcNode;

//邻接表类型
typedef struct ALGraph{
	AdjList vertics;//vertices--vertex的复数
	int vexnum, arcnum;//图的当前顶点数和弧数
}ALGraph;
int LocateVex(ALGraph G, VerTexType u)
{
	//图G中查找顶点u,存在则返回顶点表中的下标；否则返回-1
	int i = 0;
	while (i < G.vexnum)
	{
		if (u == G.vertics[i].data)
			return i;
		else
			i++;
	}
}
//队列的申明
typedef struct SqQueue{
	int data[MVNum];
	int front;
	int rear;
}SqQueue;//顺序循环队列
void InitQueue(SqQueue &Q)//初始化队列
{
	for (int i = 0;i < MVNum;i++)
	{
		Q.data[i] = 0;
	}
	Q.front = 0;
	Q.rear = 0;
}
bool Is_Empty(SqQueue Q)//判断队空
{
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}
void EnQueue(SqQueue &Q, int p)//入队
{
	if ((Q.rear + 1) % MVNum == Q.rear)//先判断队列是否为满
		return;
	else
	{
		Q.data[Q.rear] = p;
		Q.rear = (Q.rear + 1) % MVNum;
	}
}
int DeQueue(SqQueue& Q, int &p)
{
	if (!Is_Empty(Q))
	{
		int p = Q.data[Q.front];
		Q.data[Q.front] = 0;
		Q.front = (Q.front + 1) % MVNum;
		return p;
	}
	else
		return 0;
}
/*广度优先搜索（BFS-Breadth_First Search）*/
/*--（连通图的广度遍历）方法：从图中的某一结点出发，首先依次访问该结点的所有邻接顶点Vi1,Vi2,...,Vin。再按这些顶点被访问的先后次序依次访问与它们相邻接的所有未被访问的顶点。重复此过程，直至所有顶点均被访问为止。
* --（非连通图的广度遍历）方法：如果其中一个连通分量访问完了，那就从另一个连通分量取一个顶点的值一样作遍历*/

//BFS算法效率分析：
//-如果使用邻接矩阵，则BFS对于每一个被访问到的顶点，都要循环检测矩阵中的整整一行（n个元素），总的时间代价为O(n^2)
//-用邻接表表示图，虽然有2e个表结点，但只需扫描e个结点即可完成遍历，加上访问n个头结点的时间，时间复杂度为O(n+e)

//DFS和BFS算法效率分析
//--空间复杂度相同，都是O(n)借用了堆栈(DFS用的递归即用栈)或队列
//--时间复杂度只与存储结构（邻接矩阵或邻接表）有关，而与搜索路径无关

//使用一个队列和一个辅助数组visited
int visited[MVNum];
int FirstAdjVex(ALGraph G, int &u) {
	if (u < 0 || u >= G.vexnum)
		return -1; // 顶点v不存在

	if (G.vertics[u].firstarc != NULL)
		return G.vertics[u].firstarc->adjvex; // 返回第一个邻接顶点的索引
	else
		return -1; // 顶点v没有邻接顶点
}
int NextAdjVex(ALGraph G, int& u, int& w)
{
	//声明p指针指向G.vertics[u]的第一个边结点
	ArcNode* p = G.vertics[u].firstarc;
	while (p != NULL && p->adjvex != w)
	{//如果G.vertics[u]有边结点并且边结点指向的顶点并不是w
		p = p->nextarc;//p指向p的下一个边结点
	}
	if (p != NULL && p->nextarc != NULL) 
	{//如果p不为空，并且p的下一个边结点域也不为空，则返回所指顶点
		return p->nextarc->adjvex;
	}
	else {
		return -1; // 表示无邻接顶点
	}
}
void BFSTraverse(ALGraph G, int v)//按广度优先非递归遍历连通图G
{
	int w;
	int u;
	SqQueue Q;
	cout << "访问第" << v << "个结点" << endl;//访问第v个顶点
	visited[v] = true;
	InitQueue(Q);//辅助队列Q初始化，置空
	EnQueue(Q, v);//v进队
	while (!Is_Empty(Q))//队列非空
	{
		int u= DeQueue(Q, u);//对头元素出队并且置为u
		for (w = FirstAdjVex(G, u);w >= 0;w = NextAdjVex(G, u, w))//找到u的第一个邻接点和下一个邻接点
		{
			if (!visited[w])//如果w未被访问
			{
				cout << w;
				visited[w] = true;
				EnQueue(Q, w);//w进队
			}//if		
		}		
	}//while
}//BFS
void DFSTraverse(ALGraph G,int i)//?没懂
{
	//对图G作深度优先遍历
	for (int i = 0;i < G.vexnum;++i)
	{
		visited[i] = false;//访问标志数组初始化
	}
	for (int i = 0;i < G.vexnum;++i)
	{
		if (!visited[i])
			DFS(G, i);//对尚未访问的顶点调用DFS
	}
}
//DFS
void DFS(ALGraph G,int v)//从第v个顶点开始出发递归的深度优先遍历图G
{
	visited[v] = true;
	cout << G.vertics[v].data;//访问第v个顶点
	for (int w = FirstAdjVex(G, v);w >= 0;w = NextAdjVex(G, v, w))
		if (!visited[w])
			DFS(G, w);//对v的尚未访问的邻接顶点w递归调用DFS
}
/*
* 用邻接表表示法创建无向网
* 算法思想：
* 1、输入总顶点数和总边数
* 2、建立顶点表
* --依次输入点的信息存入顶点表中
* --使每个表头结点的指针域初始化为NULL
* 3、创建邻接表
* --依次输入每条边依附的两个顶点
* --确定两个顶点的序号i和j，建立边结点
* --将此边结点分别插入到Vi和Vj对应的两个边链表的头部
*/
void CreateUDG(ALGraph& G)//采用邻接表表示法，创建无向图G
{
	printf("请输入总顶点数，总边数：\n");
	cin >> G.vexnum >> G.arcnum;//输入总顶点数，总边数
	for (int i = 0;i < G.vexnum;++i)//输入各点，构造表头结点表
	{
		printf("请输入顶点值：\n");
		cin >> G.vertics[i].data;//输入顶点值
		G.vertics[i].firstarc = NULL;//初始化表头结点的指针域
	}
	for (int k = 0;k < G.arcnum;++k)
	{
		int i, j;
		VerTexType v1, v2;
		printf("请输入一条边依附的两个顶点：\n");
		cin >> v1 >> v2;//输入一条边依附的两个顶点
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		ArcNode *p1 = new ArcNode;//生成一个新的边结点*p1
		p1->adjvex = j;//邻接点序号为j
		p1->nextarc = G.vertics[i].firstarc;
		G.vertics[i].firstarc = p1;//将新结点*p1插入顶点Vi的边表头部（头插法）
		//有向网可以省略以下
		ArcNode *p2 = new ArcNode;//生成另一个对称的新的边结点*p2
		p2->adjvex = i;//邻接点序号为i
		p2->nextarc = G.vertics[j].firstarc;
		G.vertics[j].firstarc = p2;//将新结点*p2插入顶点Vj的边表头部
	}
}
int main(void)
{
	ALGraph G;//定义了邻接表表示的图G
	/*G.vexnum = 5;
	G.arcnum = 5;//图G包含5个顶点，5条边
	G.vertics[1].data = 'b';//图G中第2个顶点是b
	ArcNode *p = G.vertics[1].firstarc;//指针p指向顶点b的第一条边结点
	p->adjvex = 4;//p指针所指边结点是到下标为4的结点的边*/
	CreateUDG(G);
	//初始化数组
	for (int i = 0;i < MVNum;i++)
	{
		visited[i] = 0;
	}
	cout <<"------------------------------" << endl;
	cout << "BFS遍历的结果："<<endl;
	BFSTraverse(G, 1);
	cout << endl;
	cout << "------------------------------" << endl;
	cout << "DFS遍历的结果：" << endl;
	DFS(G, 0);
	return 0;
}
/*
* 邻接表特点：
* 1、方便找任一顶点的所有“邻接点”
* 2、节约稀疏图的空间：
* --对无向图：需要N个头指针+2E个结点（每个结点至少2个域）
* --对有向图：需要N个头指针+E个结点
* 3、方便计算任一顶点的“度”？
* --对无向图：是的
* --对有向图：只能计算“出度”；需要构造“逆邻接表”（存指向自己的边）来方便计算“入度”
*/
/*
* 邻接矩阵与邻接表表示法的关系：
* 1、联系：邻接表中每个链表对应于邻接矩阵中的一行，链表中结点个数等于一行中非零元素的个数
* 2、区别：
* ①对于任一确定的无向图，邻接矩阵是唯一的（行列号与顶点编号一致），但邻接表不唯一（链接次序与顶点编号无关）
* ②邻接矩阵的空间复杂度为O(n^2),而邻接表的空间复杂度为O(n+e)
* 3、用途：
* 邻接矩阵多用于稠密图；而邻接表多用于稀疏图
*/