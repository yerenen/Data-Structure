/*线性表*/
/*循环链表——链式存储结构*/
#include<iostream>
#define maxsize 200
using namespace std;
typedef struct Lnode {//声明定义一个新的链表
    int data;
    struct Lnode* next;
}Lnode, * Linklist;
Linklist Connect(Linklist Ta, Linklist Tb)//带尾指针循环链表的合并
{
    Linklist p;
    p = Ta->next;//1、p存表头结点
    Ta->next = Tb->next->next;//2、Tb表头连结Ta表尾
    delete Tb->next;//3、释放Tb表头结点
    Tb->next = p;//4、修改指针
    return Tb;
}