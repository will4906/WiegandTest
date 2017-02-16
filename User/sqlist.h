#ifndef _SQLIST_H_
#define _SQLIST_H_

#define ERR 0
#define CORRECT 1

#define INIT_SIZE 50
typedef unsigned char ElemType;

typedef struct  
{
	ElemType *elem;
	int size;
	int length;
}SqList;

unsigned char InitSqList(SqList *sql);
void RemoveAllInSqllist(SqList *sql);
unsigned char SetSqList(SqList *sql, int index, ElemType data);
int GetTheLengthOfSqlist(SqList sql);
unsigned char AddDataInSqlist(SqList *sql, ElemType data);












#endif



