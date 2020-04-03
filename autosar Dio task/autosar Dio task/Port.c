/*
 * Port.c
 *
 * Created: 01/04/2020 12:53:16 م
 *  Author: Ali makhlouf
 */ 


#include "Port.h"


//NOTE: this module's functions are stubbing function (do not follow autosar standard)


// the address of the first PIN register(which is PINA)
#define PIN_REG_BASE (volatile uint8 *)(0x39)
// the address of the first  DDR register(which is DDRA)
#define DDR_REG_BASE (volatile uint8 *)(0x3A)
// the address of the first  PORT register(which is PORTA)
#define PORT_REG_BASE (volatile uint8 *)(0x3B)

//it chooses the port registers based on the offset whether A(offset 0) - B(offset 1) - C(offset 3)
//D(offset 4).
#define PORT_OFFSET(n) (((n) * -3))

#define PORT_CH_DATA ConfigPtr->ChsDataStates[i]->ch_data


//for now(as we have only studied the DIO module) this function is responsible for setting the 
//direction register of atmega32 (DDR register) of the corresponding channels selected
void Port_Init(const Port_ConfigType * ConfigPtr)
{
	
	for (uint8 i = 0; i < PINS_NUM; i++ )
	{
		
		if (ConfigPtr->ChsDataStates[i]->channel_state != PORT_PULLUP)
		{
			//put this direction in the specific pin_no in the specific port
			ASSIGN_BIT(*(DDR_REG_BASE + PORT_OFFSET(PORT_CH_DATA->port - 'A')), PORT_CH_DATA->pin_num,
			ConfigPtr->ChsDataStates[i]->channel_state);
		}
		else //if pull up then make it input and put high to the PORT reg
		{
			// assign pin as input
			ASSIGN_BIT(*(DDR_REG_BASE + PORT_OFFSET(PORT_CH_DATA->port - 'A')), PORT_CH_DATA->pin_num, 0);
			// put 1 to port pin to make it pull up
			ASSIGN_BIT(*(PORT_REG_BASE + PORT_OFFSET(PORT_CH_DATA->port - 'A')), PORT_CH_DATA->pin_num, 1);
		}
		
	}
	
}