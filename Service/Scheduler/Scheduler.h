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

#define OS_TICK_US      50000UL

#define NUM_OF_TASKS    10UL

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
    TASK_RESUMED=0,
    TASK_SUSPENDED
}Task_State_t;

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS Prototype
 *********************************************************************************************************************/
static void OS_Tick_Notification(void);

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**************************************************************************************************************************************
 * \Syntax          : ErrorState_t Create_Task(void(*Copy_TaskFunc)(void),u32 Copy_Periodicity,u32 Copy_FirstDelay,u8 Copy_Priority)
 * \Description     : Function used to create Task for user
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : Copy_TaskFunc     Pointer to Task function
 *                    Copy_Periodicity  Task Periodicity
 *                    Copy_FirstDelay   Task First delay used to get offset of starting task
 *                    Copy_Priority     Task Priority with Max 0 and Minimum NUM_OF_TASKS-1
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 **************************************************************************************************************************************/
ErrorState_t Create_Task(void(*Copy_TaskFunc)(void),u32 Copy_Periodicity,u32 Copy_FirstDelay,u8 Copy_Priority);

/**************************************************************************************************************************************
 * \Syntax          : ErrorState_t Resunme_Task(u8 Copy_Priority)
 * \Description     : Resume task
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : Copy_Priority     Task Priority with Max 0 and Minimum NUM_OF_TASKS-1
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 **************************************************************************************************************************************/
ErrorState_t Resunme_Task(u8 Copy_Priority);

/**************************************************************************************************************************************
 * \Syntax          : ErrorState_t Suspend_Task(u8 Copy_Priority)
 * \Description     : Suspend a task
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : Copy_Priority     Task Priority with Max 0 and Minimum NUM_OF_TASKS-1
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 **************************************************************************************************************************************/
ErrorState_t Suspend_Task(u8 Copy_Priority);

/**************************************************************************************************************************************
 * \Syntax          : ErrorState_t Delete_Task(u8 Copy_Priority)
 * \Description     : Delete a task
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : Copy_Priority     Task Priority with Max 0 and Minimum NUM_OF_TASKS-1
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 **************************************************************************************************************************************/
ErrorState_t Delete_Task(u8 Copy_Priority);

/**************************************************************************************************************************************
 * \Syntax          : void Tasks_Sceduler(void)
 * \Description     : Resume task
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 **************************************************************************************************************************************/
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

#define OS_PRESENT      1UL

#define OS_NOT_PRESENT  0UL
 
#endif  /* SCHEDULER_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: SCHEDULER_interface.h
 *********************************************************************************************************************/
