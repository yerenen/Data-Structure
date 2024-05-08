/*线性表*/
/*单链表——链式存储结构*/
#include<iostream>
#define OK
#define Status
using namespace std;
typedef struct Lnode{
	int data;
	struct Lnode *next;//我定义我自己（一个嵌套的定义，因为指针指向的也是一个结构体）
}Lnode,*LinkList;//Linklist为指向结构体Lnode的指针类型
/*
单链表的初始化（带头结点的单链表）——即构造一个如图的空表
算法步骤：
①生成新结点作头结点，用头指针指向头结点。
②将头结点的指针域置空。
*/
 void InitList_L(LinkList &L)
{
	L = new Lnode; //或L = (LinkList) malloc (sizeof (LNode));申明新结点的存储空间
	L->next = NULL;
}
/*
单链表的初始化（不带头结点的单链表）
L=NULL;
*/
 /*
 单链表的算法2——判断头结点指针域是否为空（判空）
 空表：链表中无元素，称为空链表（头结点和头指针仍然在）
 */
 int ListEmpty(LinkList L)
 {
	 if (L->next)
		 return 0;
	 else
		 return 1;
 }
 /*
 单链表的算法3——单链表的销毁，链表销毁后不存在（销毁所有结点，包括头结点，所以此处的单链表不作是否有头结点的区分，因为所有的结点都销毁）
 算法思路：从头指针开始，依次释放所有结点
 */
 int DestroyList_L(LinkList &L) //销毁单链表L
 {
	 Lnode* p;//或LinkList p;
	 while (L) {
		 p = L;
		 L = L -> next;//如何让指针指向下一个结点
		 delete p;
	 }
	 return 0;
 }
 /*
单链表的算法4——清空链表：链表仍存在，但链表中无元素，成为空链表（头指针和头结点依然存在）
算法思路：依次释放所有结点，并将头结点的指针域设置为空
*/
 int ClearList(LinkList& L) {//将L重置为空表
	 Lnode* p, *q;//或LinkList p,q;
	 p = L->next;
	 while (p) {//没到表尾，指针p存放当前结点，p不为空就反复执行
		 q = p->next; //q指向要删除结点的下一个结点
		 delete p;
		 p = q;
	 }
	 L->next = NULL;//头结点指针域为空（头结点一般不存放数据）
	 return 0;
 }
 /*
 单链表的算法5——求单链表的表长
 算法思路：从首元结点开始，遍历的同时计数所有结点
 */
 int Listlength_L(LinkList L) {//返回L中数据元素个数
	 LinkList p;
	 p = L->next;//p指向第一个结点（如果有头结点，那么此处p指向的就是首元结点）
	 int i = 0;
	 while (p)//遍历单链表，统计结点数
	 {
		 i++;
		 p = p->next;
	 }
	 return i;
 }
 /*
 单链表的算法6——找第i位置的元素
 算法思路：
 ①从第i个结点（L->next）顺链扫描，用指针p指向当前扫描到的结点，p初值p = L -> next。
 ②j作计数器，累计当前扫描过的结点数，j初值为1。
 ③当p指向扫描到的下一结点时，计数器j加1。
 ④当j == 1，p所指的结点就是要找的第i个结点。
 */
 /*自写：找第i位置的元素*/
 //错误点一：while循环条件写错了
 //错误点二：算法的健壮性不够，对于不合理输入情况的判断不够
 //错误点三：k的初始值需要注意，是否带头结点，情况不同
 int GetElem(LinkList L,int i,int &e) 
 {
	 int k = 1;
	 LinkList p;
	 p = L-> next;
	 while (i != k)//注意while循环的条件，如果符合条件就会一直执行循环内的语句
	 {
		 p = p-> next;
		 k++;
	 }
	 e = p->data;
	 return e;
 }
 /*题解*/
 int GetElem_L(LinkList L, int i, int& e)//获取线性表L中的某个数据元素的内容，通过变量e返回
 {
	 LinkList p = L->next;
	 int j = 1;//初始化
	 while (p && j < i) {
		 //向后扫描，直到p指向第i个元素或p为空（要求p不为空，且j还没找到i,没找到就一直找）
		 //while循环语句的语法：如果符合条件，则一直执行循环语句，不符合条件时跳出
		 //情况一：j = i,找到了e元素，跳出循环
		 //情况二：p = NULL, 没找到e元素，且链表遍历完了，跳出循环
		 p = p->next;
		 ++j;
	 }
	 //如果p为空或者j>1，则没找到e元素，故如此返回
	 if (!p || j > i)//第i个元素不存在
		 return 1;
	 e = p->data;//取第i个元素
	 return 0;
 }
 /*
 单链表的算法7——按值查找：根据指定元素获取该数据所在的位置
 算法思路：
 ①从第一个结点起，依次和e相比较
 ②如果找到一个其值与e相等的数据元素，则返回其在链表中的“位置”或地址
 ③如果查遍整个链表都没有找到其值与e相等的元素，则返回0或“NULL”
 */
 /*自写：找元素为i的数据在线性表所在的位置，有错误*/
 //错误点一：while循环条件写错了
 //错误点二：算法的健壮性不够，对于不合理输入情况的判断不够
 //错误点三：k的初始值需要注意，是否带头结点，情况不同
 int LocateElem(LinkList L, int e, int &k)
 {
	 k = 1;
	 LinkList p;
	 p = L->next;
	 while (p->data != e)
	 {
		 p = p->next;
		 k++;
	 }
	 return k;
 }
 /*老师解一*/
