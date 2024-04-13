#include <iostream>
#include <stdio.h>
using namespace std;

#define MVNum 100 //最大顶点数
typedef int VerTexType;
typedef int OtherInfo;

// 边结点
struct ArcNode; // 提前声明 ArcNode 结构体

// 顶点结构体
typedef struct {
    VerTexType data;   //顶点信息
    ArcNode* firstarc; //指向第一条依附该顶点的边的指针
} VNode, AdjList[MVNum]; //AdjList表示邻接表类型

// 边结点
typedef struct ArcNode {
    VerTexType adjvex; //该边所指向的顶点的位置?
    struct ArcNode* nextarc;  //指向下一条边的指针
    OtherInfo info;    //和边相关的信息
} ArcNode;

// 邻接表类型
typedef struct {
    AdjList vertics; //vertices--vertex的复数
    int vexnum, arcnum; //图的当前顶点数和弧数
} ALGraph;

// 图G中查找顶点u,存在则返回顶点表中的下标；否则返回-1
int LocateVex(ALGraph G, VerTexType u) {
    int i = 0;
    while (i < G.vexnum) {
        if (u == G.vertics[i].data)
            return i;
        else
            i++;
    }
    return -1; // 未找到顶点，返回 -1
}

/*
 * 用邻接表表示法创建无向网
 */
int CreateUDG(ALGraph& G) {
    printf("请输入总顶点数，总边数：\n");
    cin >> G.vexnum >> G.arcnum; //输入总顶点数，总边数
    cin.ignore(); // 清除输入缓冲区

    for (int i = 0; i < G.vexnum; ++i) { //输入各点，构造表头结点表
        printf("请输入顶点值：\n");
        cin >> G.vertics[i].data; //输入顶点值
        G.vertics[i].firstarc = NULL; //初始化表头结点的指针域
    }

    for (int k = 0; k < G.arcnum; ++k) {
        int i, j;
        VerTexType v1, v2;
        printf("请输入一条边依附的两个顶点：\n");
        cin >> v1 >> v2; //输入一条边依附的两个顶点
        cin.ignore(); // 清除输入缓冲区

        i = LocateVex(G, v1);
        j = LocateVex(G, v2);

        ArcNode* p1 = new ArcNode; //生成一个新的边结点*p1
        p1->adjvex = j; //邻接点序号为j
        p1->nextarc = G.vertics[i].firstarc;
        G.vertics[i].firstarc = p1; //将新结点*p1插入顶点Vi的边表头部

        //有向网可以省略以下
        ArcNode* p2 = new ArcNode; //生成另一个对称的新的边结点*p2
        p2->adjvex = i; //邻接点序号为i
        p2->nextarc = G.vertics[j].firstarc;
        G.vertics[j].firstarc = p2; //将新结点*p2插入顶点Vj的边表头部
    }

    return 0; // 函数执行成功，返回 0
}

int main(void) {
    ALGraph G; //定义了邻接表表示的图G
    CreateUDG(G);
    return 0;
}
