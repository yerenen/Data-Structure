#include<iostream>
#define maxsize 200
using namespace std;
typedef struct Lnode {//��������һ���µ�����
    int data;
    struct Lnode* next;
}Lnode, * Linklist;
int Initlist_L(Linklist &L)//��ʼ������(��ͷ��������)
{
    L = (Lnode *)malloc(sizeof(Lnode));
    L->next = NULL;
    //��������ͷָ��ָ���ͷ����ָ����Ϊ�գ�������Ϊ�գ�ע����ָ��������������Ϊ�����������ͷ�������������п��ܴ���������ݵ�
    return 0;
}
/*bool Initlist(Linklist& L)
{
    L = (Lnode*)malloc(sizeof(Lnode));//����һ��ͷ�ڵ㣬��ͷ��㲻�洢���ݡ�
    if (L = NULL)        //�ڴ治�㣬����ʧ��
        return false;
    L->next = NULL;  //ͷ�ڵ�֮����ʱ��û�нڵ�
    return true;
}*/
int IsEmpty_Linklist(Linklist L)
{
    if (L->next == NULL)
        return 1;
    else
        return 0;
}
/*�����������iλ�ò���eԪ�أ��˴��Ǵ�ͷ���ĵ���������*/
/*��Ӧ��ֱ�Ӳ�������ֻ��eԪ�غ�λ�ã�Ӧ������һ�����Ȼ����������Ĳ�����*/
void scanLinkList(Linklist L)
{
    int k = 0;//kԪ�����ڼ���
    Linklist p;
    p = L->next;//pָ��ָ��L����ĵ�һ�����
    while (p)//���p��Ϊ�գ���ѭ�������õ�����
    {
        cout << p->data << endl;//���ÿ��Ԫ��
        p = p->next;//pָ�벻������ָ����һ�����
        k++;//k��Ϊ�����Ȳ��ϼ�һ
    }
}
void InsertLinkList(Linklist& L, int i, int e)
{
    int k = 1;
    Linklist p = L;//����һ��ͷָ�룬ָ���һ��ͷ���,ע��������Ҫ��ʼ��ͷָ�룬�������ʼ����
    //����һ���½�㣬�����½�����eԪ�ص�ֵ(n��Ϊָ��ָ����½��)
    Linklist n = new Lnode;//�����1����Ҫ���½�����洢�ռ�
    n->next = NULL;
    n->data = e;
    while (k != i)//����ѭ�������ҵ���i�����
    {
        p = p->next;
        k++;
    }
    n->next = p->next;//ִ��һ�������Ĳ��������½�����������
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