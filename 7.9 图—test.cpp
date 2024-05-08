//��7����д����ͼ���ڽӾ����ʾת��Ϊ�ڽӱ��ʾ���㷨
#include<iostream>
#include<stdio.h>
#define MVNum 100
using namespace std;
typedef int VerTexType;
typedef int weight;
typedef struct AMGraph{
	VerTexType vertics[MVNum];//�����
	weight arc[MVNum][MVNum];//�߱�
	int arcnum, vexnum;//�����Ͷ�����
}AMGraph;
typedef struct ArcNode {//�߱�
	VerTexType adjvex;//�߶�Ӧ�Ķ���
	ArcNode* nextarc;
}ArcNode;
typedef struct VNode{//�����
	VerTexType vex;//����
	ArcNode* firstarc;
}VNode;
typedef struct ALGraph{//ͼ
	VNode vertics[MVNum];
	int vexnum, arcnum;
}ALGraph;
AMGraph G;
//����д������
//�����һ������������
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
	cout << "�����붥�����ͱ�����" << endl;
	cin >> G.vexnum >> G.arcnum;
	//��ʼ�������
	for (int i = 0; i < MVNum; i++)
	{
		G.vertics[i] = 0;
	}
	//��ʼ���߱�
	for (int i = 0; i < MVNum; i++)
	{
		for (int j = 0; j < MVNum; j++)
		{
			G.arc[i][j] = 0;
		}
	}
	//�������ֵ
	cout << "�����붥���ֵ��" << endl;
	for (int i = 0; i < G.vexnum; i++)
	{
		cin >> G.vertics[i];
	}
	//�����ڽӾ���
	//��������д������
	//2�������ڽӾ���
	VerTexType v1, v2;
	int w;
	printf("������һ�����������Ķ����Լ��ߵ�Ȩֵ��\n");
	for (int k = 0; k < G.arcnum; ++k)
	{
		cin >> v1 >> v2 >> w;//����һ�����������Ķ����Լ��ߵ�Ȩֵ
		int n = LocateVex(G, v1);
		int f = LocateVex(G, v2);//ȷ��v1��v2��G�е�λ��
		G.arc[n][f] = w;//��<v1,v2>��Ȩֵ��Ϊw
		G.arc[f][n] = G.arc[n][f];//��<v1,v2>�ĶԳƱ�<v2,v1>��ȨֵΪw
	}
}
//��д
void transferAMG(AMGraph& G, ALGraph& M)
{
	//�ڽӱ�ĳ�ʼ��
	for (int i = 0; i < MVNum; i++)
	{
		M.vertics[i].vex = 0;
		M.vertics[i].firstarc = NULL;
	}
	M.arcnum = 0;
	M.vexnum = 0;
	//ת����ʼ
	M.arcnum = G.arcnum;
	M.vexnum = G.vexnum;
	//�ڽӱ�ĸ�ֵ������ʼת�������
	for (int i = 0; i < G.vexnum; i++)
	{
		M.vertics[i].vex = G.vertics[i];//�����ĸ�ֵ
	}
	//��ʼת���߱�
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
				//�жϱߵ�ʲôʱ��û�бߣ��ں�����Ž�
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