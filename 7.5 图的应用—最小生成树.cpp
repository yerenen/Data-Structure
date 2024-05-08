/*
* 7.5 ͼ��Ӧ��
* 7.5.1 ��С������
* --����������ͨ�ұ������ٴﵽû�л�·
* --��С������������һ���������磬�ڸ����������������У�ʹ�ø���Ȩֵ֮����С���ǿ���������Ϊ��������С��������Ҳ����С������������
* --��С�������ĵ���Ӧ�ã�
* ����n�����н���ͨ��������n������Ӧ��n-1����·��
* ����Ϊÿ����·�����ж�Ӧ�ľ��óɱ�����n�����������n(n-1)/2����·����ô�����ѡ��n-1����·��ʹ���ܷ������٣��˴��ķ��ÿ����ΪȨֵ��
* --���������ѧģ�ͣ�����Ȼ�˴�����ͨ����һ����������
* ���㡪����ʾ���У���n��
* �ߡ�����ʾ��·����n-1��
* �ߵ�Ȩֵ������ʾ��·�ľ��ô���
* ��ͨ��������ʾn�����м�ͨ����*/

/*˼·���������ڽӾ��������������ٱ���������С������*/
#include<iostream>
#include<stdio.h>
#define MVNum 100

typedef char VerTexType;
using namespace std;
typedef struct AMGraph{//�ڽӾ���ṹ��
	VerTexType vertices[MVNum];//�����
	int Graph[MVNum][MVNum];//Ȩֵ��
	int vexnum,arcnum;
}AMGraph;

//���ڽӾ������ҵ������ڶ�����ж�Ӧ��λ��
int LocateVex(AMGraph G,VerTexType u)
{
	for (int i = 0;i < G.vexnum;i++)
	{
		if (G.vertices[i] == u)
			return i;
	}
}
//������С������Minimun Spanning Tree
//MST���ʣ�
//���������Ĺ�������У�ͼ��n����������������ϣ�
//�������������ϵĶ��㼯��U
//��δ�����������ϵĶ��㼯��V-U
//��������Ӧ��������ͨU�ж����V-U�ж���ı���ѡȡȨֵ��С�ıߡ�

//������С����������һ��Prim�㷨����һ�����ϰ���һ�����㿪ʼ����Ȩֵ��С�ıߣ����ڽӵ�������㼯�ϣ����α�����
//�㷨˼�룺
//��N={V��E}����ͨ����TE��N����С�������бߵļ���
//��ʼ��U={u0},(u0��V)��TE={}
//������u��U��v��V-U�ıߣ�u,V����E�У���һ��������С�ıߣ�u0,v0��
//��(u0,v0)���뼯��TE��ͬʱv0����U
//�ظ���������ֱ��U=VΪֹ����T=(V,TE)ΪN����С������
//--�ص㣺
//--ѡ���
//--ʱ�临�Ӷȣ�O(n^2)
//--�ʺϳ���ͼ

void Prim(AMGraph G,VerTexType v0,int &sum)
{
	int lowcost[MVNum], vest[MVNum], v;//vestΪ��С������������
	int i, j, k, min;
	v = LocateVex(G,v0);//��v0���㿪ʼ������С������
	for (int i = 0;i < G.vexnum;++i)//��ʼ��lowcost�����vest����
	{
		lowcost[i] = G.Graph[v][i];
		vest[i] = 0;
	}
	vest[v] = 1;//��v0��������
	sum = 0;//sum���������ۼ�����Ȩֵ
	for (int i = 0;i < G.vexnum - 1;++i)
	{
		min = INT_MAX;//���ֵ����
		/*���ѭ������ѡ����ѡ���е���Сֵ*/
		for (int j = 0;j < G.vexnum;++j)
		{
			if (vest[j] == 0 && lowcost[j] < min)//ѡ����ǰ�����������ඥ����̱��е���̵�һ��
			{
				min = lowcost[j];
				k = j;
			}
		}
		vest[k] = 1;
		v = k;
		sum += min;//������sum��¼��С��������Ȩֵ
		/*�������ѭ���Ըղ���Ķ���vΪý����º�ѡ��*/
		for (j = 0;j < G.vexnum;++j)
		{
			if (vest[j] == 0 && G.Graph[v][j] < lowcost[j])
				lowcost[j] = G.Graph[v][j];
		}
	}
}

