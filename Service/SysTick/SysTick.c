/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  STK_Program.c
 *		  Layer:  MCAL
 *       Module:  STK
 *		Version:  1.00
 *	
 *  Description:  Implementation of the module function
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../../LIB/Std_Types.h"
#include "../../LIB/TM4C123xx.h"
#include "../../LIB/Bit_Math.h"

#include "SysTick.h"

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
static void (*STK_CallBackFunc)(void)=NULL;

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : void STK_Delyms(u32 Copy_Delayms)
 * \Description     : used for delay of max 4192 ms
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_Delayms    Delay in ms
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void STK_Delyms(u32 Copy_Delayms)
{
    /*Max count 4192 ms*/
    /*Program the value of Load*/
    /*To convert the time to ms we must multiply by 4000*/
    STK->LOAD=Copy_Delayms*STK_FACTOR;
    /*Clear current*/
    STK->CURRENT=(u32)0;
    /*Set the clock source*/
    CLR_BIT(STK->CTRL,STK_CLK_SRC);
    /*Enable the STK*/
    SET_BIT(STK->CTRL,STK_ENABLE);
    /*Busy waiting until it counts to zero*/
    do{
        /*MISRA*/
    }
    while(GET_BIT(STK->CTRL,STK_COUNT)==0);
}

/***********************************************************************************************************************************
 * \Syntax          : ErrorState_t STK_Init(STK_ClcSource_t Copy_ClockSource, STK_Value_t Copy_Value, STK_IntState_t Copy_IntState)
 * \Description     : initialize the SysTick with required configuration
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_ClockSource    SysTick Clock Source
 *                    Copy_Value          The Top Value of SysTick
 *                    Copy_IntState       The Initial interrupt state
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *************************************************************************************************************************************/
ErrorState_t STK_Init(STK_ClcSource_t Copy_ClockSource, STK_Value_t Copy_Value, STK_IntState_t Copy_IntState)
{
    ErrorState_t Local_ErrorState=E_OK;
    if(Copy_ClockSource>STK_SYS_CLOCK)
    {
        Local_ErrorState=E_WRONG_OPTION;
    }
    else
    {
        /*Set the STK Value*/
        Local_ErrorState=STK_SetValue(Copy_Value);
        if(Local_ErrorState == E_OK)
        {
            /*Set the clock source*/
            INSERT_BIT(STK->CTRL,STK_CLK_SRC,Copy_ClockSource);
            /*Enable the STK*/
            SET_BIT(STK->CTRL,STK_ENABLE);
            /*Set interrupt state*/
            Local_ErrorState=STK_SetIntState(Copy_IntState);
            /*Enable the STK*/
            SET_BIT(STK->CTRL,STK_ENABLE);
        }
    }
    return Local_ErrorState;
}

/***********************************************************************************************************************************
 * \Syntax          : ErrorState_t STK_SetIntState(STK_IntState_t Copy_IntState)
 * \Description     : set the SysTick interrupt state
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_IntState       The interrupt state
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *************************************************************************************************************************************/
ErrorState_t STK_SetIntState(STK_IntState_t Copy_IntState)
{
    ErrorState_t Local_ErrorState=E_OK;
    if(Copy_IntState>STK_INT_ENABLED)
    {
        Local_ErrorState=E_WRONG_OPTION;
    }
    else
    {
        INSERT_BIT(STK->CTRL,STK_INT_EN,Copy_IntState);
    }
    return Local_ErrorState;
}

/***********************************************************************************************************************************
 * \Syntax          : ErrorState_t STK_SetCallBack(void (*Copy_CallBackFunc)(void))
 * \Description     : Set the SysTick callback function
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_CallBackFunc   Pointer to SysTick Callback Function
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *************************************************************************************************************************************/
ErrorState_t STK_SetCallBack(void (*Copy_CallBackFunc)(void))
{
    ErrorState_t Local_ErrorState=E_OK;
    if(Copy_CallBackFunc==NULL)
    {
        Local_ErrorState=E_NULL_POINTER;
    }
    else
    {
        /*Pass callback function to global pointer to function*/
        STK_CallBackFunc=Copy_CallBackFunc;
    }
    return Local_ErrorState;
}

/***********************************************************************************************************************************
 * \Syntax          : ErrorState_t STK_SetValue(STK_Value_t Copy_Value)
 * \Description     : Set the SysTick Top Value
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_Value          The Top Value of SysTick
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 *************************************************************************************************************************************/
ErrorState_t STK_SetValue(STK_Value_t Copy_Value)
{
    ErrorState_t Local_ErrorState=E_OK;
    if(Copy_Value>STK_MAX_VAL)
    {
        Local_ErrorState=E_NOK;
    }
    else
    {
        /*Load STK with value*/
        STK->LOAD=(u32)Copy_Value;
        /*Clear current*/
        STK->CURRENT=0;
    }
    return Local_ErrorState;
}

/***********************************************************************************************************************************
 * \Syntax          : void SysTick_Handler(void)
 * \Description     : The SysTick Handler
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *************************************************************************************************************************************/
void SysTick_Handler(void)
{
    if(STK_CallBackFunc!=NULL)
    {
        /*Invoke callback function*/
        STK_CallBackFunc();
    }
    /*Read COUNT flag to be cleared*/
    GET_BIT(STK->CTRL,STK_COUNT);
}

/**********************************************************************************************************************
 *  END OF FILE: STK_Program.c
 *********************************************************************************************************************/
