/*
* �ڽӱ��ʾ������ʽ��
* ���㣺�����˳�򽫶������ݴ洢��һά�����У�
* ����ͬһ����ıߣ��Զ���Ϊβ�Ļ���������������洢��
* 1������ͼ
* --�ص㣺
* �ڽӱ�Ψһ
* ������ͼ����n�����㣬e���ߣ������ڽӱ���Ҫn��ͷ����2e�����㡣���˴洢ϡ��ͼ
* ����ͼ�ж���Vi�Ķ�Ϊ��i���������еĽ����
* --����ռ�
* O(n+2e)
* 2������ͼ
* --�ص�(�ҳ������ף��������)
* ����Vi�ĳ���Ϊ��i���������еĽ�����
* ����Vi�����Ϊ�������������ٽ����ֵΪi-1�Ľ�����
* --����ռ�
* O(n+e)\
*/
#include<iostream>
#include<stdio.h>
using namespace std;

#define MVNum 100//��󶥵���
typedef char VerTexType;
typedef int OtherInfo;

//�߽��
struct ArcNode;//��ǰ����ArcNode�ṹ�壨����

//����ṹ��
typedef struct VNode{
	VerTexType data;//������Ϣ
	ArcNode* firstarc;//ָ���һ�������ö���ıߵ�ָ��
}VNode,AdjList[MVNum];//AdjList��ʾ�ڽӱ�����

//�߽��
typedef struct ArcNode{//�߽��
	int adjvex;//�û���ָ��Ķ����λ��
	ArcNode* nextarc;//ָ����һ���ߵ�ָ��
	OtherInfo info;//�ͱ���ص���Ϣ
}ArcNode;

