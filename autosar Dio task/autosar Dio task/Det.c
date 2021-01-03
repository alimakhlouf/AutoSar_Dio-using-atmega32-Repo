/*
 * Det.c
 *
 * Created: 01/04/2020 01:13:35 م
 *  Author: Ali makhlouf
 * DET Module's files are stub files that are not based on autosar standard 
 */ 

#include "Det.h"


//NOTE: this module's functions are stubbing function (do not follow autosar standard) 


Det_ConfigType det_config = {&DDRC, &PORTC};

void Det_Init(const Det_ConfigType* ConfigPtr)
{
	*(ConfigPtr->det_ddr) = 0xff;
}


Std_ReturnType Det_ReportError(uint16 ModuleId,uint8 InstanceId,uint8 ApiId, uint8 ErrorId)
{
	*(det_config.det_port) = ErrorId;
	
	return E_OK;
}