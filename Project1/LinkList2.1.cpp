#include<iostream>
#define maxsize 200
using namespace std;
typedef struct Lnode {
    int data;
    struct Lnode* next;
}Lnode, * Linklist;
bool Initlist(Linklist& L)
{
    L = (Linklist)malloc(sizeof(Lnode));
    if (L == NULL) 
        return false;
    else
    {
        L->next = NULL;
        return true;
    }
}
int IsEmpty_Linklist(Linklist L)
{
    if (L->next == NULL)
        return 1;
    else
        return 0;
}
void scanLinkList(Linklist L)
{
    int k = 0;//kԪ�����ڼ���
    Linklist p = L;
    p = L->next;//pָ��ָ��L����ĵ�һ�����
    while (p)
    {
        //���p��Ϊ�գ���ѭ�������õ�����
        cout << p->data << endl;
        p = p->next;//pָ�벻������ָ����һ�����
        k++;//k��Ϊ�����Ȳ��ϼ�һ
        //���ÿ��Ԫ��
    }
}
void InsertLinkList(Linklist& L, int i, int e)
{
    int k = 1;
    Linklist p = L;
    //����һ��ͷָ�룬ָ���һ��ͷ���
    //����һ���½�㣬�����½�����eԪ�ص�ֵ(n��Ϊָ��ָ����½��)
    Linklist n = new Lnode;
    //�����1����Ҫ���½�����洢�ռ�
    n->next = NULL;
    n->data = e;
    while (k != i)
    {
        //����ѭ�������ҵ���i�����
        p = p->next;
        k++;
    }
    n->next = p->next;
    //ִ��һ�������Ĳ��������½�����������
    p->next = n;
}
int main() {
    Linklist L;
    Initlist(L);
    InsertLinkList(L, 1, 1);
    InsertLinkList(L, 2, 2);
    InsertLinkList(L, 3, 3);
    InsertLinkList(L, 4, 4);
    InsertLinkList(L, 5, 5);
    InsertLinkList(L, 6, 6);
    InsertLinkList(L, 7, 7);
    InsertLinkList(L, 8, 8);
    scanLinkList(L);
}