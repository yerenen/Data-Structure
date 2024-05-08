#include<iostream>
#include<stdio.h>
#define MAXSIZE 100
using namespace std;
typedef int KeyType;
typedef struct {
	KeyType key;
}RedType;
typedef struct SqList{
	RedType r[MAXSIZE+1];
	int length;
}SqList;

//�⣺�ҳ�������δ���ֵ���С������(��д)
//���㣺����
//ʱ�临�Ӷȣ�O(n^2)
//�ռ临�Ӷȣ�O(1)
//�˴�ʹ�õ���ֱ�Ӳ��������㷨�ȶ�
int Search_Min(SqList &L)
{
	//�������ų�����
	//int i;//��ʾ���򲿷ֵ�һ��λ��
	int j;//��ʾ����λ�ù�����Ѱ�ҵ��±�
	for (int i = 2; i <= L.length; ++i)
	{
		if (L.r[i].key < L.r[i - 1].key)//�����򲿷ֵڶ���Ԫ�رȵ�һ��Ԫ��С���轫L.r[i]���������ӱ�
		{
			L.r[0] = L.r[i];//����Ϊ�ڱ�
			for (j = i - 1; L.r[0].key < L.r[j].key; --j)
			{
				L.r[j + 1] = L.r[j];//��¼����
			}
			L.r[j + 1] = L.r[0];//���뵽��ȷλ��
		}
	}
	//����������������С������
	int k = 1;
	for (int n = 1; n < L.length+1; n++)
	{
		if (L.r[n].key == k && L.r[n].key >0)
			k++;
	}
	return k;
}

//�⣺�ҳ�������δ���ֵ���С������(���)
//���㣺����
//ʱ�临�Ӷȣ�O(n)
//�ռ临�Ӷȣ�O(n)
//�ռ任ʱ��
int R[MAXSIZE];//��������
int Search_Min_Stan(SqList& L)
{
	int i = 0;
	for (int i = 1; i <= L.length; i++)
	{
		if (L.r[i].key > 0 && L.r[i].key <= L.length)
			R[i] = i;
	}
	for (int i = 1; i <= L.length; i++)
	{
		if (L.r[i].key == 0)
			return i;
	}
	return i + 1;
}

int main(void)
{
	SqList L;
	//��ʼ��˳���
	for (int i = 0; i < MAXSIZE+1; i++)
	{
		L.r[i].key = 0;
	}
	L.length = 0;
	//��˳���ֵ
	cout << "������˳����ȣ�" << endl;
	cin >> L.length;
	cout << "������˳���Ԫ�أ�" << endl;
	for (int i = 1; i < L.length+1; i++)
	{
		cin >> L.r[i].key;
	}
	cout << "��⣺" << Search_Min_Stan(L) << endl;//���������
	cout << "�Խ⣺" << Search_Min(L) << endl;//���
}