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
#include "Std_Types.h"
#include "Bit_Math.h"

#include "SysTick.h"

#include "Scheduler.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static TCB_t TASK_ControlBlock[MAX_TASK_NUM]={{NULL}};

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
ErrorState_t Create_Task(void(*Copy_TaskFunc)(void),u32 Copy_Periodicity,u32 Copy_FirstDelay,u8 Copy_Priority)
{
    ErrorState_t Local_ErrorState=E_OK;
    if(Copy_TaskFunc==NULL)
    {
        Local_ErrorState=E_NULL_POINTER;
    }
    else
    {
        /*Make sure that the priority isn't set to another task*/
        if((TASK_ControlBlock[Copy_Priority].Task_Func==NULL) && (Copy_Priority<MAX_TASK_NUM))
        {
            /*Set the task parameters*/
            TASK_ControlBlock[Copy_Priority].Task_Func=Copy_TaskFunc;
            TASK_ControlBlock[Copy_Priority].Periodicity=Copy_Periodicity;
            TASK_ControlBlock[Copy_Priority].First_Delay=Copy_FirstDelay;
            TASK_ControlBlock[Copy_Priority].State=TASK_RESUMED;
        }
        else
        {
            Local_ErrorState=E_NOK;
        }
    }
    return Local_ErrorState;
}

ErrorState_t Resunme_Task(u8 Copy_Priority)
{
    ErrorState_t Local_ErrorState=E_OK;
    if(Copy_Priority<MAX_TASK_NUM)
    {
        TASK_ControlBlock[Copy_Priority].State=TASK_RESUMED;
    }
    else
    {
        Local_ErrorState=E_WRONG_OPTION;
    }
    return Local_ErrorState;
}

ErrorState_t Suspend_Task(u8 Copy_Priority)
{
    ErrorState_t Local_ErrorState=E_OK;
    if(Copy_Priority<MAX_TASK_NUM)
    {
        TASK_ControlBlock[Copy_Priority].State=TASK_SUSPENDED;
    }
    else
    {
        Local_ErrorState=E_WRONG_OPTION;
    }
    return Local_ErrorState;
}

ErrorState_t Delete_Task(u8 Copy_Priority)
{
    ErrorState_t Local_ErrorState=E_OK;
    if(Copy_Priority<MAX_TASK_NUM)
    {
        TASK_ControlBlock[Copy_Priority].Task_Func=NULL;
    }
    else
    {
        Local_ErrorState=E_WRONG_OPTION;
    }
    return Local_ErrorState;
}

void Tasks_Sceduler(void)
{
    u8 Local_Counter=0;
    STK_Init(STK_INT_OS_DIV_4, (OS_TICK_US*4UL), STK_INT_ENABLED);
    STK_SetCallBack(OS_Tick_Notification);
    while(1)
    {
        if(OS_Flag==OS_PRESENT)
        {
            /*Set the OS tick as not Present*/
            OS_Flag=OS_NOT_PRESENT;
            for(Local_Counter=0;Local_Counter<MAX_TASK_NUM;Local_Counter++)
            {
                /*check if task is Already Created*/
                if(TASK_ControlBlock[Local_Counter].Task_Func!=NULL)
                {
                    /*Check if Task Resumed*/
                    if(TASK_ControlBlock[Local_Counter].State==TASK_RESUMED)
                    {
                        /*If task periodicity come go and implement it*/
                        if(TASK_ControlBlock[Local_Counter].First_Delay==0)
                        {
                            TASK_ControlBlock[Local_Counter].Task_Func();
                            /*Set first delay with the task periodicity*/
                            TASK_ControlBlock[Local_Counter].First_Delay=TASK_ControlBlock[Local_Counter].Periodicity-1;
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
