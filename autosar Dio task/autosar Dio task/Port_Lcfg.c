/*
 * Port_Lcfg.c
 *
 * Created: 01/04/2020 01:27:01 م
 *  Author: Ali makhlouf
 * PORT Module's files are stub files that are not based on autosar standard 
 */ 


#include "Port.h"

//link time configurations used in Port_Init function 
//channels array exist in Dio_Lcfg.c .. it's not right to use another modules files but this is a stubbing function
Ports_DirType pinstates[PINS_NUM] = {
	{&channels[0], PORT_OUTPUT}, 
	{&channels[1], PORT_OUTPUT},
	{&channels[2], PORT_PULLUP},
	{&channels[3], PORT_OUTPUT}
};

//initialization structure passed to the Port_Init function .. it points to the upper structure
//which points to the actual configuration that is in the upper structure , but we defined this to
//be compatible with the standard function template 
Port_ConfigType port_config = {
	{
		&pinstates[0], 
		&pinstates[1],
		&pinstates[2],
		&pinstates[3]
	}
};