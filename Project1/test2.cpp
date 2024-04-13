#include <iostream>
#include <stdio.h>
using namespace std;

#define MVNum 100 //��󶥵���
typedef int VerTexType;
typedef int OtherInfo;

// �߽��
struct ArcNode; // ��ǰ���� ArcNode �ṹ��

// ����ṹ��
typedef struct {
    VerTexType data;   //������Ϣ
    ArcNode* firstarc; //ָ���һ�������ö���ıߵ�ָ��
} VNode, AdjList[MVNum]; //AdjList��ʾ�ڽӱ�����

// �߽��
typedef struct ArcNode {
    VerTexType adjvex; //�ñ���ָ��Ķ����λ��?
    struct ArcNode* nextarc;  //ָ����һ���ߵ�ָ��
    OtherInfo info;    //�ͱ���ص���Ϣ
} ArcNode;

// �ڽӱ�����
typedef struct {
    AdjList vertics; //vertices--vertex�ĸ���
    int vexnum, arcnum; //ͼ�ĵ�ǰ�������ͻ���
} ALGraph;

// ͼG�в��Ҷ���u,�����򷵻ض�����е��±ꣻ���򷵻�-1
int LocateVex(ALGraph G, VerTexType u) {
    int i = 0;
    while (i < G.vexnum) {
        if (u == G.vertics[i].data)
            return i;
        else
            i++;
    }
    return -1; // δ�ҵ����㣬���� -1
}

/*
 * ���ڽӱ��ʾ������������
 */
int CreateUDG(ALGraph& G) {
    printf("�������ܶ��������ܱ�����\n");
    cin >> G.vexnum >> G.arcnum; //�����ܶ��������ܱ���
    cin.ignore(); // ������뻺����

    for (int i = 0; i < G.vexnum; ++i) { //������㣬�����ͷ����
        printf("�����붥��ֵ��\n");
        cin >> G.vertics[i].data; //���붥��ֵ
        G.vertics[i].firstarc = NULL; //��ʼ����ͷ����ָ����
    }

    for (int k = 0; k < G.arcnum; ++k) {
        int i, j;
        VerTexType v1, v2;
        printf("������һ�����������������㣺\n");
        cin >> v1 >> v2; //����һ������������������
        cin.ignore(); // ������뻺����

        i = LocateVex(G, v1);
        j = LocateVex(G, v2);

        ArcNode* p1 = new ArcNode; //����һ���µı߽��*p1
        p1->adjvex = j; //�ڽӵ����Ϊj
        p1->nextarc = G.vertics[i].firstarc;
        G.vertics[i].firstarc = p1; //���½��*p1���붥��Vi�ı߱�ͷ��

        //����������ʡ������
        ArcNode* p2 = new ArcNode; //������һ���ԳƵ��µı߽��*p2
        p2->adjvex = i; //�ڽӵ����Ϊi
        p2->nextarc = G.vertics[j].firstarc;
        G.vertics[j].firstarc = p2; //���½��*p2���붥��Vj�ı߱�ͷ��
    }

    return 0; // ����ִ�гɹ������� 0
}

int main(void) {
    ALGraph G; //�������ڽӱ��ʾ��ͼG
    CreateUDG(G);
    return 0;
}
