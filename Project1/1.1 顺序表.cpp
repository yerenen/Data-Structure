/*���Ա�*/
/*˳�����˳��洢�ṹ*/
#include<iostream>
using namespace std;
#define maxsize 100
typedef struct //����˳���Ľṹ��
{
	int data[maxsize];//���˳���Ԫ�ص����飬Ĭ����int�ͣ��ɸ�����ĿҪ��int������������
	int length;//���˳���ĳ���
}Sqlist;
/*
˳���Ļ���������
1��InitList(&L);//��ʼ������������һ���յ����Ա�����Ϊ�漰ԭ��������Ҫ���Ķ�������ʹ�����õķ���&L��
2��DestroyList(&L);//�����Ѵ��ڵ����Ա�L������ԭ��
3��ClearList(&L);//�����Ա���գ��ʣ�Ϊʲô���漰���ã������ٱ���ʲô�����𣿣�
4��ListInsert(&L,i,e);//�����Ա�L��iλ�ò���eԪ�أ��ʣ�Ϊʲô�˴�e�������ã�
5��ListDelete(&L,i,&e);//ɾ�����Ա�L��iλ�õ�eԪ��,����e(�ʣ�ΪʲôeҲҪ���ã���Ԫ��ֱ��ɾ���������ˣ�������Ϊ�˸�ɶ)
6��IsEmpty(L);//bool���͵ĺ��������LΪ���򷵻�true�����򷵻�false
7��ListLength(L);//�������Ա�L��Ԫ�ظ���
8��LocateElem(L,e);//��ֵ���ң���L�в��������ֵe��ȵ�Ԫ�أ����ɹ����ظ�Ԫ���ڱ��е���ţ����򷵻�0
9��GetElem(L,i,&e);//��λ���ң���L�еĵ�i��λ��Ԫ�ط��ظ�e
*/

/*
˳����ɾ����
���Ա��ɾ��������ָ����ĵ�i(1<=i<=n)�����ɾ��ʹ����Ϊn�����Ա�(a1,...,ai-1,ai,ai+1,...,an)��ɳ���Ϊn-1�����Ա�(a1,...,ai-1,ai+1,...,an)
�㷨˼�룺
���ж�ɾ��λ��i�Ƿ�Ϸ����Ϸ�ֵΪ1<=i<=n��
�ڽ���ɾ����Ԫ�ر�����e��
�۽���i+1����nλ��Ԫ��������ǰ�ƶ�һ��λ��
�ܱ���һ��ɾ���ɹ�����OK
*/
/*
int ListDelete(Sqlist &L, int i,int &e)//������ɾ���㷨
{
	if ((i<1)||(i>L.length))//�ж�ɾ��λ���Ƿ�Ϸ�
		return false;
	e=L.data[i-1];
	for (int j = i;j < L.length;j++)
	{
		L.data[j-1] = L.data[j];
	}
	L.length--;
	return true;
}
*/
/*int ListDelete(Sqlist L, int i, int& e)//������ɾ������
{
	if ((i < 1) || (i > L.length))//1���ж�ɾ��λ��i�Ƿ�Ϸ�
		return false;
	e = L.data[i];
	for (int j=i;j <= L.length-1;j++)//2������i+1����nλ��Ԫ��������ǰ�ƶ�һ��λ��
	{
		e = L.data[i];
		L.data[j-1] = L.data[j];
		L.length--;//3������һ��ɾ���ɹ�����OK
	}
	return e;
}
//ʱ�临�Ӷȣ�n-1/2(O(n))
*/

/*
˳���Ĳ��룺
���Ա�Ĳ���������ָ�ڱ�ĵ�i��1<=i<=n+1����λ���ϣ�����һ���½��e��ʹ����Ϊn�����Ա�a1,...,ai-1,ai,...,an����ɳ���Ϊn+1�����Ա�a1,...,ai-1,e,ai,...,an����ɳ���Ϊn+1�����Ա�(a1,...,ai-1,e,ai,...,an)
�㷨˼�룺
���жϲ���λ��i�Ƿ�Ϸ�
���ж�˳���Ĵ洢�ռ��Ƿ�����������������ERROR
�۽���n����iλ��Ԫ����������ƶ�һ��λ�ã��ճ���i��λ��
*/
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
int InitList(Sqlist& L) //����һ���յ�˳���L;
{
	L.length = 0;
	return true;
}
int ListDelete(Sqlist& L, int i, int& e)//������ɾ���㷨
{
	if ((i < 1) || (i > L.length))//�ж�ɾ��λ���Ƿ�Ϸ�
		return false;
	e = L.data[i - 1];
	for (int j = i;j < L.length;j++)
	{
		L.data[j - 1] = L.data[j];
	}
	L.length--;
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
int Getlength(Sqlist L)//������������Ա�ĳ���
{
	return(L.length);
}
int main()
{
	Sqlist L;
	int e;
	/*
	int a = 0;
	int i = 0;
	L.length = 10;
	std::cout << "��һ�θ�ֵ������";
	for (int i = 0;i < 10; i++) //���Ա�����鸳ֵ
	{
		L.data[i] = i;
		std::cout << L.data[i];
	}
	ListInsert(L,2,6);
	std::cout << "��һ�����鳤��Ϊ��"<<L.length<<endl;
	std::cout << "��һ�β��������" ;
	for (int i = 0;i < 10; i++) //���Ա�����鸳ֵ
	{
		std::cout<< L.data[i];
	}
	std::cout << "�ڶ������鳤��Ϊ��" <<L.length<<endl;
	ListDelete(L, 3);
	std::cout << "��һ��ɾ��������";
	for (int i = 0;i < 10; i++) //���Ա�����鸳ֵ
	{
		std::cout<< L.data[i];
	}
	std::cout << "���������鳤��Ϊ��" <<L.length<<endl;
	*/
	InitList(L);
	std::cout << "��һ�γ�ʼ�����������鳤��Ϊ��" << Getlength(L) << endl;
	ListInsert(L, 1, 1);
	ListInsert(L, 2, 2);
	ListInsert(L, 3, 3);
	ListInsert(L, 4, 4);
	ListInsert(L, 5, 5);
	for (int i = 0;i < L.length; i++) //���Ա�����鸳ֵ
	{
		std::cout << L.data[i];
	}
	std::cout << "��һ�β�����������鳤��Ϊ��" << Getlength(L) << endl;
	ListDelete(L, 1, e);
	for (int i = 0;i < L.length; i++) //���Ա�����鸳ֵ
	{
		std::cout << L.data[i];
	}
	std::cout << "�ڶ���ɾ�����������鳤��Ϊ��" << Getlength(L) << endl;
	std::cout << "�ڶ���ɾ�������б�ɾ����Ԫ��Ϊ" << e << endl;
	std::cout << "��λ���ҵ�2λ��eԪ��ֵΪ��" << GetElem(L, 2, e) << endl;
	std::cout << "��ֵ����Ԫ��ֵΪ3�������������е�λ��Ϊ��" << LocateElem(L, 3) << endl;
	return 0;
}
