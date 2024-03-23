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
    int k = 0;//k元素用于计数
    Linklist p = L;
    p = L->next;//p指针指向L链表的第一个结点
    while (p)
    {
        //如果p不为空，则循环遍历该单链表
        cout << p->data << endl;
        p = p->next;//p指针不断下移指向下一个结点
        k++;//k作为链表长度不断加一
        //输出每个元素
    }
}
void InsertLinkList(Linklist& L, int i, int e)
{
    int k = 1;
    Linklist p = L;
    //申明一个头指针，指向第一个头结点
    //申明一个新结点，并且新结点存入e元素的值(n作为指针指向该新结点)
    Linklist n = new Lnode;
    //错误点1：需要给新结点分配存储空间
    n->next = NULL;
    n->data = e;
    while (k != i)
    {
        //首先循环链表，找到第i个结点
        p = p->next;
        k++;
    }
    n->next = p->next;
    //执行一个断链的操作，将新结点插入链表中
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