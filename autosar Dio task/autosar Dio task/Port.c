/*
 * Port.c
 *
 * Created: 01/04/2020 12:53:16 م
 *  Author: Ali makhlouf
 * PORT Module's files are stub files that are not based on autosar standard 
 */ 


#include "Port.h"


//NOTE: this module's functions are STUBBING functions (do not follow autosar standard)
#define PORT_CH_DATA(i) ConfigPtr->ChsDataStates[(i)]->ch_data


//for now(as we have only studied the DIO module) this function is responsible for setting the 
//direction register of atmega32 (DDR register) of the corresponding channels selected
void Port_Init(const Port_ConfigType * ConfigPtr)
{
	
	for (uint8 i = 0; i < PINS_NUM; i++ )
	{
		
		if (ConfigPtr->ChsDataStates[i]->channel_state != PORT_PULLUP)
		{
			//put this direction in the specific pin_no in the specific port
			ASSIGN_BIT(*(DDR_REG_BASE + PORT_OFFSET(PORT_CH_DATA(i)->port - 'A')), PORT_CH_DATA(i)->pin_num,
						ConfigPtr->ChsDataStates[i]->channel_state);
		}
		else //if pull up then make it input and put high to the PORT reg
		{
			// assign pin as input
			ASSIGN_BIT(*(DDR_REG_BASE + PORT_OFFSET(PORT_CH_DATA(i)->port - 'A')), PORT_CH_DATA(i)->pin_num, 0);
			// put 1 to port pin to make it pull up
			ASSIGN_BIT(*(PORT_REG_BASE + PORT_OFFSET(PORT_CH_DATA(i)->port - 'A')), PORT_CH_DATA(i)->pin_num, 1);
		}
		
	}
	
}