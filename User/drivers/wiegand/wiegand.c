/*************************************************************************************
* FileName: wiegand.c
* Author:		will4906
* Email:		553105821@qq.com
* Date:			2017/02/14
* Apache license:
	Copyright 2017 will4906

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
**************************************************************************************/
#include "wiegand.h"
#include "stm32f10x.h"
#include "sqlist.h"
#include "Uart.h"
#include "delay.h"
#include "sqlist.h"
#include "UnpackWiegand.h"

static void InitWiegandGpio(void);
static u8 checkForInputBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
/*********************************************************************
* Function: Initialize the wiegand config
* Param: 		void
* Return: 	void
**********************************************************************/
void InitWiegandCon(void)
{
	InitWiegandGpio();
	InitWiegandProtocol();
}

/*********************************************************************
* Function: Initialize the wiegand Gpios
* Param: 		void
* Return: 	void
**********************************************************************/
static void InitWiegandGpio(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 // 上拉输入
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/*********************************************************************
* Function: 响应data0中断
* Param: 		void
* Return: 	void
**********************************************************************/
void AnswerDataZeroExti(void)
{
	if(checkForInputBit(GPIOD,GPIO_Pin_0))
	{
		UnpackWiegandData(0);
	}
}

/*********************************************************************
* Function: 响应data0中断
* Param: 		void
* Return: 	void
**********************************************************************/
void AnswerDataOneExti(void)
{
	if(checkForInputBit(GPIOD,GPIO_Pin_1))
	{
		UnpackWiegandData(1);
	}
}

/*********************************************************************
* Function: 防止高电平突然变低电平影响中断
* Param: 		GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin
* Return: 	是否为正确的中断
**********************************************************************/
static u8 checkForInputBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	u8 i;
	for(i = 0; i < 5; i ++)
	{
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 0)  //计算脉宽
		{
			delay_us(10);									//不知道延时会不会和lwip冲突，待测试
		}
		else
		{
			break;
		}
	}
	return i == 5;
}
 

















