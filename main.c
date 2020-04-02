/*
 * autosar_dio_atmega32.c
 *
 * Created: 01/04/2020 12:23:04 م
 * Author : Ali makhlouf
 */ 

#include "dio.h"
#include "micro_config.h"
#include "Port.h"
#include "Det.h"
#include "uart_api.h"

int main(void)
{
	Port_Init(&port_config);
	
    /* Replace with your application code */
    while (1) 
    {
		Dio_FlipChannel(BUZZER);
		Dio_WriteChannel(LED, STD_HIGH);
		_delay_ms(1000);
		Dio_FlipChannel(BUZZER);
		Dio_WriteChannel(LED, STD_LOW);
		_delay_ms(1000);	
		
		if (Dio_ReadChannel(SW) == STD_HIGH)
		{
			Dio_WriteChannel(LED1, STD_HIGH);
		}
		else
		{
			Dio_WriteChannel(LED1, STD_LOW);
		}
    }
	
}

