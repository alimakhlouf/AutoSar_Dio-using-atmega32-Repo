/*
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

// the address of the first PIN registers(which is PINA)
#define PIN_REG_BASE (volatile uint8 *)(0x39)
// the address of the first  DDR registers(which is DDRA)
#define DDR_REG_BASE (volatile uint8 *)(0x3A)
// the address of the first  PORT registers(which is PORTA)
#define PORT_REG_BASE (volatile uint8 *)(0x3B)

//it chooses the port registers based on the offset whether A(offset 0) - B(offset 1) - C(offset 3)
//D(offset 4).
#define PORT_OFFSET(n) (((n) * -3))

//defines the PORT register address based on the char value in actual_port (e.g. if actual_ pin =  'B'
 //will give you the address of PORTB)  
#define SPECIFIC_PORT_REG *(PORT_REG_BASE + PORT_OFFSET(actual_port - 'A'))

//gives you the PIN register address based on the char value in actual_port (e.g. if actual_ pin = 'C'
//then it will give you the address of PINC)
#define SPECIFIC_PIN_REG *(PIN_REG_BASE + PORT_OFFSET(actual_port  - 'A'))




Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	
	uint8 i = 0; //used as a counter below
	uint8 ch_port = 0; //will hold the port value of the parameter channel_id  
	uint8 ch_pin = 0; //will hold the pin number of the parameter channel_id (aaccording to 
	//the port which it's in)  
	
	Dio_LevelType result; //the level of the channel
	
	//search for the parameter channel_ID in the available IDs you have
	for (i = 0; i < PINS_NUM; i++ )
	{
		
		//if the ID in the parameter exists within the available IDs
		if (ChannelId == channels[i].Channel_Id)
		{
			ch_port = channels[i].port; //hold the port value of the parameter channel_id 
			ch_pin = channels[i].pin_num; //will hold the pin number (according to the port)
			// of the parameter channel_id
			break;
		}
		
	}

#if DioDevErrorDetect == STD_ON
	//if no such ID exists .. report an error
	if (i >= PINS_NUM)
	{
		Det_ReportError(DioId, 0, DIO_READCHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID);
	}
#endif

	//get the channel value using the pin_num value and the port value 
	if (GET_BIT(*(PIN_REG_BASE + PORT_OFFSET(ch_port - 'A')), ch_pin) != 0)
	{
		result = STD_HIGH;
	}
	else
	{
		result = STD_LOW;
	}
		
	
	
	//return this value
	return result;
}


void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
	
	//same comments as Dio_ReadChannel
	uint8 i = 0;
	uint8 ch_port = 0;
	uint8 ch_pin = 0;
	
	for (i = 0; i < PINS_NUM; i++ )
	{
		
		if (ChannelId == channels[i].Channel_Id)
		{
			ch_port = channels[i].port;
			ch_pin = channels[i].pin_num;
			break;
		}
		
	}

	
#if DioDevErrorDetect == STD_ON
	if (i >= PINS_NUM)
	{
		Det_ReportError(DioId, 0, DIO_WRITECHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID);
	}
	
#endif
	//assign the level to the channel
	//
	ASSIGN_BIT(*(PORT_REG_BASE + PORT_OFFSET(ch_port - 'A')), ch_pin, Level);
	
}


Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
	uint8 i = 0;
	uint8 actual_port = 'A';
	
	for (i = 0; i < PORTS_NUM; i++ )
	{
		
		if (PortId == ports[i].Port_Id)
		{
			actual_port = ports[i].port;
			break;
		}
		
	}
	
#if DioDevErrorDetect == STD_ON
	if (i >= PORTS_NUM)
	{
		Det_ReportError(DioId, 0, DIO_READPORT_ID, DIO_E_PARAM_INVALID_PORT_ID);
	}
#endif
	
	//return the PIN register of the specific PortId 
	return (SPECIFIC_PIN_REG);
}

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
	//same comments as Dio_ReadPort
	uint8 i = 0;
	uint8 actual_port = 'A';
	
	for (i = 0; i < PORTS_NUM; i++ )
	{
		
		if (PortId == ports[i].Port_Id)
		{
			actual_port = ports[i].port;
			break;
		}
		
	}
	
#if DioDevErrorDetect == STD_ON
	if (i >= PORTS_NUM)
	{
		Det_ReportError(DioId, 0, DIO_WRITEPORT_ID, DIO_E_PARAM_INVALID_PORT_ID);
	}
#endif
	
	//set the selected PORT register the value in the parameter(level) 
	SPECIFIC_PORT_REG = Level;
	
}

Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr)
{
	uint8 i = 0;
	uint8 actual_port = 'A';
	
	for (i = 0; i < GROUPS_NUM; i++ )
	{
		
		if (ChannelGroupIdPtr == groups[i].Group_ID)
		{
			actual_port = groups[i].port;
			break;
		}
		
	}
	
	
#if DioDevErrorDetect == STD_ON
	if (i >= GROUPS_NUM)
	{
		Det_ReportError(DioId, 0, DIO_READCHANNELGROUP_ID, DIO_E_PARAM_INVALID_GROUP);
	}
#endif
	
	//first select the PIN register .. then apply he mask to get the specific bits the shift right
	// to remove the offset 
	return ( ((SPECIFIC_PIN_REG) & ChannelGroupIdPtr->mask) >> ChannelGroupIdPtr->offset ) ;
}

void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level)
{
	int8 i = 0;
	uint8 actual_port = 'A';
	
	for (i = 0; i < GROUPS_NUM; i++ )
	{
		
		if (ChannelGroupIdPtr == groups[i].Group_ID)
		{
			actual_port = groups[i].port;
			break;
		}
		
	}
	
#if DioDevErrorDetect == STD_ON
	if (i >= GROUPS_NUM)
	{
		Det_ReportError(DioId, 0, DIO_WRITECHANNELGROUP_ID, DIO_E_PARAM_INVALID_GROUP);
	}
#endif
	
	//assign the group to the port by first clearing the bits and then oring with the channel 
	//group after shifting thm to their specific offset  
	SPECIFIC_PORT_REG = ((SPECIFIC_PORT_REG) & ~(ChannelGroupIdPtr->mask)) | 
	                     (Level << ChannelGroupIdPtr->offset);
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
	uint8 actual_port = 'A';
	uint8 ch_pin = 0;
	
	for (i = 0; i < PINS_NUM; i++ )
	{
		
		if (ChannelId == channels[i].Channel_Id)
		{
			actual_port = channels[i].port;
			ch_pin = channels[i].pin_num;
			break;
		}
		
	}
	
#if DioDevErrorDetect == STD_ON
	if (i >= PINS_NUM)
	{
		Det_ReportError(DioId, 0, DIO_WRITECHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID);
	}
	
#endif
	
	
	TOGGLE_BIT(SPECIFIC_PORT_REG, ch_pin);
	
	
	
	return Dio_ReadChannel(ChannelId);
	
}
#endif