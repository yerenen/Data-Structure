/*���Ա�*/
/*˫����������ʽ�洢�ṹ*/
/*��Ҫ���ִ�����ͷ�����*/
#include<iostream>
#define ERROR
#define OK
using namespace std;
typedef struct DuLNode {
	int data;
	struct DuLNode *prior, *next;
}DuLNode,*DuLinkList;//�������������ָ�����ָ���أ�
void ListInsert_Dul(DuLinkList& L, int i, int e)
{
	//�ڴ�ͷ����˫��ѭ������L�е�i��λ��֮ǰ����Ԫ��e
	DuLinkList p;
	if( !(p = GetElemP_Dul(L, i)))//������ָ��pָ���i��λ��,��ʵ��̫�����Ϊɶ�����������ָ��pָ���i��λ��
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
	//ɾ����ͷ����˫��ѭ������L�ĵ�i��Ԫ�أ�����e����
	if (!(p = GetElemP_Dul(L, i)))
		return ERROR;
	e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return OK;
}

