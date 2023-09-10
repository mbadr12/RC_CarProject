/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  RCC_interface.h
 *		  Layer:  MCAL
 *       Module:  RCC
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
	RCC_WTD1=0,
	RCC_WTD2,
	RCC_GPTM0=8,
	RCC_GPTM1,
	RCC_GPTM2,
	RCC_GPTM3,
	RCC_GPTM4,
	RCC_GPTM5,
	RCC_GPIOA=16,
	RCC_GPIOB,
	RCC_GPIOC,
	RCC_GPIOD,
	RCC_GPIOE,
	RCC_GPIOF,
	RCC_UDMA=24,
	RCC_HIB=40,
	RCC_UART0=48,
	RCC_UART1,
	RCC_UART2,
	RCC_UART3,
	RCC_UART4,
	RCC_UART5,
	RCC_UART6,
	RCC_UART7,
	RCC_SSI0,
	RCC_SSI1,
	RCC_SSI2,
	RCC_SSI3,
	RCC_I2C0=64,
	RCC_I2C1,
	RCC_I2C2,
	RCC_I2C3,
	RCC_USB=80,
	RCC_CAN0=104,
	RCC_CAN1,
	RCC_ADC0=112,
	RCC_ADC1,
	RCC_ACMP=120,
	RCC_PWM0=128,
	RCC_PWM1,
	RCC_QEI0=136,
	RCC_QEI1,
	RCC_EEPROM=176,
	RCC_wGPTM0=184,
	RCC_wGPTM1,
	RCC_wGPTM2,
	RCC_wGPTM3,
	RCC_wGPTM4,
	RCC_wGPTM5
}RCC_Prph_t;

typedef enum
{
	RCC_CLK_DISABLE=0,
	RCC_CLK_ENABLE
}RCC_PrphClkState_t;
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
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
ErrorState_t RCC_SetPrephralClockState(RCC_Prph_t Copy_Peripheral, RCC_PrphClkState_t Copy_ClockState);

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
ErrorState_t RCC_SetPrephralClockStateSleepMode(RCC_Prph_t Copy_Peripheral, RCC_PrphClkState_t Copy_ClockState);

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
ErrorState_t RCC_SetPrephralClockStateDeepSleepMode(RCC_Prph_t Copy_Peripheral, RCC_PrphClkState_t Copy_ClockState);

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
ErrorState_t RCC_IsPeripheralPresent(RCC_Prph_t Copy_Peripheral, bool* Copy_IsPersent);

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
ErrorState_t RCC_PeripheralSWReset(RCC_Prph_t Copy_Peripheral);

/**************************************************************************************************************************************
 * \Syntax          : void RCC_ConfigureClock(u8 Clock_Freq, u8 PWM_Config)
 * \Description     : Set the System Clock and PWM clock Configuration
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Clock_Freq   		The System Frequency
 *                    PWM_Config   		The PWM Configuration
 * \Parameters (out): None
 * \Return value:   : void
 **************************************************************************************************************************************/
void RCC_ConfigureClock(u8 Clock_Freq, u8 PWM_Config);

#endif  /* RCC_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: RCC_interface.h
 *********************************************************************************************************************/

