#if 0
9 ����
9.3 ��������
9.3.1 ����˼��
�����Ƚϣ�������������򽻻���ֱ�����м�¼���ź���Ϊֹ��
9.3.2 �����Ľ������򷽷�
--ð������O��n^2����
--��������O��nlog2n����
9.3.3 ð������
9.3.3.1 ����˼��
ÿ�˲��Ͻ���¼�����Ƚϣ�������ǰС��󡱹��򽻻�
9.3.4 �������򡪡��Ľ��Ľ�������
9.3.4.1 ����˼��(�ݹ�)
����ȡһ��Ԫ�أ��磺��һ����Ϊ���ģ�pivot��
�����б���С��Ԫ��һ����ǰ�ţ��������Ԫ��һ�ɺ��
���γ����������ӱ�
�ܶԸ��ӱ�����ѡ������Ԫ�ز��Դ˹������
��ֱ��ÿ���ӱ��Ԫ��ֻʣһ��
9.3.4.2 �ص�
��ÿһ�˵��ӱ���γ��ǲ��ô���ͷ���м佻��ʽ�ƽ���
������ÿ���жԸ��ӱ�Ĳ��������ƣ��ɲ��õݹ��㷨
#endif

#include<iostream>
#include<stdio.h>
#define MAXSIZE 20//���¼������20
using namespace std;
typedef int KeyType;//��ؼ���Ϊ��������int�ͣ�
typedef struct RedType {//����ÿ����¼������Ԫ�أ��Ľṹ
	KeyType key;//�ؼ���
	//InfoType otherinfo;//����������
}RedType;//Record Type
typedef struct SqList {//����˳���Ľṹ
	RedType r[MAXSIZE + 1];//�洢˳��������
	//r[0]һ�����ڱ��򻺳���
	int length;//˳���ĳ���
}SqList;
//SqList T;
//RedType R;

//ð�������㷨���Ż�ǰ��
//�ŵ㣺ÿ�˽���ʱ�������ܼ���һ�����ֵ�������λ�ã�����ͬʱ������˳����Ԫ�أ�
//������Ч�ʣ�
//һ��ĳһ�˱Ƚ�ʱ�����ּ�¼������˵�����ź����ˣ��Ϳ��Խ������㷨
void bubble_sort(SqList& L)
{
	int n = L.length;
	int m, i, j;
	RedType x;//����ʱ��ʱ�洢
	for (int m = 1; m <= n - 1; m++)//�ܹ�m��
	{
		for (int j = 1; j <= n - m; j++)
		{
			if (L.r[j].key > L.r[j + 1].key)//��������
			{
				x = L.r[j];//����
				L.r[j] = L.r[j + 1];
				L.r[j + 1] = x;
			}//endif
		}//for
	}
}

//ð�������㷨���Ż���
//1��ʱ�临�Ӷȣ�
//�������������򱾾������򣩣�
//�Ƚϴ�����n-1
//�ƶ�������0
//ʱ�临�Ӷȣ�O(n)
//�����������������򣩣�
//�Ƚϴ�����n(n-1)/2
//�ƶ�������3n(n-1)/2
//ʱ�临�Ӷȣ�O(n^2)
//��ƽ��ʱ�临�Ӷȣ�O(n^2)
//�����ռ䣺S(n) = O(1)
//2���ص㣺ð���������ȶ���
void bubble_sort_best(SqList& L)//�Ľ����ð�������㷨
{
	int n = L.length;
	int m, i, j, flag = 1;//flag��Ϊ�Ƿ��н����ļ�¼
	RedType x;
	for (int m = 1; m <= n - 1 && flag == 1; m++)
	{
		flag = 0;
		for (int j = 1; j <= m; j++)
		{
			if (L.r[j].key > L.r[j + 1].key) {//��������
				flag = 1;//����������flag��Ϊ1��������û����������flag����Ϊ0
				x = L.r[j];
				L.r[j] = L.r[j + 1];
				L.r[j + 1] = x;//����
			}//endif
		}//for
	}
}

//�����ĵ��λ��
int Partition(SqList &L, int low, int high)
{
	L.r[0] = L.r[low];
	int pivotkey = L.r[low].key;
	while (low < high)
	{
		while (low < high && L.r[high].key >= pivotkey)//���highָ��ָ���ֵ����pivotkey
			--high;//Ԫ�ؿ��Բ��ö���highָ������
		L.r[low] = L.r[high];//ֱ������highָ��ָ���ֵС��pivot���򸳸�lowָ��
		while (low < high && L.r[low].key <= pivotkey)
			++low;
		L.r[high] = L.r[low];
	}
	L.r[low] = L.r[0];
	return low;
}

//��˳���L��������
//���������㷨����
//��ʱ�临�Ӷȣ�ƽ��ʱ�临�Ӷ�ΪO(nlog2n)
//Qsort()��O(log2n)
//Partition()��O(n)
//�ڿռ临�Ӷ�
//����������ԭ������
//��ƽ������£���Ҫ��O(logn)��ջ�ռ�
//�����£�ջ�ռ�ɴ�O(n)
//���ȶ���
//����������һ�ֲ��ȶ������򷽷�
//�ܻ���Ԫ�ص�ѡȡ��Ӱ��ʱ�����ܵĹؼ�
//�������ݴ���Խ�ң���ѡ����Ԫ�ص�ֵ�������Խ�ã������ٶ�Խ�죬������������Ȼ���򷽷�
//�ı仮��Ԫ�ص�ѡȡ����������ֻ�ܸı��㷨ƽ������µ��������ܣ��޷��ı������µ�ʱ�����ܡ��������£����������ʱ�临�Ӷ�����O(n^2)
void QSort(SqList& L, int low, int high)
{
	if (low < high) {//���ȴ���1
		int pivotloc = Partition(L, low, high);
		//��L.r[low...high]һ��Ϊ����pivotlocΪ����Ԫ���ź����λ��
		QSort(L, low, pivotloc - 1);//�Ե��ӱ�ݹ�����
		QSort(L, pivotloc + 1, high);//�Ը��ӱ�ݹ�����
	}//endif
}//QSort

int main(void)
{
	SqList L;
	int n = MAXSIZE;
	//��˳����ʼ��
	for (int i = 1; i < MAXSIZE+1; i++)
	{
		L.r[i].key = n;
		n--;
	}
	L.length = MAXSIZE + 1;
	//�����ʼ˳���
	cout << "��ʼ˳���Ϊ��" << endl;
	for (int i = 1; i < MAXSIZE + 1; i++)
	{
		cout << L.r[i].key << " ";
	}
	cout << endl;
	//��������
	QSort(L, 1, L.length);
	cout << "ʹ�ÿ��������˳���Ϊ��" << endl;
	for (int i = 1; i < MAXSIZE + 1; i++)
	{
		cout << L.r[i].key<<" ";
	}
	cout << endl;
	//ð�������Ż�ǰ��
	bubble_sort(L);
	cout << "ʹ��ð�������˳���Ϊ��" << endl;
	for (int i = 1; i < MAXSIZE + 1; i++)
	{
		cout << L.r[i].key << " ";
	}
	cout << endl;
	//ð�������Ż���
	bubble_sort_best(L);
	cout << "ʹ���Ż����ð�������˳���Ϊ��" << endl;
	for (int i = 1; i < MAXSIZE + 1; i++)
	{
		cout << L.r[i].key << " ";
	}
	return 0;
}