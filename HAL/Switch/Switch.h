/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  Switch_interface.h
 *		  Layer:  HAL
 *       Module:  Switch
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef SWITCH_INTERFACE_H
#define SWITCH_INTERFACE_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/EXTI/EXTI.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
    SW_PRESSED=0,
    SW_NOT_PRESSED
}Switch_State_t;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : ErrorState_t LCD_Init(LCD_Config_t* Copy_Config)
 * \Description     : Initialize the LCD module
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_Config     The Configuration structure for the module
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *******************************************************************************/
ErrorState_t Switch_Init(GPIO_Port_t Copy_SwPort,GPIO_Pin_t Copy_SwPin,GPIO_PinPullUpDown_t Copy_SwState);

ErrorState_t Switch_IntConfig(EXTI_Config_t *Copy_Button,void(*Copy_NotificationFunc)(void));

ErrorState_t Switch_GetStatus(GPIO_Port_t Copy_SwPort,GPIO_Pin_t Copy_SwPin,GPIO_PinPullUpDown_t Copy_SwPullType,Switch_State_t* Copy_SwState);

#endif  /* SWITCH_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Switch_interface.h
 *********************************************************************************************************************/
