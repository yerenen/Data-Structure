/*���Ա�*/
/*ѭ����������ʽ�洢�ṹ*/
#include<iostream>
#define maxsize 200
using namespace std;
typedef struct Lnode {//��������һ���µ�����
    int data;
    struct Lnode* next;
}Lnode, * Linklist;
Linklist Connect(Linklist Ta, Linklist Tb)//��βָ��ѭ������ĺϲ�
{
    Linklist p;
    p = Ta->next;//1��p���ͷ���
    Ta->next = Tb->next->next;//2��Tb��ͷ����Ta��β
    delete Tb->next;//3���ͷ�Tb��ͷ���
    Tb->next = p;//4���޸�ָ��
    return Tb;
}