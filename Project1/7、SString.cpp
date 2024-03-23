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
（9）Index(S,T,pos)//子串的位置❤
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
	char ch[MAXLEN + 1];//存储串的一维数组
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
	int i = 1, j = 1;
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
		if (j > T.length)
			return i - T.length;//返回匹配的第一个字符的下标
		else
			return 0;//模式匹配不成功          
	}
}
int Index_KMP(SString S, SString T, int pos)
{
	i = pos, j = 1;
	while (i < S.length && j < T.length) {
		if (j == 0 || S.ch[i] == T.ch[j])
		{
			i++;
			j++;
		}
		else
	}
	if (j > T.length)
		return i - T.length;/*匹配成功*/
	else
		return 0;/*返回不匹配标志*/
}