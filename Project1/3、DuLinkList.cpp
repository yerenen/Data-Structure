/*线性表*/
/*双向链表——链式存储结构*/
/*需要区分带不带头结点吗*/
#include<iostream>
#define ERROR
#define OK
using namespace std;
typedef struct DuLNode {
	int data;
	struct DuLNode *prior, *next;
}DuLNode,*DuLinkList;//这里如何区分左指针和右指针呢？
void ListInsert_Dul(DuLinkList& L, int i, int e)
{
	//在带头结点的双向循环链表L中第i个位置之前插入元素e
	DuLinkList p;
	if( !(p = GetElemP_Dul(L, i)))//首先让指针p指向第i个位置,其实不太能理解为啥这个函数能让指针p指向第i个位置
		return ERROR;
	DuLinkList s = new DuLNode;
	s->data = e;
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return OK;
}
void ListDelete_Dul(DuLinkList& L, int i, int& e)
{
	//删除带头结点的双向循环链表L的第i个元素，并用e返回
	if (!(p = GetElemP_Dul(L, i)))
		return ERROR;
	e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return OK;
}

