/*
* 7.5 ͼ��Ӧ��
* 7.5.2 ���·��
* �ٵ�����;��
* --��ͨ��������⣺
* �Ӽ׵ص��ҵ�֮���Ƿ��й�·��ͨ�����ж���ͨ;������£���һ��·��̣�
* --��ͨ��������������ʾ��
* ���㣺�ص�
* ������ʾ�����ص���·��ͨ
* ���ϵ�Ȩֵ����ʾ����֮��ľ��롢��ͨ�ѻ�;��������ʱ���
* --�����ʹһ���ص㵽��һ���ص������ʱ����̻��˷���ʡ�������һ���������ص�֮������·�����⡣
* ���������
* ����������A�㣨Դ�㣩����B�㣨�յ㣩�Ķ���·���У�Ѱ��һ������Ȩֵ֮����С��·���������·��
* �����·������С������������
* ���·������С��������ͬ��·���ϲ�һ������n�����㣬Ҳ��һ������n-1����
* ����������
* --��һ�����⣺��Դ���·������Dijkstra(�Ͻ�˹����)�㷨
* --�ڶ������⣺���ж��������·������Floyd���������£��㷨
*/
#include<iostream>
#include<stdio.h>
#define MVNum 100
#define INFINITY 99999
using namespace std;
typedef int VertexType;
typedef struct AMGraph{
	VertexType vertices[MVNum];//�����
	int AMGraph[MVNum][MVNum];//�ڽӾ���
	int arcnum, vexnum;//�����Ͷ�����
}AMGraph;
/*Ѱ��ͼ�ж���u��λ�ã�*/
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
��һ���汾˼�룺
��Դ���·���㷨����Dijkstra�㷨
1��ÿ�δ�δ��ǵĽڵ���ѡ��������������Ľڵ㣬��ǡ���¼������·��������
2������ռ���ڵ�A���ڽ��ڵ�B�ľ��루��������ǵĽڵ㣩
�����ڵ�A�ľ��� + �ڵ�A���ڵ�B�ı߳��� < �ڵ�B�ľ��룬�͸��½ڵ�B�ľ����ǰ���

	�ڶ����汾˼�룺
	��Դ���·���㷨����Dijkstra�㷨
	1����ʼ�������ҳ���Դ��Vo�����յ�Vk��ֱ��·��(Vo, Vk), ��ͨ��һ���������·��
	2��ѡ�񣺴���Щ·�����ҳ�һ��������̵�·��(Vo, u)
	--�˴�·����̵Ķ�����u��ʾ
	--����δ��ͨ��ֱ�ﵽ��Ķ���·����Ϊ��
	3�����£�Ȼ����������·�������ʵ�����
	--����ͼ�д��ڻ�(u, Vk), ��(Vo, u) + (u, Vk) < (Vo, Vk), ����·��(Vo, u, Vk)����(Vo, Vk)
	--���ҵ����·���Ķ������S���ϣ�����������T���ϣ�T��V - S
	4���ڵ�����ĸ���·���У����ҳ�����̵�·������������

	Dijkstra�㷨����·�����ȵ�������������·��
	1����V�ֳ����飺
	��1��S����������·���Ķ���ļ���
	��2��T = V - S����δȷ�����·���Ķ��㼯��
	2����T�ж��㰴���·�������Ĵ���ӵ�S��
	��֤��
	��1����Դ��Vo��S�и���������·�����ȶ������ڴ�Vo��T���κζ�������·�����ȣ����豣֤Voͨ��S�����㵽��T�ĳ�������С�ģ�
	��2��ÿ�������Ӧһ������ֵ��
	--S�ж��㣺��Vo���˶�������·������
	--T�ж��㣺��Vo���˶����ֻ����S�ж������м䶥������·������
#endif
/*Dijkstra�㷨*/
/*ʱ�临�Ӷȣ�O(n^2)*/
VertexType dist[MVNum];//��������dist
VertexType path[MVNum];//��������path
int set[MVNum];//��������set
void Dijkstra(AMGraph G, VertexType v, VertexType dist[], VertexType path[])//��ͼ��v���㿪ʼ����������С·��
{
	int min, i, j, u;
	int m = LocateVex(G, v);
	//��ʼ�Ը�������г�ʼ��
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
	/*��ʼ����������*/
	/*�ؼ�������ʼ*/
	for (i = 0;i < G.vexnum - 1;i++)
	{
		min = INFINITY;
		/*���ѭ��ÿ�δ�ʣ�ඥ����ѡ��һ�����㣬
		ͨ����������·��������ʣ�ඥ���·�����ǳ�����̵�*/
		for (j = 0;j < G.vexnum;++j)
		{
			if (set[j] == 0 && dist[j] < min)//���j��S���㼯�ﲢ��dist[j]<min
			{
				u = j;
				min = dist[j];
			}
		}
		set[u] = 1;//��ѡ���Ķ��㲢�����·��
		/*���ѭ���Ըղ���Ķ�����Ϊ�м�㣬������ͨ��ʣ�ඥ���·�����м��*/
		for (j = 0;j < G.vexnum;++j)
		{
			//���if�����Ϊ���ж϶���u�ļ����Ƿ�����ͨ������j�ĸ���·����������֣���ı�ԭ��·�����䳤�ȣ�����ʲô������
			if (set[j] == 0 && dist[u] + G.AMGraph[u][j] < dist[j])
			{
				dist[j] = dist[u] + G.AMGraph[u][j];
				path[j] = u;
			}
		}
		/*�ؼ���������*/
	}
}

#if 0
�����ж��������·��
����һ��ÿ����һ��������ΪԴ�㣬�ظ�ִ��Dijkstra�㷨n��
��������Floyd�㷨

�㷨˼�룺
���������̽
��Vi��Vj�����п��ܴ��ڵ�·����
ѡ��һ��������̵�·��
#endif
/*Floyd�㷨*/
/*ʱ�临�Ӷȣ�O(n^3)*/
int Path[MVNum][MVNum];//��������
int A[MVNum][MVNum];
void Floyd(AMGraph* G, int Path[][MVNum], int A[][MVNum])
{
	//ͼg�ı߾����У���INF����ʾ����֮�䲻���ڱ�
	int i, j, k;
	//�˴�˫ѭ��������A[][]��Path[][]��ʼ��
	for (int i = 0;i < G->vexnum;++i)
	{
		for (int j = 0;j < G->vexnum;++j)
		{
			A[i][j] = G->AMGraph[i][j];
			Path[i][j] = -1;
		}
		//��������ѭ��Ϊ�㷨����Ҫ�������������kΪ�м������еĶ����(i,j)����ɨ����޸�
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

/*����������*/
void Create_AMGraph(AMGraph& G)
{
	printf("�����붥�����ͱ�����");
	cin >> G.vexnum >> G.arcnum;
	//��ʼ�������
	for (int i = 0;i < G.vexnum;i++)
	{
		G.vertices[i] = 0;
	}
	printf("�����������ֵ��");
	for (int i = 0;i < G.vexnum;i++)
	{
		cin >> G.vertices[i];
	}
	//��ʼ���ڽӾ���
	for (int i = 0;i < G.vexnum;i++)
	{
		for (int j = 0;j < G.vexnum;j++)
		{
			G.AMGraph[i][j] = INFINITY;
		}
	}
	VertexType u, w;
	int r;
	printf("�����������߼���Ȩֵ��");
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
	//����������
	Create_AMGraph(G);
	VertexType T = 0;
	Dijkstra(G, T, dist, path);
	for (int i = 0;i < G.vexnum;i++)
	{
		cout << dist[i] << endl;
	}
	Floyd(G, Path, A);
}