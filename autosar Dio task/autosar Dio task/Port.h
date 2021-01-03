/*
 * Port.h
 *
 * Created: 01/04/2020 12:52:24 م
 * Author: Ali makhlouf
 * PORT Module's files are stub files that are not based on autosar standard 
 */ 


#ifndef PORT_H_
#define PORT_H_


#include "Dio.h" // this is wrong but  it's just a stub file (not a real autosar standard
#include "Std_Types.h"
#include "common_macros.h" //not standardized library

// the address of the first PIN register(which is PINA)
#define PIN_REG_BASE (volatile uint8 *)(0x39)
// the address of the first  DDR register(which is DDRA)
#define DDR_REG_BASE (volatile uint8 *)(0x3A)
// the address of the first  PORT register(which is PORTA)
#define PORT_REG_BASE (volatile uint8 *)(0x3B)

/*it chooses the address port registers based on the offset whether A(offset 0) - B(offset 1) - 
C(offset 3) D(offset 4).*/
#define PORT_OFFSET(n) (((n) * -3))

//defines the PORT register address based on the char value in mcu_port argument (e.g. if actual_ pin =  'B'
//will give you the address of PORTB)  
#define SPECIFIC_PORT_REG *(PORT_REG_BASE + PORT_OFFSET(mcu_port - 'A'))

//gives you the PIN register address based on the char value in mcu_port (e.g. if actual_ pin = 'C'
//then it will give you the address of PINC)
#define SPECIFIC_PIN_REG *(PIN_REG_BASE + PORT_OFFSET(mcu_port  - 'A'))

//gives you the DDR register address based on the char value in mcu_port (e.g. if actual_ pin = 'C'
//then it will give you the address of PINC)
#define SPECIFIC_DDR_REG *(DDR_REG_BASE + PORT_OFFSET(mcu_port  - 'A'))
                         

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