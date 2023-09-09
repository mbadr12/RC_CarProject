/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  RCC_Program.c
 *		  Layer:  MCAL
 *       Module:  RCC
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "TM4C123xx.h"
#include "Bit_Math.h"

#include "RCC.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************************************************************
 * \Syntax          : ErrorState_t RCC_SetPrephralClockState(RCC_Prph_t Copy_Peripheral, RCC_PrphClkState_t Copy_ClockState)
 * \Description     : Set the peripheral clock state
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_Peripheral   The peripheral to control its clock
 *                    Copy_ClockState   The state to be set
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 ******************************************************************************************************************************/
ErrorState_t RCC_SetPrephralClockState(RCC_Prph_t Copy_Peripheral, RCC_PrphClkState_t Copy_ClockState)
{
    ErrorState_t Local_ErrorState=E_OK;
    u8 Local_RegNum=Copy_Peripheral/8;
    u8 Local_BitNum=Copy_Peripheral%8;
    if((Copy_Peripheral>RCC_wGPTM5) || (Copy_ClockState>RCC_CLK_ENABLE))
    {
        Local_ErrorState=E_WRONG_OPTION;
    }
    else
    {
        INSERT_BIT(SYSCRL->RCGC[Local_RegNum],Local_BitNum,Copy_ClockState);
    }
    return Local_ErrorState;
}

/**************************************************************************************************************************************
 * \Syntax          : ErrorState_t RCC_SetPrephralClockStateSleepMode(RCC_Prph_t Copy_Peripheral, RCC_PrphClkState_t Copy_ClockState)
 * \Description     : Set the peripheral clock state in sleep mode
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_Peripheral   The peripheral to control its clock
 *                    Copy_ClockState   The state to be set
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 **************************************************************************************************************************************/
ErrorState_t RCC_SetPrephralClockStateSleepMode(RCC_Prph_t Copy_Peripheral, RCC_PrphClkState_t Copy_ClockState)
{
    ErrorState_t Local_ErrorState=E_OK;
    u8 Local_RegNum=Copy_Peripheral/8;
    u8 Local_BitNum=Copy_Peripheral%8;
    if((Copy_Peripheral>RCC_wGPTM5) || (Copy_ClockState>RCC_CLK_ENABLE))
    {
        Local_ErrorState=E_WRONG_OPTION;
    }
    else
    {
        INSERT_BIT(SYSCRL->SCGC[Local_RegNum],Local_BitNum,Copy_ClockState);
    }
    return Local_ErrorState;
}

/**************************************************************************************************************************************
 * \Syntax          : ErrorState_t RCC_SetPrephralClockStateDeepSleepMode(RCC_Prph_t Copy_Peripheral, RCC_PrphClkState_t Copy_ClockState)
 * \Description     : Set the peripheral clock state in Deep sleep mode
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_Peripheral   The peripheral to control its clock
 *                    Copy_ClockState   The state to be set
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 **************************************************************************************************************************************/
ErrorState_t RCC_SetPrephralClockStateDeepSleepMode(RCC_Prph_t Copy_Peripheral, RCC_PrphClkState_t Copy_ClockState)
{
    ErrorState_t Local_ErrorState=E_OK;
    u8 Local_RegNum=Copy_Peripheral/8;
    u8 Local_BitNum=Copy_Peripheral%8;
    if((Copy_Peripheral>RCC_wGPTM5) || (Copy_ClockState>RCC_CLK_ENABLE))
    {
        Local_ErrorState=E_WRONG_OPTION;
    }
    else
    {
        INSERT_BIT(SYSCRL->DCGC[Local_RegNum],Local_BitNum,Copy_ClockState);
    }
    return Local_ErrorState;
}

/**************************************************************************************************************************************
 * \Syntax          : ErrorState_t RCC_IsPeripheralPresent(RCC_Prph_t Copy_Peripheral, bool* Copy_IsPersent)
 * \Description     : Check if the peripheral present or not
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : Copy_Peripheral   The peripheral to control its clock
 * \Parameters (out): Copy_IsPersent    The state of Peripheral
 * \Return value:   : ErrorState_t
 **************************************************************************************************************************************/
ErrorState_t RCC_IsPeripheralPresent(RCC_Prph_t Copy_Peripheral, bool* Copy_IsPersent)
{
    ErrorState_t Local_ErrorState=E_OK;
    u8 Local_RegNum=Copy_Peripheral/8;
    u8 Local_BitNum=Copy_Peripheral%8;
    if((Copy_Peripheral>RCC_wGPTM5) || (Copy_IsPersent == NULL))
    {
        Local_ErrorState=E_WRONG_OPTION;
    }
    else
    {
        *Copy_IsPersent=(bool)GET_BIT(SYSCRL->PP[Local_RegNum],Local_BitNum);
    }
    return Local_ErrorState;
}

/**************************************************************************************************************************************
 * \Syntax          : ErrorState_t RCC_PeripheralSWReset(RCC_Prph_t Copy_Peripheral)
 * \Description     : Do software reset on a peripheral
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_Peripheral   The peripheral to control its clock
 * \Parameters (out): None
 * \Return value:   : ErrorState_t
 **************************************************************************************************************************************/
ErrorState_t RCC_PeripheralSWReset(RCC_Prph_t Copy_Peripheral)
{
    {
        ErrorState_t Local_ErrorState=E_OK;
        u8 Local_RegNum=Copy_Peripheral/8;
        u8 Local_BitNum=Copy_Peripheral%8;
        if(Copy_Peripheral>RCC_wGPTM5)
        {
            Local_ErrorState=E_WRONG_OPTION;
        }
        else
        {
            SET_BIT(SYSCRL->SR[Local_RegNum],Local_BitNum);
            CLR_BIT(SYSCRL->SR[Local_RegNum],Local_BitNum);
        }
        return Local_ErrorState;
    }
}

/**********************************************************************************************************************
 *  END OF FILE: RCC_Program.c
 *********************************************************************************************************************/
