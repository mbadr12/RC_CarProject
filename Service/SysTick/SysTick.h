/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  STK_interface.h
 *		  Layer:  MCAL
 *       Module:  STK
 *		Version:  1.00
 *	
 *  Description:  interfaces of STK
 *  
 *********************************************************************************************************************/
#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
    STK_INT_OS_DIV_4=0,
    STK_SYS_CLOCK
}STK_ClcSource_t;

typedef enum
{
    STK_INT_DISABLED=0,
    STK_INT_ENABLED
}STK_IntState_t;

typedef u32 STK_Value_t;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

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
ErrorState_t STK_Init(STK_ClcSource_t Copy_ClockSource, STK_Value_t Copy_Value, STK_IntState_t Copy_IntState);

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
ErrorState_t STK_SetIntState(STK_IntState_t Copy_IntState);

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
ErrorState_t STK_SetCallBack(void (*Copy_CallBackFunc)(void));

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
ErrorState_t STK_SetValue(STK_Value_t Copy_Value);

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
void STK_Delyms(u32 Copy_Delayms);

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define STK_CLK_SRC     2UL

#define STK_COUNT       16UL

#define STK_ENABLE      0UL

#define STK_INT_EN       1UL

#define STK_FACTOR      4000UL

#define STK_MAX_VAL     0xffffffUL
 
#endif  /* STK_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: STK_interface.h
 *********************************************************************************************************************/
