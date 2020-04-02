﻿/*
 * Dio.h
 *
 * Created: 01/04/2020 12:38:23 م
 *  Author: Ali makhlouf
 */ 


#ifndef DIO_H_
#define DIO_H_


#include "Std_Types.h"
#include "Dio_Cfg.h"


//API SERVICES ID
#define DIO_READCHANNEL_ID            0X00
#define DIO_WRITECHANNEL_ID           0X01
#define DIO_READPORT_ID               0X02
#define DIO_WRITEPORT_ID              0X03
#define DIO_READCHANNELGROUP_ID       0X04
#define DIO_WRITECHANNELGROUP_ID      0X05
#define DIO_GETSERVICEINFO_ID         0X11
#define DIO_FLIPCHANNEL_ID            0X12

// ERRORS IDs
#define DIO_E_PARAM_INVALID_CHANNEL_ID     0x0A
#define DIO_E_PARAM_CONFIG                 0X10
#define DIO_E_PARAM_INVALID_PORT_ID        0X14
#define DIO_E_PARAM_INVALID_GROUP          0X1F
#define DIO_E_PARAM_POINTER                0X20

#define DioId 125 //based on this link https://dev.toppers.jp/trac_user/ap/wiki/r422




/*internal data types of the Dio module*/ 
typedef uint8 Dio_ChannelType;

typedef uint8 Dio_PortType;

typedef struct {
	uint8 mask;
	uint8 offset;
	Dio_PortType port;
	
}Dio_ChannelGroupType;

typedef uint8 Dio_LevelType ;

typedef uint8 Dio_PortLevelType;
/***************************************************/



/**user defined types to be used in the Lcfg.c file**/
typedef struct {
	Dio_ChannelType Channel_Id;
	uint8 pin_num;
	uint8 port;
} channels_StructArrType;

typedef struct {
	Dio_PortType Port_Id;
	uint8 port;
} ports_StructArrType;

typedef struct  {
	Dio_ChannelGroupType * Group_ID;
	uint8 port;
} groups_StructArrType;
/*******************************************************/



//functions prototypes
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId);
void Dio_WriteChannel (Dio_ChannelType ChannelId, Dio_LevelType Level);
Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId);
void Dio_WritePort (Dio_PortType PortId, Dio_PortLevelType Level);
Dio_PortLevelType Dio_ReadChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr);
void Dio_WriteChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level);

#if (DioVersionInfoApi == STD_ON)
void Dio_GetVersionInfo (Std_VersionInfoType* VersionInfo);
#endif

#if (DioFlipChannelApi == STD_ON)
Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId);
#endif


//link time configurations
extern channels_StructArrType channels[PINS_NUM];
extern ports_StructArrType ports[PORTS_NUM];
extern groups_StructArrType groups[GROUPS_NUM];


#endif /* DIO_H_ */