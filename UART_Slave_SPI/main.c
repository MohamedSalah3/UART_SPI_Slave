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
	uint8_t data_sent='M';
	uint8_t flag=0;
	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);
	gpioPinDirection(GPIOB,BIT3,OUTPUT);
	timer2Init(T2_NORMAL_MODE,T2_OC2_DIS,T2_PRESCALER_NO,0,0,0,T2_POLLING);
	Uart_Init(Baud9600,OneStopBit,NoParity,EightBits,ASynchronous);
	SPI_Init();
	while(1)
		{		
			
			UartTransmitPooling('B');
			while (pushButtonGetStatus(BTN_0)==Released);
			UartTransmitPooling('M');		
				while (pushButtonGetStatus(BTN_0)==Pressed)
				{
					timer2Start();
					timer2DelayMs(50);
						data_sent =SPI_Receive();
				UartTransmitPooling('S');
					UartTransmitPooling(data_sent);
				}
				
					
			
    }



}