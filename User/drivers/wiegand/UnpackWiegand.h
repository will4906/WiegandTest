#ifndef _UNPACK_WIEGAND_H_
#define _UNPACK_WIEGAND_H_

#include "sqlist.h"


#define WIEGAND_LENGTH 26

void InitWiegandProtocol(void);
unsigned char UnpackWiegandData(unsigned char data);
void CheckWiegandDataDelay(void);
unsigned char ReadWiegandResult(unsigned char *hidLow, unsigned short *pid);
unsigned char GetDataInSqlist(SqList sql, int index, ElemType *data);















#endif


