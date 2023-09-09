//*****************************************************************************
//
// Startup code for use with TI's Code Composer Studio.
//
// Copyright (c) 2011-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

#include <stdint.h>

//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
void Default_Handler(void);

void ResetISR(void);                               
static void NmiSR(void);                           
static void FaultISR(void);
void GPIOA_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOB_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOC_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOD_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOE_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOF_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void MemManage_Handler(void)                      __attribute__ ((weak, alias ("Default_Handler")));
void BusFault_Handler(void)                      __attribute__ ((weak, alias ("Default_Handler")));
void UsageFault_Handler(void)                     __attribute__ ((weak, alias ("Default_Handler")));
void SVC_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void DebugMon_Handler(void)                       __attribute__ ((weak, alias ("Default_Handler")));
void PendSV_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void SysTick_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void GPIOA_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOB_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOC_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOD_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOE_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void UART0_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void UART1_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void SSI0_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void I2C0_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void PMW0_FAULT_Handler(void)                     __attribute__ ((weak, alias ("Default_Handler")));
void PWM0_0_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void PWM0_1_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void PWM0_2_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void QEI0_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void ADC0SS0_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void ADC0SS1_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void ADC0SS2_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void ADC0SS3_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void WDT0_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void TIMER0A_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void TIMER0B_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void TIMER1A_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void TIMER1B_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void TIMER2A_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void TIMER2B_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void COMP0_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void COMP1_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void COMP2_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void SYSCTL_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void FLASH_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOF_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOG_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOH_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void UART2_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void SSI1_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void TIMER3A_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void TIMER3B_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void I2C1_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void QEI1_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void CAN0_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void CAN1_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void CAN2_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void HIB_Handler(void)                            __attribute__ ((weak, alias ("Default_Handler")));
void USB0_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void PWM0_3_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void UDMA_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void UDMAERR_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void ADC1SS0_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void ADC1SS1_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void ADC1SS2_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void ADC1SS3_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void GPIOJ_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOK_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOL_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void SSI2_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void SSI3_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void UART3_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void UART4_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void UART5_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void UART6_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void UART7_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void I2C2_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void I2C3_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void TIMER4A_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void TIMER4B_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void TIMER5A_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void TIMER5B_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void WTIMER0A_Handler(void)                       __attribute__ ((weak, alias ("Default_Handler")));
void WTIMER0B_Handler(void)                       __attribute__ ((weak, alias ("Default_Handler")));
void WTIMER1A_Handler(void)                       __attribute__ ((weak, alias ("Default_Handler")));
void WTIMER1B_Handler(void)                       __attribute__ ((weak, alias ("Default_Handler")));
void WTIMER2A_Handler(void)                       __attribute__ ((weak, alias ("Default_Handler")));
void WTIMER2B_Handler(void)                       __attribute__ ((weak, alias ("Default_Handler")));
void WTIMER3A_Handler(void)                       __attribute__ ((weak, alias ("Default_Handler")));
void WTIMER3B_Handler(void)                       __attribute__ ((weak, alias ("Default_Handler")));
void WTIMER4A_Handler(void)                       __attribute__ ((weak, alias ("Default_Handler")));
void WTIMER4B_Handler(void)                       __attribute__ ((weak, alias ("Default_Handler")));
void WTIMER5A_Handler(void)                       __attribute__ ((weak, alias ("Default_Handler")));
void WTIMER5B_Handler(void)                       __attribute__ ((weak, alias ("Default_Handler")));
void FPU_Handler(void)                            __attribute__ ((weak, alias ("Default_Handler")));
void I2C4_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void I2C5_Handler(void)                           __attribute__ ((weak, alias ("Default_Handler")));
void GPIOM_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPION_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void QEI2_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOP0_Handler(void)                        __attribute__ ((weak, alias ("Default_Handler")));
void GPIOP1_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOP2_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOP3_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOP4_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOP5_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOP6_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOP7_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOQ0_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOQ1_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOQ2_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOQ3_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOQ4_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOQ5_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOQ6_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOQ7_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void GPIOR_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void GPIOS_Handler(void)                          __attribute__ ((weak, alias ("Default_Handler")));
void PMW1_0_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void PWM1_1_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void PWM1_2_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void PWM1_3_Handler(void)                         __attribute__ ((weak, alias ("Default_Handler")));
void PWM1_FAULT_Handler(void)                     __attribute__ ((weak, alias ("Default_Handler")));
                                                  
