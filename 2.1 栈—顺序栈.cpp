/*���Ա�*/
/*˳��ջ����˳��洢�ṹ*/
/*�洢��ʽ��ͬһ�����Ա��˳��洢�ṹ��ȫ��ͬ*/
/*����һ���ַ�����Ĵ洢��Ԫ���δ����ջ�׵�ջ��������Ԫ�ء�ջ��һ���ڵ͵�ַ��*/
/*--����topָ�룬ָʾջ��Ԫ����˳��ջ�е�λ��*/
/*--����baseָ�룬ָʾջ��Ԫ����˳��ջ�е�λ��*/
#include<iostream>
#include<stdio.h>
#define MAXSIZE 100
using namespace std;
typedef struct {
	int *base;//ջ��ָ��
	int *top;//ջ��ָ��
	int stacksize;//ջ�����������
}SqStack;
/*˳��ջ�㷨һ��˳��ջ�ĳ�ʼ��*/
int InitStack(SqStack& S)//����һ����ջ
{
	S.base = new int[MAXSIZE];//��S.base=(SElemtype*)malloc(MAXSIZE *sizeof(SElemtype));
	if (!S.base)exit(OVERFLOW);//�洢����ʧ��
	S.top = S.base;//ջ��ָ�����ջ��ָ��
	S.stacksize = MAXSIZE;
	return 0;
}
/*˳��ջ�㷨�����ж�˳��ջ�Ƿ�Ϊ��*/
int Is_Empty(SqStack& S)
{
	//��ջ�գ��򷵻�TRUE�����򷵻�FALSE
	if (S.top == S.base)
		return 0;
	else
		return 1;
}
/*˳��ջ�㷨������˳��ջ����*/
int StackLength(SqStack S)
{
	return S.top - S.base;
}
/*˳��ջ�㷨�ģ����˳��ջ*/
int ClearStack(SqStack &S)//�����⣬�Ƿ���Ҫ�����÷�
{
	if (S.base)//�ж�ջ�Ƿ����
		S.top = S.base;
	return 0;
}
/*˳��ջ�㷨�壺����˳��ջ*/
int DestroyStack(SqStack& S)
{
	if (S.base) {//���ջ�����Ҳ�Ϊ��
		delete S.base;//ɾ��ջ��ָ��
		S.stacksize = 0;//��ջ�ĸ�������Ϊ0
		S.base = S.top = NULL;//topָ���baseָ�������Ϊ�գ������Ѿ�ɾ��ջ��ָ������Ϊʲô��Ҫ�ÿգ�
	}
	return 0;
}
/*˳��ջ�㷨����˳��ջ����ջ*/
/*�㷨˼�룺
* ���ж��Ƿ�ջ����������������磩
* ��Ԫ��eѹ��ջ��
* ��ջ��ָ���һ*/
int Push(SqStack& S, int e)
{
	if (S.top - S.base == S.stacksize)//ջ��
		return 1;
	*S.top++ = e;//��e����topָ����ָ�Ŀռ䣬Ȼ��topָ����һ�ռ�
	return 0;
}
/*˳��ջ�㷨�ߣ�˳��ջ�ĳ�ջ*/
/*�㷨˼�룺
* ���ж��Ƿ�ջ�գ�������������磩
* �ڻ�ȡջ��Ԫ��e
* ��ջ��ָ���һ*/
int pop(SqStack& S, int& e)
{
	//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
	if (S.top == S.base)//�ȼ���if(StackEmpty(S))
		return 1;
	else
	{
		e = *--S.top;//ָ�������ƣ�Ȼ����ȡָ�뵱����ȡ��Ԫ�ص�ֵ��ֵ��e
		return 0;
	}
}
void ScanSqStack(SqStack S)//����ջ
{
	int e = StackLength(S);
	if (e > 0)
	{
		for (int i = 0;i < e;i++)
		{
			cout << S.base[i] << endl;
		}
	}
	else
	{
		cout << "˳��ջΪ��" << endl;
	}
}
int main()
{
	int e;
	SqStack S;
	InitStack(S);//��ʼ��ջ
	Push(S, 1);//��ջ
	Push(S, 2);
	Push(S, 3);
	Push(S, 4);
	Push(S, 5);
	ScanSqStack(S);
	cout<<"ջ����Ϊ" << StackLength(S) << endl;
	pop(S,e);//��ջ
	ScanSqStack(S);//����ջ
	cout << "ջ����Ϊ" << StackLength(S) << endl;
	ClearStack(S);
	cout<<"�ж��Ƿ�ջ�գ����ջ�շ���0�����ջ���շ���1��" << Is_Empty(S) << endl;
	DestroyStack(S);
	ScanSqStack(S);//����ջ
}