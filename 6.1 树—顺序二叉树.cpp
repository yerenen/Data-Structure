#if 0
��
1.1 ������
1.1.1 ��������˳��洢
--ȱ�㣺
���������Ϊk����ֻ��k�����ĵ�֧����Ҫ����Ϊ2(k) - 1��һά���顣����������
--�ص㣺
���֮��Ĺ�ϵ�̺�����洢λ�����˷ѿռ䣬���ڴ�������������ȫ��������
#endif

#include<iostream>
#include<stdio.h>
using namespace std;
#define MAXSIZE 100//���������������
typedef int TElemType;//�������������ͣ�Ŀǰ�ݶ�Ϊ����
typedef TElemType SqBiTree[MAXSIZE];//0�ŵ�Ԫ�洢�����
SqBiTree T;
TElemType Nil = 0;

//�����ʼ��������
//��ΪT�ǹ̶����鲻��ı䣬���Դ˴�����Ҫ&
void InitBiTree(SqBiTree T)
{
	int i;
	for (int i = 0;i < MAXSIZE;i++)
	{
		T[i] = Nil;
	}
}

int main(void)
{
	SqBiTree T;
	InitBiTree(T);
	for (int i = 0;i < MAXSIZE;i++)
	{
		cout << T[i] << endl;
	}
}