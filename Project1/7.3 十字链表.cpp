/*
* ͼ�Ĵ洢�ṹ
* --ʮ������
* ���ڽӱ�Ļ�����Ϊ�˽������ͼ����Ķ����ѵ�ȱ��
*/
#include<iostream>
#include<stdio.h>
#define MVNum 100
using namespace std;

typedef int VerTexType;
typedef int InfoType;
typedef struct ArcNode{//�߽��
	int tailvex, headvex;//�û���β��ͷ�����λ��
	ArcNode* hink,*tlink;//�ֱ�Ϊ��ͷ��ͬ�ͻ�β��ͬ�Ļ�������
	InfoType info;//�û������Ϣ
}ArcNode;
typedef struct VNode{//������
	VerTexType data;
	ArcNode* firstin,*firstout;//�ֱ�ָ��ö����һ���뻡�ͳ���
}VNode;
typedef struct OLGraph{//ͼ
	VNode vertices[MVNum];//��ͷ����
	int vexnum, arcnum;//����ͼ�ĵ�ǰ�������ͻ���
}OLGraph;
void CreateDG(OLGraph& G)//����ʮ������
{

}
int main(void)
{

}
