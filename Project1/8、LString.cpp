/*���Ա�*/
/*����������ʽ�洢�ṹ�������ṹ��*/
#include<iostream>
#include<stdio.h>
#define CHUNKSIZE 80//��Ĵ�С�����û�����
using namespace std;
typedef struct Chunk {
	char ch[CHUNKSIZE];
	struct Chunk* next;
}Chunk;
typedef struct {
	Chunk * head, * tail;//����ͷָ���βָ��
	int curlen;//���ĵ�ǰ����
}LString;//�ַ����Ŀ����ṹ