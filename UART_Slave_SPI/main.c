/*
 * UART.c
 *
 * Created: 10/02/2020 08:00:40 م
 *  Author: mo
 */
#include "pushButtonConfig.h"
#include "pushButton.h"
#include "led.h"
#include "ledConfig.h"
#include "timers.h"
#include "uart.h"
#include "uartconfig.h"
#include "SPI.h"
#include "SPI_Config.h"
int main(void)
{
	uint8_t data_sent='A';
	uint8_t flag=0;
	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);
	gpioPinDirection(GPIOB,BIT3,OUTPUT);
	Led_Init(LED_0);
	Led_Init(LED_1);
	timer2Init(T2_NORMAL_MODE,T2_OC2_DIS,T2_PRESCALER_NO,0,0,0,T2_POLLING);
	Uart_Init(Baud9600,OneStopBit,NoParity,EightBits,ASynchronous);
	Led_On(LED_0);
	Led_On(LED_1);
    SPI_Init();
	while(1)
		{
				while(flag == 1){
			data_sent =SPI_Receive();
			UartTransmitPooling((data_sent++));
									}			
			if (pushButtonGetStatus(BTN_0))
				{
						flag=1;
				}
				if (pushButtonGetStatus(BTN_1))
				{
					flag=0;
				UartTransmitPooling(data_sent+'0');			
				}
				/*
				data_sent =SPI_Receive();
			UartTransmitPooling(data_sent);
		*/
				timer2Start();
				timer2DelayMs(1000);

    }

}
