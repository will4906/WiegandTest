#include "stm32f10x.h"
#include "delay.h"
#include "TotalTimer.h"
#include "led.h"
#include "Uart.h"
#include "Exti.h"
#include "wiegand.h"
#include "UnpackWiegand.h"
#include "UartCom2.h"

int main()
{
	u8 data[] = "hello";
	u8 hidLow = 0;
	u16 pid = 0;
	delay_init();
	//定时器时间设置为10ms
	InitTimerCon();
	InitUartCon();
	LED_Init();
	InitExtiCon();
	InitWiegandCon();
	
	while(1)
	{
		if(ReadWiegandResult(&hidLow, &pid))
		{
			printf2("hidLow = %d, pid = %d", hidLow, pid);
		}
		/*EnableAllLed();
		delay_ms(1000);
		if(ReadUartData(UART_PORT_COM2,data))
		{
			SendUartData(UART_PORT_COM2,data,5);
		}
		DisableAllLed();
		delay_ms(500);*/
	}
}
