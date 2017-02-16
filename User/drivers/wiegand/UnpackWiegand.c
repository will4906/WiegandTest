#include "UnpackWiegand.h"
#include "UartCom2.h"

static SqList wiegandList;
static signed char delayTimeFlag = 0;
static unsigned char clearFlag = 0;
/*********************************************************************
* Function: Initialize the wiegand protocol stack
* Param: 		void
* Return: 	void
**********************************************************************/
void InitWiegandProtocol(void)
{
	InitSqList(&wiegandList);
}

/*********************************************************************
* Function: Unpack the wiegand data
* Param: 		void
* Return: 	void
**********************************************************************/
unsigned char UnpackWiegandData(unsigned char data)
{
	unsigned char flag = AddDataInSqlist(&wiegandList, data);
	int len = GetTheLengthOfSqlist(wiegandList);
	if(len == WIEGAND_LENGTH){
		delayTimeFlag = -1;
	}else{
		delayTimeFlag = 2;
	}
	return flag;
}

/*********************************************************************
* Function: 防止数据出错计时函数，请将此函数置于大于1ms定时器中
* Param: 		void
* Return: 	void
**********************************************************************/
void CheckWiegandDataDelay(void)
{
	if(delayTimeFlag > 0){
		delayTimeFlag --;
	}
	if(delayTimeFlag == 0){
		clearFlag = 1;
	}
}

/*********************************************************************
* Function: wiegand协议周期性检查函数，请置于主循环
* Param: 		void
* Return: 	void
**********************************************************************/
unsigned char ReadWiegandResult(unsigned char *hidLow, unsigned short *pid)
{
	unsigned char i = 0;
	unsigned char data = 0;
	
	unsigned char first = 0;
	unsigned char last = 0;
	unsigned char tmpHidLow = 0;
	unsigned short tmpPid = 0;
	
	unsigned char lowHidOneSum = 0;
	unsigned char pidOneSum = 0;
	if(delayTimeFlag == -1){
		for(i = 0; i < WIEGAND_LENGTH; i++){
			if(GetDataInSqlist(wiegandList, i, &data))
			{
				if(i == 0){
					first = data;
				}
				if(i == WIEGAND_LENGTH - 1){
					last = data;
				}
				if(i > 0 && i < 9)
				{
					tmpHidLow |= data << (i - 1);
				}
				if(i >= 9 && i < 25)
				{
					tmpPid |= data << (i - 9);
				}
				if(i > 0 && i < 13)
				{
					if(data == 1){
						lowHidOneSum ++;
					}
				}
				if(i >= 13 && i < 25){
					if(data == 1){
						pidOneSum ++;
					}
				}
			}
			else
			{
				return 0;
			}
		}

		if((lowHidOneSum + first) % 2 == 0 && (pidOneSum + last) % 2 == 1){
			*hidLow = tmpHidLow;
			*pid = tmpPid;
			RemoveAllInSqllist(&wiegandList);
		}else{
			RemoveAllInSqllist(&wiegandList);
			return 0;
		}
		RemoveAllInSqllist(&wiegandList);
		return 1;
	}
	if(clearFlag == 1){
		RemoveAllInSqllist(&wiegandList);
		clearFlag = 0;
	}
	return 0;
}



