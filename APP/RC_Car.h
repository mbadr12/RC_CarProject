/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  RC_Car_interface.h
 *		  Layer:  App
 *        Module:  Car Application
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef RC_CAR_H
#define RC_CAR_H

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define LDR_DIFF            700UL

#define MIN_DISTANCE        10UL

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : void Ultrasonic_Notifaction(void)
 * \Description     : Notification Function of the ultrasonic reading completion
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void Ultrasonic_Notifaction(void);

/******************************************************************************
 * \Syntax          : void Switch1_Notification(void)
 * \Description     : Notification Function of the Pressing Switch 1
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void Switch1_Notification(void);

/******************************************************************************
 * \Syntax          : void Switch2_Notification(void)
 * \Description     : Notification Function of the Pressing Switch 2
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void Switch2_Notification(void);
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : void CAR_Init(void)
 * \Description     : Initialization of hardware and creation of tasks
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void CAR_Init(void);

/******************************************************************************
 * \Syntax          : void UltraSonic_Task(void)
 * \Description     : Get the Ultrasonic Reading
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void UltraSonic_Task(void);

/******************************************************************************
 * \Syntax          : void avoid_obstacles(void)
 * \Description     : A task Implements the logic of obstacles avoid
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void avoid_obstacles(void);

/******************************************************************************
 * \Syntax          : void CarStart_Task(void)
 * \Description     : Start Moving the Car
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void CarStart_Task(void);

/******************************************************************************
 * \Syntax          : void CarStop_Task(void)
 * \Description     : Stop Moving the Car
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void CarStop_Task(void);

/******************************************************************************
 * \Syntax          : void Watch_Task(void)
 * \Description     : Calculate the elapsed time of the car moving
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void Watch_Task(void);

/******************************************************************************
 * \Syntax          : void ldr_swing_car(void)
 * \Description     : A task that Implements the logic of Swing of car
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void ldr_swing_car(void);

/******************************************************************************
 * \Syntax          : void LCD_Distancedisplay(void)
 * \Description     : Display the Distance on LCD
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void LCD_Distancedisplay(void);

/******************************************************************************
 * \Syntax          : void LCD_LDRDisplay(void)
 * \Description     : Display the Difference of the 2 LDRs Reading on LCD
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void LCD_LDRDisplay(void);

/******************************************************************************
 * \Syntax          : void LCD_TimeDisplay(void)
 * \Description     : Display the Difference of the 2 LDRs Reading on LCD
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void LCD_TimeDisplay(void);

/******************************************************************************
 * \Syntax          : void Temperature_Task(void)
 * \Description     : Get the temperature every 4 Seconds
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void Temperature_Task(void);

#endif  /* RC_Car_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: RC_Car.h
 *********************************************************************************************************************/
