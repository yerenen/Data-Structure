/*线性表*/
/*链串——链式存储结构（块链结构）*/
#include<iostream>
#include<stdio.h>
#define CHUNKSIZE 80//块的大小可由用户定义
using namespace std;
typedef struct Chunk {
	char ch[CHUNKSIZE];
	struct Chunk* next;
}Chunk;
typedef struct {
	Chunk * head, * tail;//串的头指针和尾指针
	int curlen;//串的当前长度
}LString;//字符串的快链结构