//�ڽӱ�����
typedef struct ALGraph{
	AdjList vertics;//vertices--vertex�ĸ���
	int vexnum, arcnum;//ͼ�ĵ�ǰ�������ͻ���
}ALGraph;
int LocateVex(ALGraph G, VerTexType u)
{
	//ͼG�в��Ҷ���u,�����򷵻ض�����е��±ꣻ���򷵻�-1
	int i = 0;
	while (i < G.vexnum)
	{
		if (u == G.vertics[i].data)
			return i;
		else
			i++;
	}
}
//���е�����
typedef struct SqQueue{
	int data[MVNum];
	int front;
	int rear;
}SqQueue;//˳��ѭ������
void InitQueue(SqQueue &Q)//��ʼ������
{
	for (int i = 0;i < MVNum;i++)
	{
		Q.data[i] = 0;
	}
	Q.front = 0;
	Q.rear = 0;
}
bool Is_Empty(SqQueue Q)//�ж϶ӿ�
{
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}
void EnQueue(SqQueue &Q, int p)//���
{
	if ((Q.rear + 1) % MVNum == Q.rear)//���ж϶����Ƿ�Ϊ��
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
/*�������������BFS-Breadth_First Search��*/
/*--����ͨͼ�Ĺ�ȱ�������������ͼ�е�ĳһ���������������η��ʸý��������ڽӶ���Vi1,Vi2,...,Vin���ٰ���Щ���㱻���ʵ��Ⱥ�������η������������ڽӵ�����δ�����ʵĶ��㡣�ظ��˹��̣�ֱ�����ж����������Ϊֹ��
* --������ͨͼ�Ĺ�ȱ������������������һ����ͨ�����������ˣ��Ǿʹ���һ����ͨ����ȡһ�������ֵһ��������*/

//BFS�㷨Ч�ʷ�����
//-���ʹ���ڽӾ�����BFS����ÿһ�������ʵ��Ķ��㣬��Ҫѭ���������е�����һ�У�n��Ԫ�أ����ܵ�ʱ�����ΪO(n^2)
//-���ڽӱ��ʾͼ����Ȼ��2e�����㣬��ֻ��ɨ��e����㼴����ɱ��������Ϸ���n��ͷ����ʱ�䣬ʱ�临�Ӷ�ΪO(n+e)

//DFS��BFS�㷨Ч�ʷ���
//--�ռ临�Ӷ���ͬ������O(n)�����˶�ջ(DFS�õĵݹ鼴��ջ)�����
//--ʱ�临�Ӷ�ֻ��洢�ṹ���ڽӾ�����ڽӱ��йأ���������·���޹�

//ʹ��һ�����к�һ����������visited
int visited[MVNum];
int FirstAdjVex(ALGraph G, int &u) {
	if (u < 0 || u >= G.vexnum)
		return -1; // ����v������

	if (G.vertics[u].firstarc != NULL)
		return G.vertics[u].firstarc->adjvex; // ���ص�һ���ڽӶ��������
	else
		return -1; // ����vû���ڽӶ���
}
int NextAdjVex(ALGraph G, int& u, int& w)
{
	//����pָ��ָ��G.vertics[u]�ĵ�һ���߽��
	ArcNode* p = G.vertics[u].firstarc;
	while (p != NULL && p->adjvex != w)
	{//���G.vertics[u]�б߽�㲢�ұ߽��ָ��Ķ��㲢����w
		p = p->nextarc;//pָ��p����һ���߽��
	}
	if (p != NULL && p->nextarc != NULL) 
	{//���p��Ϊ�գ�����p����һ���߽����Ҳ��Ϊ�գ��򷵻���ָ����
		return p->nextarc->adjvex;
	}
	else {
		return -1; // ��ʾ���ڽӶ���
	}
}
void BFSTraverse(ALGraph G, int v)//��������ȷǵݹ������ͨͼG
{
	int w;
	int u;
	SqQueue Q;
	cout << "���ʵ�" << v << "�����" << endl;//���ʵ�v������
	visited[v] = true;
	InitQueue(Q);//��������Q��ʼ�����ÿ�
	EnQueue(Q, v);//v����
	while (!Is_Empty(Q))//���зǿ�
	{
		int u= DeQueue(Q, u);//��ͷԪ�س��Ӳ�����Ϊu
		for (w = FirstAdjVex(G, u);w >= 0;w = NextAdjVex(G, u, w))//�ҵ�u�ĵ�һ���ڽӵ����һ���ڽӵ�
		{
			if (!visited[w])//���wδ������
			{
				cout << w;
				visited[w] = true;
				EnQueue(Q, w);//w����
			}//if		
		}		
	}//while
}//BFS
void DFSTraverse(ALGraph G,int i)//?û��
{
	//��ͼG��������ȱ���
	for (int i = 0;i < G.vexnum;++i)
	{
		visited[i] = false;//���ʱ�־�����ʼ��
	}
	for (int i = 0;i < G.vexnum;++i)
	{
		if (!visited[i])
			DFS(G, i);//����δ���ʵĶ������DFS
	}
}
//DFS
void DFS(ALGraph G,int v)//�ӵ�v�����㿪ʼ�����ݹ��������ȱ���ͼG
{
	visited[v] = true;
	cout << G.vertics[v].data;//���ʵ�v������
	for (int w = FirstAdjVex(G, v);w >= 0;w = NextAdjVex(G, v, w))
		if (!visited[w])
			DFS(G, w);//��v����δ���ʵ��ڽӶ���w�ݹ����DFS
}
/*
* ���ڽӱ��ʾ������������
* �㷨˼�룺
* 1�������ܶ��������ܱ���
* 2�����������
* --������������Ϣ���붥�����
* --ʹÿ����ͷ����ָ�����ʼ��ΪNULL
* 3�������ڽӱ�
* --��������ÿ������������������
* --ȷ��������������i��j�������߽��
* --���˱߽��ֱ���뵽Vi��Vj��Ӧ�������������ͷ��
*/
void CreateUDG(ALGraph& G)//�����ڽӱ��ʾ������������ͼG
{
	printf("�������ܶ��������ܱ�����\n");
	cin >> G.vexnum >> G.arcnum;//�����ܶ��������ܱ���
	for (int i = 0;i < G.vexnum;++i)//������㣬�����ͷ����
	{
		printf("�����붥��ֵ��\n");
		cin >> G.vertics[i].data;//���붥��ֵ
		G.vertics[i].firstarc = NULL;//��ʼ����ͷ����ָ����
	}
	for (int k = 0;k < G.arcnum;++k)
	{
		int i, j;
		VerTexType v1, v2;
		printf("������һ�����������������㣺\n");
		cin >> v1 >> v2;//����һ������������������
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		ArcNode *p1 = new ArcNode;//����һ���µı߽��*p1
		p1->adjvex = j;//�ڽӵ����Ϊj
		p1->nextarc = G.vertics[i].firstarc;
		G.vertics[i].firstarc = p1;//���½��*p1���붥��Vi�ı߱�ͷ����ͷ�巨��
		//����������ʡ������
		ArcNode *p2 = new ArcNode;//������һ���ԳƵ��µı߽��*p2
		p2->adjvex = i;//�ڽӵ����Ϊi
		p2->nextarc = G.vertics[j].firstarc;
		G.vertics[j].firstarc = p2;//���½��*p2���붥��Vj�ı߱�ͷ��
	}
}
int main(void)
{
	ALGraph G;//�������ڽӱ��ʾ��ͼG
	/*G.vexnum = 5;
	G.arcnum = 5;//ͼG����5�����㣬5����
	G.vertics[1].data = 'b';//ͼG�е�2��������b
	ArcNode *p = G.vertics[1].firstarc;//ָ��pָ�򶥵�b�ĵ�һ���߽��
	p->adjvex = 4;//pָ����ָ�߽���ǵ��±�Ϊ4�Ľ��ı�*/
	CreateUDG(G);
	//��ʼ������
	for (int i = 0;i < MVNum;i++)
	{
		visited[i] = 0;
	}
	cout <<"------------------------------" << endl;
	cout << "BFS�����Ľ����"<<endl;
	BFSTraverse(G, 1);
	cout << endl;
	cout << "------------------------------" << endl;
	cout << "DFS�����Ľ����" << endl;
	DFS(G, 0);
	return 0;
}
/*
* �ڽӱ��ص㣺
* 1����������һ��������С��ڽӵ㡱
* 2����Լϡ��ͼ�Ŀռ䣺
* --������ͼ����ҪN��ͷָ��+2E����㣨ÿ���������2����
* --������ͼ����ҪN��ͷָ��+E�����
* 3�����������һ����ġ��ȡ���
* --������ͼ���ǵ�
* --������ͼ��ֻ�ܼ��㡰���ȡ�����Ҫ���조���ڽӱ�����ָ���Լ��ıߣ���������㡰��ȡ�
*/
/*
* �ڽӾ������ڽӱ��ʾ���Ĺ�ϵ��
* 1����ϵ���ڽӱ���ÿ�������Ӧ���ڽӾ����е�һ�У������н���������һ���з���Ԫ�صĸ���
* 2������
* �ٶ�����һȷ��������ͼ���ڽӾ�����Ψһ�ģ����к��붥����һ�£������ڽӱ�Ψһ�����Ӵ����붥�����޹أ�
* ���ڽӾ���Ŀռ临�Ӷ�ΪO(n^2),���ڽӱ�Ŀռ临�Ӷ�ΪO(n+e)
* 3����;��
* �ڽӾ�������ڳ���ͼ�����ڽӱ������ϡ��ͼ
*/