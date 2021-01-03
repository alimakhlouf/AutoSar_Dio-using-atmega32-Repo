/*
 * Dio_Cfg.h
 *
 * Created: 01/04/2020 12:41:39 م
 *  Author: Ali makhlouf
 */ 


#ifndef DIO_CFG_H_
#define DIO_CFG_H_




//DIO_GENERAL .. these also existed in the dio_md.arxml

/*
Switches the development error detection and notification on or off.
 true: detection and notification is enabled.
1
 false: detection and notification is disabled.
Type EcucBooleanParamDef
*/
#define DioDevErrorDetect STD_ON

/*
Adds / removes the service Dio_FlipChannel() from the code.
1
EcucBooleanParamDef
*/                                                   
#define DioFlipChannelApi STD_ON

/*
Adds / removes the service Dio_GetVersionInfo() from the code.
1
EcucBooleanParamDef
*/
#define DioVersionInfoApi STD_OFF                          
/********************************************************************/ 



//Dio_PORT
/*
- Numeric identifier of the DIO port. Not all MCU ports may be used for DIO,
  thus there may be "gaps" in the list of all IDs. This value will be
  assigned to the DIO port symbolic name (i.e. the SHORT-NAME of the
  DioPort container) .
-1
-EcucIntegerParamDef
-Range 0 .. 4294967295
*/


/*************CHANNELS - PORTS - GROUPS NUMBERS***********/
#define PINS_NUM   4
#define PORTS_NUM  2
#define GROUPS_NUM 0
/*********************************************************/


/*****************PORTS - CHANNELS - GROUPS IDs ********************/
/**page 45 in SWS :This value will be assigned to the DIO port symbolic
 name (i.e. the SHORT-NAME of the DioPort container)*/
#define DioPortId_1 0
#define DioPortId_2 1
#define DioChannelId_1 1
#define DioChannelId_2 6
#define DioChannelId_3 9
#define DioChannelId_4 8    
/******************************************************************/


/********************SHORT NAMES(SYMBOLIC NAMES)**********************/
#define A      DioPortId_1  
#define B      DioPortId_2 
#define LED    DioChannelId_1
#define BUZZER DioChannelId_2
#define SW     DioChannelId_3
#define LED1   DioChannelId_4
/****************************************************************/



#endif /* DIO_CFG_H_ */