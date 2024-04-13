/*线性表*/
/*串——内容受限的线性表*/
/*
1、串——
由零个或多个任意字符组成的有限序列。
S="a1a2...an"(n>=0)。
串名S，串值n，串长n。若n=0，则称为空串。*/
/*
2、串的定义——
子串：一个串中任意个连续字符组成的子序列（含空串）称为该串的子串。
真子串：不包含自身的所有子串。
主串：包含子串的串相应地称为主串。
字符位置：字符在序列中的序号为该字符在串中的位置。
子串位置：子串第一个字符在主串中的位置。
空格串：由一个或多个空格组成的串，与空串不同。
串相等：当且仅当两个串的长度相等并且各个对应位置上的字符都相同时，这两个串才是相等的。*/
/*
3、案例引入——
案例4.1：病毒感染检测*/
/*
4、串的类型定义、存储结构及运算
ADT String{
数据对象:D={ai|ai∈CharacterSet,i=1,2,...,n,n>=0}
数据关系:R1={<ai-1,ai>|ai-1,ai∈D,i=1,2,...,n}
基本操作:
（1）StrAssign(&T,chars)//串赋值
（2）StrComare(S,T)//串比较
（3）StrLength(S)//求串长
（4）Concat(&T,S1,S2)//串连结
（5）SubString(&Sub,S,pos,len)//求子串
（6）StrCopy(&T,S)//串拷贝
（7）StrEmpty(S)//串判空
（8）ClearString(&S)//清空串
（9）Index(S,T,pos)//子串的位置❤（KMP算法）
（10）Replace(&S,T,V)//串替换
（11）StrInsert(&S,pos,T)//子串插入
（12）StrDelete(&S,pos,len)//子串删除
（13）DestroyString(&S)//串销毁
}ADT String
*/
/*顺序串——顺序存储结构*/
#include<iostream>
#include<stdio.h>
#define MAXLEN 255
using namespace std;
typedef struct {
	char ch[MAXLEN + 1];//存储串的一维数组，数据元素从0-255（一共256个元素）
	int length;//串的当前长度
}SString;
/*串的模式匹配算法——BF算法*/
/*Brute-Force算法简称为BF算法，亦称为简单匹配算法。采用穷举法的思路。算法的思路是从S的每一个字符开始依次与T的字符进行匹配。*/
//Index(S,T,pos)
//将主串的第pos个字符和模式串的第一个字符相比较
//若相等，继续逐个比较后续字符
//若不等，从主串的下一字符起，重新与模式串的第一个字符相比较
//直到主串的一个连续子串字符序列与模式串相等。返回值为S中与T匹配的子序列第一个字符的序号，即匹配成功。否则，匹配失败，返回值0
int Index_BF(SString S, SString T)
{
	int i = 0, j = 0;
	while (i <= S.length && j <= T.length) {
		if (S.ch[i] == T.ch[j])//主串和子串依次匹配下一个字符
		{
			++i;
			++j;
		}
		else {//主串、子串指针回溯重新开始下一次匹配
			i = i - j + 2;//回溯位置是个难点
			j = 1;
		}
	}
		if (j > T.length)
			return i - T.length;//返回匹配的第一个字符的下标
		else
			return 0;//模式匹配不成功          
}

/*KMP算法*/
/*通过计算返回子串T的next数组*/
void get_next(SString T, int* next)
{
	int i, k;
	i = 1;
	k = 0;
	next[1] = 0;
	while (i < T.length)//此处T[0]表示串T的长度
	{
		if (k == 0 || T.ch[i] == T.ch[k])
		{
			++i;
			++k;
			next[i] = k;
		}
		else
		{
			k = next[k];//若字符不相同，则k值回溯
		}
	}
}
/*改良过后的KMP算法*/
/*通过计算返回子串T的nextval数组*/
void get_nextval(SString T, int* nextval)
{
	int i, k;
	i = 1;
	k = 0;
	nextval[1] = 0;
	while (i < T.length)//T[i]表示后缀的单个字符，T[k]表示前缀的单个字符
	{
		if (k == 0 || T.ch[i] == T.ch[k])
		{
			++i;
			++k;
			if (T.ch[i] != T.ch[k])//若当前字符与前缀字符不同
				nextval[i] = k;//则当前的j为nextval在i位置的值
			else
				nextval[i] = nextval[k];//如果与前缀字符相同，则将前缀字符的nextval值赋值给nextval在i位置的值
		}
		else
			k = nextval[k];//若字符不相同，则k值回溯
	}
}
/*返回子串T在主串S中第pos个字符之后的位置，若不存在，则函数返回值为0*/
/*T非空，1<=pos<=StrLength(S)*/
int Index_KMP1(SString S, SString T, int pos)
{
	int i = pos;//i用于主串S中当前位置下标值，从pos位置开始匹配
	int j = 1;//j用于子串T中当前位置下标值
	int next[255];//定义一串next数组
	get_next(T, next);//对串T做分析，得到next数组
	while (i <= S.length && j <= T.length)//当i小于S的长度且j小于T长度时，循环继续
	{
		if (j == 0 || S.ch[i] == T.ch[j])//两字母相等且继续，与朴素算法相比 增加了j=0的判断
		{
			++i;
			++j;
		}
		else//指针后退重新开始匹配
		{
			j = next[j];//j退回至合适位置，i值不变
		}
	}
	if (j > T.length)
		return i - T.length;
	else
		return 0;
}
/*KMP的改良算法*/
int Index_KMP2(SString S, SString T, int pos)
{
	int i = pos;//i用于主串S中当前位置下标值，从pos位置开始匹配
	int j = 1;//j用于子串T中当前位置下标值
	int next[255];//定义一串next数组
	get_nextval(T, next);//对串T做分析，得到next数组
	while (i <= S.length && j <= T.length)//当i小于S的长度且j小于T长度时，循环继续
	{
		if (j == 0 || S.ch[i] == T.ch[j])//两字母相等且继续，与朴素算法相比 增加了j=0的判断
		{
			++i;
			++j;
		}
		else//指针后退重新开始匹配
		{
			j = next[j];//j退回至合适位置，i值不变
		}
	}
	if (j > T.length)
		return i - T.length;
	else
		return 0;
}
void Init_Str(SString& S)
{
	for (int i = 0;i < S.length;i++)
	{
		cin >> S.ch[i];
	}
}
int main(void)
{
	int pos=1;
	SString S;
	printf("请输入所需要创建的S字符串长度：");
	cin >> S.length;
	printf("请输入S字符串所需要的字符串：");
	Init_Str(S);
	SString T;
	printf("请输入所需要创建的T字符串长度：");
	cin >> T.length;
	printf("请输入T字符串所需要的字符串：");
	Init_Str(T);
	Index_KMP1(S, T, pos);
	cout<<"KMP算法："<<Index_KMP1(S, T, pos)<<endl;
	Index_KMP2(S, T, pos);
	cout << "KMP的改良算法：" << Index_KMP2(S, T, pos)<<endl;
	Index_BF(S, T);
	cout << "暴力破解的算法：" << Index_BF(S,T) << endl;
}
