/*����*/
/*�����ǽ��ڱ�β���в���������ڱ�ͷ����ɾ�����������Ա�*/
/*��β��an�ˣ���Ϊ��β����ͷ��a1�ˣ���Ϊ��ͷ��*/
/*����һ���Ƚ��ȳ�(FIFO)�����Ա�*/
/*˳����С���˳��洢�ṹ*/
#include<iostream>
#include<stdio.h>
#define MAXQSIZE 100//�����г���
using namespace std;
typedef struct {
	int* base;//��ʼ���Ķ�̬����洢�ռ�
	int front;//ͷָ��
	int rear;//βָ��
}SqQueue;
/*˳������㷨1�������еĳ�ʼ��*/
int InitQueue(SqQueue& Q)
{
	Q.base = new int[MAXQSIZE];//��������ռ�
	//Q.base=(QElemType *)malloc(MAXSIZE *sizeof(QElemType));
	if (!Q.base) exit(OVERFLOW);//�洢����ʧ��
	Q.front = Q.rear = 0;//ͷָ��βָ����Ϊ0������Ϊ��
	return 0;
}
/*˳������㷨2��������еĳ���*/
int QueueLength(SqQueue Q)
{
	return((Q.rear - Q.front+MAXQSIZE)%MAXQSIZE);
}
/*˳������㷨3����ѭ�����г���*/
int DeQueue(SqQueue& Q, int& e)
{
	if (Q.front == Q.rear)//�ӿ�
		return 0;
	e = Q.base[Q.front];//�����ͷԪ��
	Q.front = (Q.front + 1) % MAXQSIZE;//��ͷָ��+1
	return e;
}
/*˳������㷨3.1����ѭ���������*/
int InsertQueue(SqQueue& Q, int e)
{
	//��Ҫ�ж϶����Ƿ�Ϊ������������ж�
	Q.base[Q.rear] = e;//��Ҫ�����Ԫ�ظ���rearָ��
	Q.rear = (Q.rear + 1) % MAXQSIZE;//��βָ��+1
	return 0;
}
/*˳������㷨4����ȡ��ͷԪ��*/
int GetHead(SqQueue Q)
{
	if (Q.front != Q.rear)//���в�Ϊ��
		return Q.base[Q.front];//���ض�ͷָ��Ԫ�ص�ֵ����ͷָ�벻��
	return 1;
}
void scanQueue(SqQueue Q)
{
	int e = Q.front;
	int r = Q.rear;
	for (int i = e;i < r;i++)
	{
		cout << Q.base[i] << endl;
	}
}
int main()
{  
	int e;
	SqQueue Q;
	InitQueue(Q);//��ʼ������
	InsertQueue(Q, 1);//�������Ԫ��
	InsertQueue(Q, 2);
	InsertQueue(Q, 3);
	cout<<"��ͷԪ��Ϊ��"<<GetHead(Q)<<endl;
	scanQueue(Q);//��������
	cout<<"����Ԫ��Ϊ��"<<DeQueue(Q, e)<<endl;
	InsertQueue(Q, 4);
	scanQueue(Q);
}