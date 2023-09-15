/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  SCHEDULER_Program.c
 *		  Layer:  Service
 *        Module:  Scheduler
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../../LIB/Std_Types.h"

#include "../SysTick/SysTick.h"

#include "Scheduler.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static TCB_t TASK_ControlBlock[NUM_OF_TASKS]={NULL};

static u8 OS_Flag=OS_NOT_PRESENT;

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
static void OS_Tick_Notification(void)
{
    OS_Flag=OS_PRESENT;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
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
ErrorState_t Create_Task(void(*Copy_TaskFunc)(void),u32 Copy_Periodicity,u32 Copy_FirstDelay,u8 Copy_Priority)
{
    ErrorState_t Local_ErrorState0=E_OK;
    if(Copy_TaskFunc==NULL)
    {
        Local_ErrorState0=E_NULL_POINTER;
    }
    else
    {
        /*Make sure that the priority isn't set to another task*/
        if((TASK_ControlBlock[Copy_Priority].Task_Func==NULL) && (Copy_Priority<NUM_OF_TASKS))
        {
            /*Set the task parameters*/
            TASK_ControlBlock[Copy_Priority].Task_Func=Copy_TaskFunc;
            TASK_ControlBlock[Copy_Priority].Periodicity=Copy_Periodicity;
            TASK_ControlBlock[Copy_Priority].First_Delay=Copy_FirstDelay;
            TASK_ControlBlock[Copy_Priority].State=TASK_RESUMED;
        }
        else
        {
            Local_ErrorState0=E_NOK;
        }
    }
    return Local_ErrorState0;
}

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
ErrorState_t Resunme_Task(u8 Copy_Priority)
{
    ErrorState_t Local_ErrorState3=E_OK;
    if(Copy_Priority<NUM_OF_TASKS)
    {
        TASK_ControlBlock[Copy_Priority].State=TASK_RESUMED;
    }
    else
    {
        Local_ErrorState3=E_WRONG_OPTION;
    }
    return Local_ErrorState3;
}

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
ErrorState_t Suspend_Task(u8 Copy_Priority)
{
    ErrorState_t Local_ErrorState2=E_OK;
    if(Copy_Priority<NUM_OF_TASKS)
    {
        TASK_ControlBlock[Copy_Priority].State=TASK_SUSPENDED;
    }
    else
    {
        Local_ErrorState2=E_WRONG_OPTION;
    }
    return Local_ErrorState2;
}

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
ErrorState_t Delete_Task(u8 Copy_Priority)
{
    ErrorState_t Local_ErrorState1=E_OK;
    if(Copy_Priority<NUM_OF_TASKS)
    {
        TASK_ControlBlock[Copy_Priority].Task_Func=NULL;
    }
    else
    {
        Local_ErrorState1=E_WRONG_OPTION;
    }
    return Local_ErrorState1;
}

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
void Tasks_Sceduler(void)
{
    u8 Local_Counter=0;
    STK_Init(STK_INT_OS_DIV_4, (STK_Value_t)(OS_TICK_US*4UL), STK_INT_ENABLED);
    STK_SetCallBack(&OS_Tick_Notification);
    while(1)
    {
        if(OS_Flag==OS_PRESENT)
        {
            /*Set the OS tick as not Present*/
            OS_Flag=OS_NOT_PRESENT;
            for(Local_Counter=0UL;Local_Counter<NUM_OF_TASKS;Local_Counter++)
            {
                /*check if task is Already Created*/
                if(TASK_ControlBlock[Local_Counter].Task_Func!=NULL)
                {
                    /*Check if Task Resumed*/
                    if(TASK_ControlBlock[Local_Counter].State==TASK_RESUMED)
                    {
                        /*If task periodicity come go and implement it*/
                        if(TASK_ControlBlock[Local_Counter].First_Delay==0UL)
                        {
                            TASK_ControlBlock[Local_Counter].Task_Func();
                            /*Set first delay with the task periodicity*/
                            TASK_ControlBlock[Local_Counter].First_Delay=TASK_ControlBlock[Local_Counter].Periodicity-1UL;
                        }
                        else
                        {
                            TASK_ControlBlock[Local_Counter].First_Delay--;
                        }
                    }
                    else
                    {
                        /*Do Nothing*/
                    }
                }
                else
                {
                    /*Do Nothing*/
                }
            }
        }
    }
}

/**********************************************************************************************************************
 *  END OF FILE: SCHEDULER_Program.c
 *********************************************************************************************************************/
