/*
 * Port_Lcfg.c
 *
 * Created: 01/04/2020 01:27:01 م
 *  Author: Ali makhlouf
 */ 


#include "Port.h"

//link time configurations used in Port_Init function 
Ports_DirType pinstates[PINS_NUM] = {
	{&channels[0], PORT_OUTPUT}, //channels array exist in Dio_Lcfg.h
	{&channels[1], PORT_OUTPUT},
	{&channels[2], PORT_PULLUP},
	{&channels[3], PORT_OUTPUT}
};

//initialization structure passed to the Port_Init function .. it point to the upper function
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