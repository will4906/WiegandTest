/*************************************************************************************
* FileName: Exti.c
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
#include "Exti.h"
#include "Uart.h"
#include "delay.h"
#include "wiegand.h"
#include "UartCom2.h"
/*********************************************************************
* Static Function Declaration
**********************************************************************/
static void InitExti(void);
static void InitNvic(void);
static void InitGpio(void);


/*********************************************************************
* Function: Initialize all Exti config
* Param: 		void
* Return: 	void
**********************************************************************/
void InitExtiCon(void)
{
	InitGpio();
	InitExti();
	InitNvic();
}

/*********************************************************************
* Function: Initialize the Gpio config
* Param: 		void
* Return: 	void
**********************************************************************/
static void InitGpio(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource1);
}

/*********************************************************************
* Function: Initialize the exti config
* Param: 		void
* Return: 	void
**********************************************************************/
static void InitExti(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

/*********************************************************************
* Function: Initialize the Nvic config
* Param: 		void
* Return: 	void
**********************************************************************/
static void InitNvic(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*********************************************************************
* Function: The interrupt handler function of the exti0
* Param: 		void
* Return: 	void
**********************************************************************/
void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		AnswerDataZeroExti();
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

/*********************************************************************
* Function: The interrupt handler function of the exti1
* Param: 		void
* Return: 	void
**********************************************************************/
void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		AnswerDataOneExti();
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}


 
 
