/*
 * Det.h
 *
 * Created: 01/04/2020 12:46:42 م
 * Author: Ali makhlouf
 * DET Module's files are stub files that are not based on autosar standard 
 */ 

// it's included from another module so you have to go to go to this module to know how o write DET)Report Error function
//and stub this function
// and the code included in it f it for example toggles a certain led ten you write the code hat toggles t dirtectly with no standard


#ifndef DET_H_
#define DET_H_

#include "Std_Types.h"
#include "Std_Types.h"
#include "micro_config.h"


typedef struct {
	uint8 * det_ddr;
	uint8 * det_port;  
}Det_ConfigType;

Std_ReturnType Det_ReportError(uint16 ModuleId,uint8 InstanceId,uint8 ApiId, uint8 ErrorId);

#endif /* DET_H_ */