/*���Ա�*/
/*��ջ������ʽ�洢�ṹ*/
/*��ջ���������޵ĵ�����ֻ��������ͷ�����в���*/
#include<iostream>
#include<stdio.h>
using namespace std;
typedef struct StackNode {
	int data;
	struct StackNode* next;
}StackNode,*LinkStack;
/*��ջ�㷨һ����ջ�ĳ�ʼ��*/
int InitStack(LinkStack& S)
{
	//����һ����ջ��ջ��ָ����Ϊ��
	S = NULL;
	return 0;
}
/*��ջ�㷨�����ж���ջ�Ƿ�Ϊ��*/
int StackEmpty(LinkStack S)
{
	if (S == NULL)
		return 0;
	else
		return 1;
}
/*��ջ�㷨������ջ����ջ*/
int Push(LinkStack& S, int e)
{
	LinkStack p = new StackNode;//�����½��p
	p->data = e;//���½����������Ϊe
	p->next = S;//���½�����ջ��
	S = p;//�޸�ջ��ָ��
	return 0;
}
/*��ջ�㷨�ģ���ջ�ĳ�ջ*/
int Pop(LinkStack& S, int& e)
{
	if (S == NULL)
		return 0;
	e = S->data;
	LinkStack p = S;
	S = S->next;
	delete p;
	return 0;
}
/*��ջ�㷨�壺ȡջ��Ԫ��*/
int GetTop(LinkStack S)
{
	if (S != NULL)
		return S->data;
}
void scanStack(LinkStack S)
{
	while (S)
	{
		cout << S->data << endl;
		S = S->next;
	}
}
int main()
{
	int e;
	LinkStack S;
	InitStack(S);
	cout<<"�Ƿ�ջ�գ�ջ�շ���0�����շ���1��" << StackEmpty(S) << endl;
	Push(S, 1);
	Push(S, 2);
	Push(S, 3);
	scanStack(S);
	Pop(S,e);
	cout << "����ջ��Ԫ�غ�" << endl;
	scanStack(S);
}
/*ջ��ݹ�*/
/*1���ݹ�Ķ���*/
/*��һ�����󲿷ֵذ������Լ����������Լ����Լ����壬�����������ǵݹ�ģ�*/
/*��һ������ֱ�ӻ��ӵص����Լ��������������ǵݹ�Ĺ��̡����磺�ݹ���n�Ľ׳ˡ�*/
/*2������������������õ��ݹ鷽����*/
/*�ٵݹ鶨�����ѧ������*/
/*�ھ��еݹ����Ե����ݽṹ���������������...*/
/*�ۿɵݹ��������⣺�Թ����⣬Hanoi������...*/
/*3�����η����ݹ������㷨��һ����ʽ��*/
/*void p��������*/
/*{
if(�ݹ��������) ��ֱ����ⲽ��;����������*/
/*else p����С�Ĳ�����;}����������*/