/*
 * Port.h
 *
 * Created: 01/04/2020 12:52:24 م
 *  Author: Ali makhlouf
 */ 


#ifndef PORT_H_
#define PORT_H_


#include "Dio.h"
#include "Std_Types.h"
#include "common_macros.h" //not standardized library


#define  PORT_INPUT  0
#define  PORT_OUTPUT 1
#define  PORT_PULLUP 2


//user defined types for link time configurations in Port_Lcfg.h file
typedef struct {
	channels_StructArrType * ch_data;
	uint8 channel_state;
}Ports_DirType;

typedef struct {
	Ports_DirType * ChsDataStates[PINS_NUM];
} Port_ConfigType;
/***********************************************/

//functions prototypes
void Port_Init (const Port_ConfigType * ConfigPtr);




extern Ports_DirType pinstates[PINS_NUM] ;
extern Port_ConfigType port_config;
#endif /* PORT_H_ */