//*****************************************************************************
//
// External declaration for the reset handler that is to be called when the
// processor is started
//
//*****************************************************************************
extern void _c_int00(void);

//*****************************************************************************
//
// Linker variable that marks the top of the stack.
//
//*****************************************************************************
extern uint32_t __STACK_TOP;

//*****************************************************************************
//
// External declarations for the interrupt handlers used by the application.
//
//*****************************************************************************
// To be added by user

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000 or at the start of
// the program if located at a start address other than 0.
//
//*****************************************************************************
#pragma DATA_SECTION(g_pfnVectors, ".intvecs")
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((uint32_t)&__STACK_TOP),
                                            // The initial stack pointer
    ResetISR,                               // The reset handler
    NmiSR,                                  // The NMI handler
    FaultISR,                               // The hard fault handler
    MemManage_Handler,                      // The MPU fault handler
    BusFault_Handler,                      	// The bus fault handler
    UsageFault_Handler,                     // The usage fault handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    SVC_Handler,                      		// SVCall handler
    DebugMon_Handler,                       // Debug monitor handler
    0,                                      // Reserved
    PendSV_Handler,                     	// The PendSV handler
    SysTick_Handler,                      	// The SysTick handler
    GPIOA_Handler,                          // GPIO Port A
    GPIOB_Handler,                          // GPIO Port B
    GPIOC_Handler,                          // GPIO Port C
    GPIOD_Handler,                          // GPIO Port D
    GPIOE_Handler,                          // GPIO Port E
    UART0_Handler,                      	// UART0 Rx and Tx
    UART1_Handler,                      	// UART1 Rx and Tx
    SSI0_Handler,                      		// SSI0 Rx and Tx
    I2C0_Handler,                      		// I2C0 Master and Slave
    PMW0_FAULT_Handler,                     // PWM Fault
    PWM0_0_Handler,                      	// PWM Generator 0
    PWM0_1_Handler,                      	// PWM Generator 1
    PWM0_2_Handler,                      	// PWM Generator 2
    QEI0_Handler,                      		// Quadrature Encoder 0
    ADC0SS0_Handler,                      	// ADC Sequence 0
    ADC0SS1_Handler,                      	// ADC Sequence 1
    ADC0SS2_Handler,                      	// ADC Sequence 2
    ADC0SS3_Handler,                      	// ADC Sequence 3
    WDT0_Handler,                      		// Watchdog timer
    TIMER0A_Handler,                      	// Timer 0 subtimer A
    TIMER0B_Handler,                      	// Timer 0 subtimer B
    TIMER1A_Handler,                      	// Timer 1 subtimer A
    TIMER1B_Handler,                      	// Timer 1 subtimer B
    TIMER2A_Handler,                      	// Timer 2 subtimer A
    TIMER2B_Handler,                      	// Timer 2 subtimer B
    COMP0_Handler,                      	// Analog Comparator 0
    COMP1_Handler,                      	// Analog Comparator 1
    COMP2_Handler,                      	// Analog Comparator 2
    SYSCTL_Handler,                      	// System Control (PLL, OSC, BO)
    FLASH_Handler,                      	// FLASH Control
    GPIOF_Handler,                       	// GPIO Port F
    GPIOG_Handler,                      	// GPIO Port G
    GPIOH_Handler,                      	// GPIO Port H
    UART2_Handler,                      	// UART2 Rx and Tx
    SSI1_Handler,                      		// SSI1 Rx and Tx
    TIMER3A_Handler,                      	// Timer 3 subtimer A
    TIMER3B_Handler,                      	// Timer 3 subtimer B
    I2C1_Handler,                      		// I2C1 Master and Slave
    QEI1_Handler,                      		// Quadrature Encoder 1
    CAN0_Handler,                      		// CAN0
    CAN1_Handler,                      		// CAN1
    CAN2_Handler,                       	// Reserved
    0,                                      // Reserved
    HIB_Handler,                      		// Hibernate
    USB0_Handler,                     	 	// USB0
    PWM0_3_Handler,                      	// PWM Generator 3
    UDMA_Handler,                      		// uDMA Software Transfer
    UDMAERR_Handler,                      	// uDMA Error
    ADC1SS0_Handler,                      	// ADC1 Sequence 0
    ADC1SS1_Handler,                      	// ADC1 Sequence 1
    ADC1SS2_Handler,                      	// ADC1 Sequence 2
    ADC1SS3_Handler,                      	// ADC1 Sequence 3
    0,                                      // Reserved
    0,                                      // Reserved
    GPIOJ_Handler,                      	// GPIO Port J
    GPIOK_Handler,                      	// GPIO Port K
    GPIOL_Handler,                      	// GPIO Port L
    SSI2_Handler,                      		// SSI2 Rx and Tx
    SSI3_Handler,                      		// SSI3 Rx and Tx
    UART3_Handler,                      	// UART3 Rx and Tx
    UART4_Handler,                      	// UART4 Rx and Tx
    UART5_Handler,                      	// UART5 Rx and Tx
    UART6_Handler,                      	// UART6 Rx and Tx
    UART7_Handler,                      	// UART7 Rx and Tx
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    I2C2_Handler,                      		// I2C2 Master and Slave
    I2C3_Handler,                      		// I2C3 Master and Slave
    TIMER4A_Handler,                      	// Timer 4 subtimer A
    TIMER4B_Handler,                      	// Timer 4 subtimer B
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    TIMER5A_Handler,                      	// Timer 5 subtimer A
    TIMER5B_Handler,                      	// Timer 5 subtimer B
    WTIMER0A_Handler,                      	// Wide Timer 0 subtimer A
    WTIMER0B_Handler,                      	// Wide Timer 0 subtimer B
    WTIMER1A_Handler,                      	// Wide Timer 1 subtimer A
    WTIMER1B_Handler,                      	// Wide Timer 1 subtimer B
    WTIMER2A_Handler,                      	// Wide Timer 2 subtimer A
    WTIMER2B_Handler,                      	// Wide Timer 2 subtimer B
    WTIMER3A_Handler,                      	// Wide Timer 3 subtimer A
    WTIMER3B_Handler,                      	// Wide Timer 3 subtimer B
    WTIMER4A_Handler,                      	// Wide Timer 4 subtimer A
    WTIMER4B_Handler,                      	// Wide Timer 4 subtimer B
    WTIMER5A_Handler,                      	// Wide Timer 5 subtimer A
    WTIMER5B_Handler,                      	// Wide Timer 5 subtimer B
    FPU_Handler,                      		// FPU
    0,                                      // Reserved
    0,                                      // Reserved
    I2C4_Handler,                      		// I2C4 Master and Slave
    I2C5_Handler,                      		// I2C5 Master and Slave
    GPIOM_Handler,                      	// GPIO Port M
    GPION_Handler,                      	// GPIO Port N
    QEI2_Handler,                      		// Quadrature Encoder 2
    0,                                      // Reserved
    0,                                      // Reserved
    GPIOP0_Handler,                      	// GPIO Port P (Summary or P0)
    GPIOP1_Handler,                      	// GPIO Port P1
    GPIOP2_Handler,                      	// GPIO Port P2
    GPIOP3_Handler,                      	// GPIO Port P3
    GPIOP4_Handler,                      	// GPIO Port P4
    GPIOP5_Handler,                      	// GPIO Port P5
    GPIOP6_Handler,                      	// GPIO Port P6
    GPIOP7_Handler,                      	// GPIO Port P7
    GPIOQ0_Handler,                      	// GPIO Port Q (Summary or Q0)
    GPIOQ1_Handler,                      	// GPIO Port Q1
    GPIOQ2_Handler,                      	// GPIO Port Q2
    GPIOQ3_Handler,                      	// GPIO Port Q3
    GPIOQ4_Handler,                      	// GPIO Port Q4
    GPIOQ5_Handler,                      	// GPIO Port Q5
    GPIOQ6_Handler,                      	// GPIO Port Q6
    GPIOQ7_Handler,                      	// GPIO Port Q7
    GPIOR_Handler,                      	// GPIO Port R
    GPIOS_Handler,                      	// GPIO Port S
    PMW1_0_Handler,                      	// PWM 1 Generator 0
    PWM1_1_Handler,                      	// PWM 1 Generator 1
    PWM1_2_Handler,                      	// PWM 1 Generator 2
    PWM1_3_Handler,                      	// PWM 1 Generator 3
    PWM1_FAULT_Handler                      // PWM 1 Fault
};

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
void
ResetISR(void)
{
    //
    // Jump to the CCS C initialization routine.  This will enable the
    // floating-point unit as well, so that does not need to be done here.
    //
    __asm("    .global _c_int00\n"
          "    b.w     _c_int00");
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
static void
NmiSR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
FaultISR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
void Default_Handler(void)
{
	//
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}
