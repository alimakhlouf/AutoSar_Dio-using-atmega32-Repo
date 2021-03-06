﻿/*
 * Dio.c
 *
 * Created: 01/04/2020 12:38:39 م
 *  Author: Ali makhlouf
 */ 

#include "Dio.h"
#include "Dio_MemMap.h"
#include "Det.h"
#include "SchM_Dio.h"
#include "common_macros.h"




Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	
	uint8 i = 0; //used as a counter below
	uint8 mcu_port = 0; //will hold the port value of the parameter channel_id  
	uint8 ch_pin = 0; //will hold the pin number of the parameter channel_id (aaccording to 
	//the port which it's in)  
	
	Dio_LevelType result; //the level of the channel
	
	//search for the parameter channel_ID in the available IDs you have
	for (i = 0; i < PINS_NUM; i++ )
	{
		
		//if the ID in the parameter exists within the available IDs
		if (ChannelId == channels[i].Channel_Id)
		{
			mcu_port = channels[i].port; //hold the port value of the parameter channel_id 
			ch_pin = channels[i].pin_num; //will hold the pin number (according to the port)
			// of the parameter channel_id
			break;
		}
		
	}

#if DioDevErrorDetect == STD_ON
	//if no such ID exists .. report an error
	if (i >= PINS_NUM)
	{
		// If development errors are enabled and an error occurred, the Dio
		//module's read functions shall return with the value '0'.
		Det_ReportError(DioId, 0, DIO_READCHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		
		return 0; //applying error SWS_Dio_00118
	}
#endif


	//get the channel value using the pin_num value and the port value 
	if (GET_BIT(SPECIFIC_PIN_REG(mcu_port) , ch_pin) != 0)
	{
		result = STD_HIGH;
	}
	else
	{
		result = STD_LOW;
	}
	
	/*[SWS_Dio_00083] ⌈If the micro-controller supports the direct read-back of a pin
	value, the Dio module's read functions shall provide the real pin level, when they are
	used on a channel which is configured as an output channel.⌋
	
	actually this requirement is automatically applied since the PIN register reads the pin real value in both
	input states (input - ouput)  */
		
	
	
	//return this value
	return result;
}


void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
	
	//same comments as Dio_ReadChannel
	uint8 i = 0;
	uint8 mcu_port = 0;
	uint8 ch_pin = 0;
	uint8 pin_state = 0;
	
	for (i = 0; i < PINS_NUM; i++ )
	{
		
		if (ChannelId == channels[i].Channel_Id)
		{
			mcu_port = channels[i].port;
			ch_pin = channels[i].pin_num;
			pin_state = GET_BIT (SPECIFIC_DDR_REG(mcu_port), ch_pin); //also receive the pin state which is in pinstates
			                                        // struct in Port_Lcfg.c
			break;
		}
		
	}
	
	
#if DioDevErrorDetect == STD_ON
	if (i >= PINS_NUM)
	{
		Det_ReportError(DioId, 0, DIO_WRITECHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		return ; //we must abort the write operation to avoid any runtime errors
	}
#endif

	/*applying [SWS_Dio_00070] ⌈If a Dio write function is used on an input channel, it shall have
	no effect on the physical output level. ⌋ */
	if (pin_state == STD_HIGH) //if it's output
	{
		//assign the level to the channel
		ASSIGN_BIT(SPECIFIC_PORT_REG(mcu_port), ch_pin, Level);
	}
	
}


Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
	uint8 i = 0;
	uint8 mcu_port = 'A';
	
	for (i = 0; i < PORTS_NUM; i++ )
	{
		
		if (PortId == ports[i].Port_Id)
		{
			mcu_port = ports[i].port;
			break;
		}
		
	}
	
#if DioDevErrorDetect == STD_ON
	if (i >= PORTS_NUM)
	{
		// If development errors are enabled and an error occurred, the Dio
		//module's read functions shall return with the value '0'.
		Det_ReportError(DioId, 0, DIO_READPORT_ID, DIO_E_PARAM_INVALID_PORT_ID);
		return 0; //applying error SWS_Dio_00118
	}
#endif
	
	/*[SWS_Dio_00083] ⌈If the micro-controller supports the direct read-back of a pin
	value, the Dio module's read functions shall provide the real pin level, when they are
	used on a channel which is configured as an output channel.⌋
	this requirement is automatically applied sincethe PIN register reads the pin real value in both
	input states (inpu - ouput)  */
	
	//return the PIN register of the specific PortId 
	return (SPECIFIC_PIN_REG(mcu_port));
}

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
	//same comments as Dio_ReadPort
	uint8 i = 0;
	uint8 mcu_port = 'A';
	
	for (i = 0; i < PORTS_NUM; i++ )
	{
		
		if (PortId == ports[i].Port_Id)
		{
			mcu_port = ports[i].port;
			break;
		}
		
	}
	