//������С��������������Kruskal�㷨��һ�����ϰ������ж��㵫��û�бߣ����α�����Ȩֵ��С�ıߣ�ǰ�������ǲ����γɻ���
//�㷨˼�룺
//����ͨ��N=(V,E),����С��������ʼ״̬Ϊֻ��n��������ޱߵķ���ͨͼT=��V��{}����ÿ�������Գ�һ����ͨ����
//��E��ѡȡ������С�ıߣ����ñ������Ķ�������T�в�ͬ����ͨ�����ϣ����������γɻ������򽫴˱߼��뵽T�У�������ȥ�˱ߣ�ѡȡ��һ��������С�ı�
//�������ƣ�ֱ��T�����ж��㶼��ͬһ��ͨ������Ϊֹ
//--�ص㣺
//--ѡ���
//--ʱ�临�Ӷȣ�O(eloge)��eΪ������
//--�ʺ�ϡ��ͼ
typedef struct Road{//Ϊʲô�˴���Ҫ���������ṹ�壬��ʲô����
	int a, b;//�ߵ���������
	int w;//Ȩֵ
}Road;
Road road[MVNum];
int v[MVNum];//���岢�鼯����
int getRoot(int a)//�ڲ��鼯�в��Ҹ����ĺ�����ͨ������һ����㣬�����ҵ���˫�׽�㣬�����ҵ�����㣨����˫�״洢�ṹ��
{
	while (a != v[a])
		a = v[a];
	return a;
}
void Kruskal(AMGraph G, int& sum, Road road[])
{
	int i;
	int N, E, a, b;
	N = G.vexnum;//������Ŀ
	E = G.arcnum;//����Ŀ
	sum = 0;
	for (int i = 0;i < N;++i)
	{
		v[i] = i;
	}
	sort(road, E);//��road�����е�E���߰���Ȩֵ��С��������sort��������
	for (int i = 0;i < E;++i)
	{
		a = getRoot(road[i].a);//��ȡ��i�Ķ���a
		b = getRoot(road[i].b);//��ȡ��i�Ķ���b
		if (a != b)//�����������ĸ��ڵ㲻��ͬ��˵�����������߲����γɻ������Խ������߼�����С�������С�
		{
			v[a] = b;
			sum += road[i].w;//����������Ȩֵ����䲢���Ǳ��㷨�Ĺ̶�д����Ҳ���Ըĳ������ġ����磬���������ĸ�����������ߴ����������
		}
	}
}

void CreateAMGraph(AMGraph& G)
{
	cout << "�������ڽӾ���Ķ�������ͱ߸�����" << endl;
	cin >> G.vexnum >> G.arcnum;
	for (int i = 0;i < G.vexnum;i++)
	{
		G.vertices[i] = 0;//��ʼ�������
	}
	cout << "�������ڽӾ���Ķ��㣺" << endl;
	for (int i = 0;i < G.vexnum;i++)
	{
		cin >> G.vertices[i];//���������ڽӾ���Ķ���
	}
	for(int i=0;i<G.vexnum;i++)//��ʼ���ڽӾ���
		for (int j = 0;j < G.vexnum;j++)
		{
			G.Graph[i][j] = 0;
		}
	//2�������ڽӾ���
	VerTexType v1, v2;
	int w;
	printf("������һ�����������Ķ����Լ��ߵ�Ȩֵ��\n");
	for (int k = 0;k < G.arcnum;++k)
	{
		cin >> v1 >> v2 >> w;//����һ�����������Ķ����Լ��ߵ�Ȩֵ
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);//ȷ��v1��v2��G�е�λ��
		G.Graph[i][j] = w;//��<v1,v2>��Ȩֵ��Ϊw
		G.Graph[j][i] = w;//��<v1,v2>�ĶԳƱ�<v2,v1>��ȨֵΪw
	}
}

int main(void)
{
	VerTexType v0;
	int sum;
	AMGraph G;
	CreateAMGraph(G);
	cout << "��������Ҫ��ʼ�Ķ��㣺" << endl;
	cin >> v0;
	Prim(G, v0, sum);//Prim�㷨
	cout << sum;
}
//��С���������ܲ�Ψһ
//ע�⣺Prim�㷨��Kruskal�㷨�����������ͼ�ģ�Ϊʲôֻ�������ͼ��