Lnode* LocateElem_L(LinkList L, int e)
 {
	 //在线性表L中查找值为e的数据元素
	 //找到，则返回L中值为e的数据元素的地址，查找失败则返回NULL
	 LinkList p = L->next;
	 while (p && p->data != e) {
		 //判断遍历整个链表过程中
		 // 情况一：找到元素e且链表中还有其他元素，则正常返回p
		 // 情况二：还没有找到元素e且p已经为空，返回的p为NULL，可由外部调用函数的人自行判断
		p = p->next;
	 }
	 return p;
 }
/*老师解二*/
int LocateElem_L2(LinkList L, int e)
{
	//在线性表L中查找值为e的数据元素
	//找到，则返回L中值为e的数据元素的地址，查找失败则返回NULL
	LinkList p = L->next;
	int j = 1;
	while (p && p->data != e) {
	//判断遍历整个链表过程中
	// 情况一：找到元素e且链表中还有其他元素，则正常返回p
	// 情况二：还没有找到元素e且p已经为空，返回的p为NULL
		p = p->next;
		j++;
	}
	//if语句判断p是否为空，
	// 情况一：不为空则返回j计数器，说明找到e了
	// 情况二：为空则返回0，说明没找到e
	if (p)
		return j;
	else
		return 0;
}
/*
单链表的算法8——插入操作：在第i个结点前插入值为e的新结点
算法思路：
①首先找到ai-1的存储位置p。
②生成一个数据域为e的新结点s。
③插入新结点：
--新结点的指针域指向结点ai
--结点ai-1的指针域指向新结点
*/ 
 int InsertList(LinkList& L, int i, int e)
 {
	 LinkList p = L;//头指针
	 int j = 0;
	 while (p && j < i - 1)//第i-1个结点的地址存放在前一个结点的指针域中，所以此处为j<i-1
	 {
		 p = p->next;
		 ++j;//寻找第i-1个结点，p指向i-1个结点
		 if (!p || j > i - 1)//i大于表长+1或者小于1，插入位置非法
			 return 0;
	 }
	 LinkList s = new Lnode;//生成新结点s，将结点s的数据域置为e
	 s->data = e;//将结点s插入L中
	 s->next = p->next;
	 p->next = s;
 }
 /*
 单链表的算法9——建立单链表：头插法——元素插入在链表头部，也叫前插法
 算法思路：
 ①从一个空表开始，重复读入数据。
 ②生成新结点，将读入数据存放到新结点的数据域中。
 ③从最后一个结点开始，依次将各结点插入到链表的前端
 */
 void CreateList_H(LinkList& L, int n)
 {
	 L = new Lnode;
	 L->next = NULL;//先建立一个带头结点的单链表
	 for (int i = n;i > 0;--i)
	 {
		LinkList p = new Lnode;//生成新结点p=(Lnode*)malloc(sizeof(Lnode));
		cin >> p->data;//输入元素值scanf(&p->data);
		p->next = L->next;//插入到表头
		L->next= p;
	 }
 }
 /*
  单链表的算法9——建立单链表：尾插法——元素插入在链表尾部，也叫后插法
  算法思路：
  ①从一个空表L开始，将新结点逐个插入到链表的尾部，尾指针r指向链表的尾结点。
  ②初始时，r同L均指向头结点。每读入一个数据元素则申请一个新结点，将新结点插入到尾节点后，r指向新结点。
  ③从最后一个结点开始，依次将各结点插入到链表的前端
  */
 void CreateList_R(LinkList& L, int n)
 {
	 L = new Lnode;
	 L->next = NULL;
	 LinkList r = L;//尾指针r指向头结点
	 for (int i = 0;i < n;++i)
	 {
		 LinkList p = new Lnode;
		 cin >> p->data;//生成新结点，输入元素值
		 p->next = NULL;
		 r->next = p;//插入到表尾
		 r = p;//r指向新的尾结点
	 }
 }
 /*
单链表的算法10——删除操作：在第i个结点前删除值为e的新结点(带头结点吗？头结点算不算第一个结点)
算法思路：
①首先找到ai-1的存储位置p，保存要删除的ai的值。
②另p->next指向ai+1。
③释放结点ai的空间。
*/
 int deleteList(LinkList& L, int i, int &e)
 {
	 LinkList p = L;
	 int j = 0;
	 while (p->next && j < i - 1)//这里的条件是什么意思？寻找第i个结点，并令p指向其前驱
	 {
		 p = p->next;
		 ++j;
	 }
	 if (!(p->next) || j > i - 1)//删除位置不合理
		 //位置不合理的两种情况：
		 //①删除位置小于0,j > i-1
		 //②链表为空p->next为空
		 return 0;
	 LinkList q = p->next;//临时保存被删结点的地址以备释放
	 p->next = q->next;//改变删除结点前驱结点的指针域
	 e = q->data;//保存删除结点的数据域
	 delete q;//释放被删除结点的空间
	 return 0;
 }
 void scanLinkList(LinkList L)
 {
	 int k = 0;//k元素用于计数
	 LinkList p;
	 p = L->next;//p指针指向L链表的第一个结点
	 while (p)//如果p不为空，则循环遍历该单链表
	 {
		 cout << p->data << endl;//输出每个元素
		 p = p->next;//p指针不断下移指向下一个结点
		 k++;//k作为链表长度不断加一
	 }
 }
int main()
{
	int e;
	int k;
	LinkList L;//定义链表
	Lnode *p;//定义结点指针p
	//LinkList p;//定义结点指针p(和上边一样)
	InitList_L(L);//初始化
	ClearList(L);//清空链表
	//CreateList_H(L, 5);//头插法
	//CreateList_R(L, 5);//尾插法
	scanLinkList(L);
	InsertList(L, 1, 1);//插入
	InsertList(L, 2, 2);
	InsertList(L, 3, 3);
	InsertList(L, 4, 4);
	InsertList(L, 5, 5);
	scanLinkList(L);//遍历
	//GetElem_L(L, 2, e);//按位查找
	GetElem(L, 3, e);
	cout<<"线性表L的第三个元素为：" <<e<<endl;
	//cout << "线性表L的元素为3的数据所在位置为：" <<LocateElem_L(L, 3) <<endl;//按值查找
	cout << "线性表L的元素为3的数据所在位置为：" << LocateElem(L, 3, k) << endl;
	cout << "线性表L的元素为9的数据所在位置为：" << LocateElem_L2(L, 9) << endl;
	deleteList(L, 1, e);//删除
	cout << "被删除元素为：" << e<<endl;
	scanLinkList(L);
}
