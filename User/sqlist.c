#include "sqlist.h"
#include <stdlib.h>

/*********************************************************************
* Function: Initialize the sequense list
* Param: 		SqList
* Return: 	0:err, 1:correct
**********************************************************************/
unsigned char InitSqList(SqList *sql)
{
	sql->elem = (ElemType *)calloc(INIT_SIZE,sizeof(ElemType));
	if(sql->elem == NULL)
	{
		return ERR;
	}
	else
	{
		sql->size = INIT_SIZE;
	}
	sql->length = 0;
	return CORRECT;
}

/*********************************************************************
* Function: Clear all the data in the sqlist
* Param: 		SqList
* Return: 	void
**********************************************************************/
void RemoveAllInSqllist(SqList *sql)
{
	//free(sql->elem);
	sql->length = 0;
	//sql->size = 0;
	//InitSqList(sql);
}

/*********************************************************************
* Function: Set the data at the index of the sqlist
* Param: 		SqList,index,data
* Return: 	0:err, 1:correct
**********************************************************************/
unsigned char SetSqList(SqList *sql, int index, ElemType data)
{
	if(index >= sql->length || index < 0)
	{
		return ERR;
	}
	sql->elem[index] = data;
	return CORRECT;
}

/*********************************************************************
* Function: Get The Length Of Sqlist
* Param: 		SqList
* Return: 	the length of sqlist
**********************************************************************/
int GetTheLengthOfSqlist(SqList sql)
{
	return sql.length;
}

/*********************************************************************
* Function: Add data in Sqlist
* Param: 		SqList,data
* Return: 	0:err, 1:correct	
**********************************************************************/
unsigned char AddDataInSqlist(SqList *sql, ElemType data)
{
	if(sql->length >= sql->size)
	{
		sql->elem = (ElemType*)realloc(sql->elem, (sql->size + 1) * sizeof(ElemType));
		if(sql->elem == NULL)
		{
			return ERR;
		}
	}
	sql->elem[sql->length++] = data;
	return CORRECT;
}

/*********************************************************************
* Function: Get data in Sqlist
* Param: 		SqList,index,data
* Return: 	0:err, 1:correct	
**********************************************************************/
unsigned char GetDataInSqlist(SqList sql, int index, ElemType *data)
{
	if(index < sql.length)
	{
		*data = sql.elem[index];
		return 1;
	}
	else
	{
		return 0;
	}
}



