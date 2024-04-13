/*���Ա�*/
/*���Ա��Ӧ��*/
#include<stdio.h>
#include<iostream>
using namespace std;
#define maxsize 100
typedef struct {
	int data[maxsize];
	int length;
}Sqlist;
/*Ӧ��һ�����������������Ա�La��Lb�ֱ��ʾ��������A��B����Ҫ��һ���µļ���A=AUB*/
//�㷨���裺
//����ȡ��Lb�е�ÿ��Ԫ�أ�ִ�����²�����
//����La�в��Ҹ�Ԫ��
//������Ҳ������������La�����
int ListInsert(Sqlist& L, int i, int e)//�������������������iλ�ò���eԪ�أ��ʣ�i��e�Ƿ����û���������ֵ����
{
	if (i<1 || i>L.length + 1)//�жϲ���λ���Ƿ�Ϸ�
		return false;
	if (L.length == maxsize)//�жϴ洢�ռ��Ƿ�Ϊ��
		return false;
	for (int j = L.length - 1;j >= i - 1;j--)//ע��˴�jΪL.length-1,�Ҳ����ǵ��Ų�
		L.data[j + 1] = L.data[j];
	L.data[i - 1] = e;
	L.length++;
	return true;
}
int GetElem(Sqlist L, int i, int& e) //��������λ���ҡ��������Ա��в���iλ�õ�Ԫ�أ����ظ�e��ע��˴������÷���&��ʵ��ʹ�÷���
{
	e = L.data[i - 1];//ע�����ﷵ�ص��������i-1
	return e;
}
int LocateElem(Sqlist L, int e)//��������ֵ���ҡ��������Ա�L�в���ֵΪe������λ��
{
	int i;
	for (i = 0;i < L.length;i++)
	{
		if (L.data[i] == e)
			return i + 1;
	}
	return -1;
}
int InitList(Sqlist& L) //����һ���յ�˳���L;
{
	L.length = 0;
	return true;
}
/*�ҽ�,�ҽ���ǽⲻ����*/
void merge(Sqlist &L,Sqlist J) 
{
	int i=0;
	int j=0;
	for (int i = 0;i < L.length;i++)//��������L
	{
		while (j < J.length)
		{
			while (L.data[i] != J.data[j])//
			{
				L.data[L.length++] = J.data[j++];
			}
		}
	}
}
/*���*/
/*���ԵĽ�����о���ֵ��û�ɹ��ϲ�������*/
void union_L(Sqlist& La, Sqlist Lb)
{
	int e;
	int La_len = La.length;
	int Lb_len = Lb.length;
	for (int i = 1;i <= Lb.length;i++)
	{
		GetElem(Lb, i, e);//�����Ա�Lb��ÿ��ֵ˳��ȡ����������ʲôֵ
		if (!LocateElem(La, e))//��ֵ���ң���La���Ա����Ƿ������Ԫ��
			ListInsert(La, ++La_len, e);//���La���Ա���û��eԪ�أ������������
	}
}
/*Ӧ�ö�����֪���Ա�La��Lb�е�����Ԫ�ذ�ֵ�ǵݼ�������?���������У���Ҫ��La��Lb�鲢Ϊһ���µ����Ա�Lc����Lc�е�����Ԫ���԰�ֵ�ǵݼ���������*/
//�㷨���裺
//�ٴ���һ���ձ�Lc
//�����δ�La��Lb�С�ժȡ��Ԫ��ֵ��С�Ľ����뵽Lc������ֱ������һ������Ϊֹ
//�ۼ�����La��Lb����һ�����ʣ���������Lc������
/*��⡪�������ϲ�����˳���ʵ��,˫ָ��ʵ��*/
/*
void MergeList_Sq(Sqlist LA, Sqlist LB, Sqlist& LC)
{
	pa = LA.elem;
	pb = LB.elem;//ָ��pa��pb�ĳ�ֵ�ֱ�ָ��������ĵ�һ��Ԫ��
	LC.length = LA.length + LB.length;//�±���Ϊ���ϲ�����ĳ���֮��
	LC.elem = new ElemType[LC.length];//Ϊ�ϲ�����±����һ������ռ�
	pc = LC.elem;//ָ��pcָ���±�ĵ�һ��Ԫ��
	pa_last = LA.elem + LA.length - 1;//ָ��pa_lastָ��LA������һ��Ԫ��
	pb_last = LB.elem + LB.length - 1;//ָ��pb_lastָ��LB������һ��Ԫ��
	while(pa<=pa_last&&pb<=pb_last){//�������ǿ�
		if (*pa <= *pb)//���Ρ�ժȡ��������ֵ��С�Ľ��
			*pc++ = *pa++;
		else
			*pc++ = *pb++;
	}
	while (pa <= pa_last)//LB���ѵ����β����LA��ʣ��Ԫ�ؼ���LC
		*pc++ = *pa++;
	while (pb <= pb_last)//LA���ѵ����β����LB��ʣ��Ԫ�ؼ���LC
		*pc++ = *pb++;
}
*/
void merge_L(Sqlist La, Sqlist Lb,Sqlist &Lc)
{
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < La.length && j < Lb.length)
	{
		if (La.data[i] < Lb.data[j])
		{
			Lc.data[k++] = La.data[i++];
		}
		else
		{
			Lc.data[k++] = Lb.data[j++];
		}
	}
	while (i < La.length)
	{
		Lc.data[k++] = La.data[i++];
	}
	while (j < Lb.length)
	{
		Lc.data[k++] = Lb.data[j++];
	}
	Lc.length = La.length + Lb.length;
}
int main()
{
	Sqlist J;
	Sqlist L;
	Sqlist K;
	InitList(L);
	InitList(J);
	InitList(K);
	ListInsert(L, 1, 2);
	ListInsert(L, 2, 4);
	ListInsert(L, 3, 6);
	ListInsert(J, 1, 1);
	ListInsert(J, 2, 3);
	ListInsert(J, 3, 5);
	//union_L(L, J);
	/*for (int i = 0;i < L.length;i++)
	{
		cout << L.data[i] << endl;
	}*/
	merge_L(L, J, K);
	for (int i= 0;i < K.length;i++)
	{
		cout << K.data[i] << endl;
	}
	cout << "K���Ա�ĳ���Ϊ" <<K.length<< endl;
	return 0;
}