#if DioDevErrorDetect == STD_ON
	if (i >= PORTS_NUM)
	{
		Det_ReportError(DioId, 0, DIO_WRITEPORT_ID, DIO_E_PARAM_INVALID_PORT_ID);
		return ; //we must abort the write operation to avoid any runtime errors
	}
#endif

	/*applying [SWS_Dio_00004] ⌈The Dio_WritePort function shall ensure that the functionality
	of the input channels of that port is not affected. ⌋*/
	for (uint8 cnt = 0 ; cnt < 8; cnt++ )
	{
		
		// if the pin in the port is (output) apply the new bit status otherwise do not do apply 
		if (GET_BIT(SPECIFIC_DDR_REG(mcu_port), cnt) != STD_LOW)
		{
			ASSIGN_BIT(SPECIFIC_PORT_REG(mcu_port), cnt, GET_BIT(Level , cnt) );
		}
		
	}
	
}

Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr)
{
	uint8 i = 0;
	uint8 mcu_port = 'A';
	
	for (i = 0; i < GROUPS_NUM; i++ )
	{
		
		if (ChannelGroupIdPtr == groups[i].Group_ID)
		{
			mcu_port = groups[i].port;
			break;
		}
		
	}
	
	
#if DioDevErrorDetect == STD_ON
	if (i >= GROUPS_NUM)
	{
		// If development errors are enabled and an error occurred, the Dio
		//module's read functions shall return with the value '0'.
		Det_ReportError(DioId, 0, DIO_READCHANNELGROUP_ID, DIO_E_PARAM_INVALID_GROUP);
		return 0; //applying error SWS_Dio_00118
	}
#endif
	
	/*[SWS_Dio_00083] ⌈If the micro-controller supports the direct read-back of a pin
	value, the Dio module's read functions shall provide the real pin level, when they are
	used on a channel which is configured as an output channel.⌋
	this requirement is automatically applied sincethe PIN register reads the pin real value in both
	input states (inpu - ouput)  */
	
	//first select the PIN register .. then apply he mask to get the specific bits the shift right
	// to remove the offset 
	return ( ((SPECIFIC_PIN_REG(mcu_port)) & ChannelGroupIdPtr->mask) >> ChannelGroupIdPtr->offset ) ;
}

void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level)
{
	int8 i = 0;
	uint8 mcu_port = 'A';
	
	for (i = 0; i < GROUPS_NUM; i++ )
	{
		
		if (ChannelGroupIdPtr == groups[i].Group_ID)
		{
			mcu_port = groups[i].port;
			break;
		}
		
	}
	
#if DioDevErrorDetect == STD_ON
	if (i >= GROUPS_NUM)
	{
		Det_ReportError(DioId, 0, DIO_WRITECHANNELGROUP_ID, DIO_E_PARAM_INVALID_GROUP);
		return ; //we must abort the write operation to avoid any runtime errors
	}
#endif
	
	/*now we want to apply [SWS_Dio_00040] ⌈The Dio_WriteChannelGroup shall not change the remaining
	channels of the port and channels which are configured as input. ⌋
	this is done by checking every bit in the group bits and check whether it's input or output then apply the corresponding
	new bit value if it's output ( we don't need to check the the rest of the bit in the port as we 
	won't be assigning anything to them in the first place)*/
	
	for  (uint8 i = 0; i < 8; i++ )
	{
		if (GET_BIT(ChannelGroupIdPtr->mask, (1 << i)) == STD_HIGH) // if it has found one of the channel groups
		{
			
			if (GET_BIT (SPECIFIC_DDR_REG(mcu_port), 1 << i ) == STD_HIGH) //if it's output
			{
				ASSIGN_BIT(SPECIFIC_PORT_REG(mcu_port), 1 << i , GET_BIT(Level, i) );
			}
			
		}
		
		
	}
	
}

#if (DioVersionInfoApi == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType* VersionInfo)
{
	//out of scope for now
}
#endif

#if (DioFlipChannelApi == STD_ON)
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
	uint8 i = 0;
	uint8 mcu_port = 'A';
	uint8 ch_pin = 0;
	
	for (i = 0; i < PINS_NUM; i++ )
	{
		
		if (ChannelId == channels[i].Channel_Id)
		{
			mcu_port = channels[i].port;
			ch_pin = channels[i].pin_num;
			break;
		}
		
	}
	
#if DioDevErrorDetect == STD_ON
	if (i >= PINS_NUM)
	{
		Det_ReportError(DioId, 0, DIO_WRITECHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		return Dio_ReadChannel(ChannelId); //applying SWS_Dio_00118 .. flip also reads the pin 
				  //after flipping it so the error is a applied to it
	}
	
#endif
	
	
	TOGGLE_BIT(SPECIFIC_PORT_REG(mcu_port), ch_pin);
	
	//applying SWS_Dio_00118 .. flip also reads the pin 
	//after flipping it
	return Dio_ReadChannel(ChannelId);
	
}
#endif