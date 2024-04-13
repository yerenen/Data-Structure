/*队列*/
/*队列是仅在表尾进行插入操作，在表头进行删除操作的线性表。*/
/*表尾即an端，称为队尾；表头即a1端，称为队头。*/
/*它是一种先进先出(FIFO)的线性表。*/
/*顺序队列——顺序存储结构*/
#include<iostream>
#include<stdio.h>
#define MAXQSIZE 100//最大队列长度
using namespace std;
typedef struct {
	int* base;//初始化的动态分配存储空间
	int front;//头指针
	int rear;//尾指针
}SqQueue;
/*顺序队列算法1——队列的初始化*/
int InitQueue(SqQueue& Q)
{
	Q.base = new int[MAXQSIZE];//分配数组空间
	//Q.base=(QElemType *)malloc(MAXSIZE *sizeof(QElemType));
	if (!Q.base) exit(OVERFLOW);//存储分配失败
	Q.front = Q.rear = 0;//头指针尾指针置为0，队列为空
	return 0;
}
/*顺序队列算法2——求队列的长度*/
int QueueLength(SqQueue Q)
{
	return((Q.rear - Q.front+MAXQSIZE)%MAXQSIZE);
}
/*顺序队列算法3——循环队列出队*/
int DeQueue(SqQueue& Q, int& e)
{
	if (Q.front == Q.rear)//队空
		return 0;
	e = Q.base[Q.front];//保存队头元素
	Q.front = (Q.front + 1) % MAXQSIZE;//队头指针+1
	return e;
}
/*顺序队列算法3.1——循环队列入队*/
int InsertQueue(SqQueue& Q, int e)
{
	//需要判断队列是否为满队列吗？如何判断
	Q.base[Q.rear] = e;//将要插入的元素赋给rear指针
	Q.rear = (Q.rear + 1) % MAXQSIZE;//队尾指针+1
	return 0;
}
/*顺序队列算法4——取队头元素*/
int GetHead(SqQueue Q)
{
	if (Q.front != Q.rear)//队列不为空
		return Q.base[Q.front];//返回队头指针元素的值，队头指针不变
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
	InitQueue(Q);//初始化队列
	InsertQueue(Q, 1);//插入队列元素
	InsertQueue(Q, 2);
	InsertQueue(Q, 3);
	cout<<"队头元素为："<<GetHead(Q)<<endl;
	scanQueue(Q);//遍历队列
	cout<<"出队元素为："<<DeQueue(Q, e)<<endl;
	InsertQueue(Q, 4);
	scanQueue(Q);
}