#include<iostream>
#define maxsize 200
using namespace std;
typedef struct Lnode {//声明定义一个新的链表
    int data;
    struct Lnode* next;
}Lnode, * Linklist;
int Initlist_L(Linklist &L)//初始化链表(带头结点的链表)
{
    L = (Lnode *)malloc(sizeof(Lnode));
    L->next = NULL;
    //如果链表的头指针指向的头结点的指针域为空，则链表为空，注意是指针域不是数据域，因为如果是数据域，头结点的数据域是有可能存放其他数据的
    return 0;
}
/*bool Initlist(Linklist& L)
{
    L = (Lnode*)malloc(sizeof(Lnode));//分配一个头节点，此头结点不存储数据。
    if (L = NULL)        //内存不足，分配失败
        return false;
    L->next = NULL;  //头节点之后暂时还没有节点
    return true;
}*/
int IsEmpty_Linklist(Linklist L)
{
    if (L->next == NULL)
        return 1;
    else
        return 0;
}
/*插入操作：在i位置插入e元素，此处是带头结点的单链表的情况*/
/*不应该直接插入结点吗，只有e元素和位置，应该申请一个结点然后再作插入的操作吧*/
void scanLinkList(Linklist L)
{
    int k = 0;//k元素用于计数
    Linklist p;
    p = L->next;//p指针指向L链表的第一个结点
    while (p)//如果p不为空，则循环遍历该单链表
    {
        cout << p->data << endl;//输出每个元素
        p = p->next;//p指针不断下移指向下一个结点
        k++;//k作为链表长度不断加一
    }
}
void InsertLinkList(Linklist& L, int i, int e)
{
    int k = 1;
    Linklist p = L;//申明一个头指针，指向第一个头结点,注意这里需要初始化头指针，如果不初始化则
    //申明一个新结点，并且新结点存入e元素的值(n作为指针指向该新结点)
    Linklist n = new Lnode;//错误点1：需要给新结点分配存储空间
    n->next = NULL;
    n->data = e;
    while (k != i)//首先循环链表，找到第i个结点
    {
        p = p->next;
        k++;
    }
    n->next = p->next;//执行一个断链的操作，将新结点插入链表中
    p->next = n;
}
int main() {
    Linklist L;
    Initlist_L(L);
    InsertLinkList(L, 1, 1);
    InsertLinkList(L, 2, 2);
    InsertLinkList(L, 3, 3);
    scanLinkList(L);
    return 0;
}