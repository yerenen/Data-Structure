/*���Ա�*/
/*��̬����������ķ�ʽʵ�ֵ�����*/
/*
--�ŵ㣺����ɾ��������Ҫ�����ƶ�Ԫ��
--ȱ�㣺���������ȡ��ֻ�ܴ�ͷ��㿪ʼ����������ң������̶����ɱ�
���ó�����
�ٲ�֧��ָ��ĵͼ����ԣ�
������Ԫ�������̶�����ĳ����������ϵͳ���ļ������
*/
#include<iostream>//��̬�������󳤶�
#include<stdio.h>
#define MAXSIZE 100
using namespace std;
typedef struct Node{
	int data;//�洢����Ԫ��
	int next;//��һ��Ԫ�ص������±�
}SLinkList;
/*
typedef struct Node{
	int data;//�洢����Ԫ��
	int next;//��һ��Ԫ�ص������±�
}SLinkList[MAXSIZE];
*/
//1����ʼ����̬�����ڴ洢�����н�����������
int InitList(SLinkList S[])
{
	for (int i = 0;i < MAXSIZE;i++)
	{
		S[i].next = i + 1;
	}
	S[MAXSIZE - 1].next = 0;
	return 0;
}
/*
int InitList(SLinkList S)
{
	for (int i = 0;i < MAXSIZE;i++)
	{
		S[i].next = i + 1;
	}
	S[MAXSIZE - 1].next = 0;
	return 0;
}
*/
#if 0
//����������ǿգ��򷵻ط���Ľ���±꣬���򷵻�0
int AllocNode(SLinkList& S)
{
	int i;
	i = S[0].next;
	if (i == 0)
		return 0;
	S[0].next = S[i].next;
	return i;
}
//���±�Ϊi�Ŀ��н����յ���������
void FreeNode(SLinkList S, int i)
{
	S[i].next = S[0].next;
	S[0].next = i;
}
//2������һ������n�����ľ�̬����,���ر�ͷ�ڴ洢�����λ��
void CreateList(SLinkList S, int n)
{
	int hesd, k, s, i;
	k = AllocNode(S);//�ӿ���������ȡ��һ���ս��
	head = k;
	for (int i = 1;i < -n;i++)
	{
		s = AllocNode(S);
		scanf("%d", &S[s].data);
		S[k].next = s;
		k = s;
	}
	S[k].next = 0;
	return head;
}
#endif
int main(void)
{
	SLinkList S[MAXSIZE];
	InitList(S);
	for (int i = 0;i < MAXSIZE;i++)
	{
		S[i].data = S[i].next;
		cout << S[i].data << endl;
	}
	return 0;
}
