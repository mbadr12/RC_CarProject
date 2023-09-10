/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr - Adham El-Srougy- Hazem Magdy - Omar Ayman
 *	   	   File:  RC_Car.c
 *		  Layer:  App
 *       Module:  Car Application
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../LIB/Std_Types.h"
#include "../LIB/Bit_Math.h"

#include "../HAL/LCD/LCD.h"
#include "../HAL/LDR/LDR.h"
#include "../HAL/Temperature/Temperature.h"
#include "../HAL/Ultrasonic/Ultrasonic.h"

#include "../Service/Scheduler/Scheduler.h"

#include "RC_Car.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static u8 APP_LCDX=0,APP_LCDY=0;
static LCD_Config_t APP_LCD={.ControlPins={GPIO_PIN0,GPIO_PIN7,GPIO_PIN1},.ControlPinsPorts={GPIO_PORTB,GPIO_PORTF,GPIO_PORTB},.Cursor=LCD_NO_CURSOR,
                             .DataPins={GPIO_PIN2,GPIO_PIN3,GPIO_PIN4,GPIO_PIN5},.Font=LCD_5_8_FONT,.LinesNum=LCD_TWO_LINES,.Mode=LCD_4BIT_MODE,
                             .XPosition=&APP_LCDX,.Yposition=&APP_LCDY,.DataPinsPorts={GPIO_PORTB,GPIO_PORTB,GPIO_PORTB,GPIO_PORTB}};
static u64 APP_Distance=0;

static u8 APP_UltrasonicGFlag=0;
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
 * \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Description
 * \Parameters (out): parameterName   Parameter Description
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/

void UltraSonic_Task(void)
{
    if(APP_UltrasonicGFlag==1)
    {
        LCD_WriteNumber(&APP_LCD, APP_Distance);
        APP_UltrasonicGFlag=0;
    }
}

void Ultrasonic_Notifaction(void)
{
    APP_UltrasonicGFlag=1;
    ultrasonic_distance(&APP_Distance, Ultrasonic_Notifaction);
}

void CAR_Init(void)
{
    /*Initialize the system*/
    LCD_Init(&APP_LCD);
    Ultra_Sonic_init();
    LDR_Init();
    Temperature_Init();
    ultrasonic_distance(&APP_Distance, Ultrasonic_Notifaction);
    Create_Task(UltraSonic_Task, 50, 0, 0);
    while(1);
    Tasks_Sceduler();
}

/**********************************************************************************************************************
 *  END OF FILE: RC_Car_Program.c
 *********************************************************************************************************************/
