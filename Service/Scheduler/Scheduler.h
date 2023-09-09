/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  SCHEDULER_interface.h
 *		  Layer:  Service
 *        Module:  Scheduler
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef SCHEDULER_INTERFACE_H
#define SCHEDULER_INTERFACE_H

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*Set the Tick Time in Microsecond up to 4192000*/

#define OS_TICK_US      1000

#define MAX_TASK_NUM    3

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
    TASK_RESUMED=0,
    TASK_SUSPENDED
}Task_State_t;
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): parameterName   Parameter Describtion                                                    
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
ErrorState_t Create_Task(void(*Copy_TaskFunc)(void),u32 Copy_Periodicity,u32 Copy_FirstDelay,u8 Copy_Priority);

ErrorState_t Resunme_Task(u8 Copy_Priority);

ErrorState_t Suspend_Task(u8 Copy_Priority);

ErrorState_t Delete_Task(u8 Copy_Priority);

void Tasks_Sceduler(void);

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
typedef struct
{
    void(*Task_Func)(void);
    u32 Periodicity;
    u32 First_Delay;
    Task_State_t State;
}TCB_t;

#define OS_PRESENT      1

#define OS_NOT_PRESENT  0
 
#endif  /* SCHEDULER_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: SCHEDULER_interface.h
 *********************************************************************************************************************/
