#if 0
��
1.1 ������
1.1.1 ������������Threaded Binary Tree��
--ΪʲôҪ�о�������������
���ö���������Ϊ�������Ĵ洢�ṹʱ�����Ժܷ�����ҵ�ĳ���������Һ��ӣ���һ������£��޷�ֱ���ҵ��ý����ĳ�ֱ��������е�ǰ���ͺ�̽�㡣
--���������
��ͨ������Ѱ�ҡ�����ʱ��
��������ǰ�������ָ���򡪡������˴洢����
�����ö�������Ŀ�ָ���򡪡����ĳ����������Ϊ�գ��򽫿յ�����ָ�����Ϊָ����ǰ�������ĳ�����Һ���Ϊ�գ��򽫿յ��Һ���ָ�����Ϊָ�����̡��������ָı�ָ���ָ�뱻��Ϊ������
--���ּ����������Ķ�������Ϊ����������(Threaded Binary Tree)
���ڶ�������ĳ�ֱ�������ʹ���Ϊ�����������Ĺ��̽���������
#endif
#include<iostream>
#include<stdio.h>
using namespace std;
//Ϊ������lchild��rchildָ�뵽����ָ���ӵ�ָ�룬����ָ��ǰ�����ߺ�̵�ָ�룬�Զ���������ÿ���������������־��ltag��rtag����Լ����
//ltag=0  lchildָ��ý�������
//ltag=1  lchildָ��ý���ǰ��
//rtag=0  rchildָ��ý����Һ���
//rtag=1  lchildָ��ý��ĺ��
typedef char TElemType;
typedef struct BiThrNode{
	TElemType data;//���������
	int ltag, rtag;//��ű������
	struct BiThrNode* lchild;
	struct BiThrNode* rchild;
}BiThrNode,*BiThrTree;
TElemType Nil = '#';
void CreateBiThrTree(BiThrTree *T)
{
	TElemType h;
	cin >> h;
	if (h == Nil)
		*T = NULL;
	else
	{
		*T = (BiThrTree)malloc(sizeof(BiThrNode));
		if (!*T)
			exit(OVERFLOW);
		(*T)->data = h;
		CreateBiThrTree(&((*T)->lchild));
		if ((*T)->lchild)//���������
			(*T)->ltag = 0;
		CreateBiThrTree(&((*T)->rchild));
		if ((*T)->lchild)//������Һ���
			(*T)->rtag = 0;
	}
}
void InOrderTraverse_Thr(BiThrTree T)//�������
{
	//?
}
int main(void)
{
	BiThrTree H=NULL;
	printf("�밴ǰ�����������(��:'ABDH##I##EJ###CF##G##')\n");
	CreateBiThrTree(&H); /* ��ǰ����������� */
	cout << H->lchild->data << endl;
	InOrderTraverse_Thr(H);
}