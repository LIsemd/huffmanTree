#include <iostream>
#include <fstream>
#include<string>
using namespace std;
#define MAXSIZE 100
#define OK 1 
#define ERROR 0
typedef struct{
	int weigth;
	int parent,lchrld,rchrld;
}HTNode;

typedef struct{
	HTNode *node;
	int n,m;
	int r;
}HuffmanTree;

typedef struct{
	int num;	//出现次数 
	char ch;	//字符 
}ElemType;

typedef struct{
	ElemType data[MAXSIZE];
	int length;
}Number;

typedef struct{
	char data;
	string code;
}ElemType_2;

typedef struct{
	ElemType_2 *chars;
	int length;
}Sqlist;


