/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  NVIC_interface.h
 *		  Layer:  MCAL
 *       Module:  NVIC
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
	NVIC_PORTA_IRQ=0,
	NVIC_PORTB_IRQ,
	NVIC_PORTC_IRQ,
	NVIC_PORTD_IRQ,
	NVIC_PORTE_IRQ,
	NVIC_UART0_IRQ,
	NVIC_UART1_IRQ,
	NVIC_SSI0_IRQ,
	NVIC_I2C0_IRQ,
	NVIC_PWM0FAULT_IRQ,
	NVIC_PWM0GENERATOR0_IRQ,
	NVIC_PWM0GENERATOR1_IRQ,
	NVIC_PWM0GENERATOR2_IRQ,
	NVIC_QEI0_IRQ,
	NVIC_ADC0SEQUENCE0_IRQ,
	NVIC_ADC0SEQUENCE1_IRQ,
	NVIC_ADC0SEQUENCE2_IRQ,
	NVIC_ADC0SEQUENCE3_IRQ,
	NVIC_WATCHDOGTIMERS0_1_IRQ,
	NVIC_TIMER0A_16_32_IRQ,
	NVIC_TIMER0B_16_32_IRQ,
	NVIC_TIMER1A_16_32_IRQ,
	NVIC_TIMER1B_16_32_IRQ,
	NVIC_TIMER2A_16_32_IRQ,
	NVIC_TIMER2B_16_32_IRQ,
	NVIC_ANALOG_COMPARTOR0_IRQ,
	NVIC_ANALOG_COMPARTOR1_IRQ,
	NVIC_SYSCTRL_IRQ=28,
	NVIC_FLASH_EEPROM_CTRL_IRQ,
	NVIC_PORTF_IRQ,
	NVIC_UART2_IRQ=33,
	NVIC_SSI1_IRQ,
	NVIC_TIMER3A_16_32_IRQ,
	NVIC_TIMER3B_16_32_IRQ,
	NVIC_I2C1_IRQ,
	NVIC_QEI1_IRQ,
	NVIC_CAN0_IRQ,
	NVIC_CAN1_IRQ,
	NVIC_HIB_IRQ=43,
	NVIC_USB0_IRQ,
	NVIC_PWM0_GENERATOR3_IRQ,
	NVIC_UDMA_IRQ,
	NVIC_UDMAERR_IRQ,
	NVIC_ADC1SEQUENCE0_IRQ,
	NVIC_ADC1SEQUENCE1_IRQ,
	NVIC_ADC1SEQUENCE2_IRQ,
	NVIC_ADC1SEQUENCE3_IRQ,
	NVIC_SSI2_IRQ=57,
	NVIC_SSI3_IRQ,
	NVIC_UART3_IRQ,
	NVIC_UART4_IRQ,
	NVIC_UART5_IRQ,
	NVIC_UART6_IRQ,
	NVIC_UART7_IRQ,
	NVIC_I2C2_IRQ=68,
	NVIC_I2C3_IRQ,
	NVIC_TIMER4A_16_32_IRQ,
	NVIC_TIMER4B_16_32_IRQ,
	NVIC_TIMER5A_16_32_IRQ=92,
	NVIC_TIMER5B_16_32_IRQ,
	NVIC_TIMER0A_32_64_IRQ,
	NVIC_TIMER0B_32_64_IRQ,
	NVIC_TIMER1A_32_64_IRQ,
	NVIC_TIMER1B_32_64_IRQ,
	NVIC_TIMER2A_32_64_IRQ,
	NVIC_TIMER2B_32_64_IRQ,
	NVIC_TIMER3A_32_64_IRQ,
	NVIC_TIMER3B_32_64_IRQ,
	NVIC_TIMER4A_32_64_IRQ,
	NVIC_TIMER4B_32_64_IRQ,
	NVIC_TIMER5A_32_64_IRQ,
	NVIC_TIMER5B_32_64_IRQ,
	NVIC_FPU_IRQ,
	NVIC_PMW1_GENERATOR0_IRQ=134,
	NVIC_PWM1_GENERATOR1_IRQ,
	NVIC_PWM1_GENERATOR2_IRQ,
	NVIC_PWM1_GENERATOR3_IRQ,
	NVIC_PWM1_FAULT_IRQ,
}NVIC_IRQ_t;

typedef enum
{
    NVIC_INT_DISABLE=0,
    NVIC_INT_ENABLE,
}NVIC_IntState_t;

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
ErrorState_t NVIC_SetInterruptState(NVIC_IRQ_t Copy_IRQ_n,NVIC_IntState_t Copy_State);

ErrorState_t NVIC_SetPendingFlag(NVIC_IRQ_t Copy_IRQ_n,NVIC_IntState_t Copy_State);

ErrorState_t NVIC_GetActiveFlag(NVIC_IRQ_t Copy_IRQ_n,NVIC_IntState_t* Copy_State);

#endif  /* NVIC_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: NVIC_interface.h
 *********************************************************************************************************************/
