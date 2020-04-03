/*
 * Std_Types.h
 *
 * Created: 01/04/2020 12:43:00 م
 *  Author: Ali makhlouf
 */ 


#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#include "Compiler.h"
#include "Platform_Types.h"

typedef uint8 Std_ReturnType;
 
#define E_OK       1
#define E_NOT_OK   0 
#define STD_HIGH   1
#define STD_LOW    0
#define STD_ACTIVE 1
#define STD_IDLE 0
#define STD_ON     1
#define STD_OFF    0   

typedef struct
{
	uint16 vendorID;
	uint16 moduleID;
	uint8 instanceID;
	uint8 sw_major_version;
	uint8 sw_minor_version;
	uint8 sw_patch_version;
} Std_VersionInfoType;

#endif /* STD_TYPES_H_ */