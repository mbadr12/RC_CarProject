#include "LIB/Std_Types.h"
#include "HAL/Motor/Motor.h"

void Motor_Init(void)
{
    /* Enable GPIOA and GPIOE Clock */
    RCC_SetPrephralClockState(RCC_GPIOA, RCC_CLK_ENABLE);
    RCC_SetPrephralClockState(RCC_GPIOE, RCC_CLK_ENABLE);
    /* Configure PA4, PA5, PA6, PA7 as output pins and PE4, PE5 as PWM pins */
    GPIO_Config_t Init_GPIO[6] = { };
    Init_GPIO[0].Mode = GPIO_PIN_ALTFUNC;
    Init_GPIO[0].AltFuncNum = GPIO_ALTFUNC5;
    Init_GPIO[0].Port = GPIO_PORTE;
    Init_GPIO[0].Pin = GPIO_PIN4;
    Init_GPIO[0].PinPull = GPIO_PIN_FLOATING;
    Init_GPIO[1].Mode = GPIO_PIN_ALTFUNC;
    Init_GPIO[1].AltFuncNum = GPIO_ALTFUNC5;
    Init_GPIO[1].Port = GPIO_PORTE;
    Init_GPIO[1].Pin = GPIO_PIN5;
    Init_GPIO[1].PinPull = GPIO_PIN_FLOATING;
    Init_GPIO[2].Dir = GPIO_PIN_OUTPUT;
    Init_GPIO[2].Mode = GPIO_PIN_DIGITAL;
    Init_GPIO[2].Pin = GPIO_PIN4;
    Init_GPIO[2].Port = GPIO_PORTA;
    Init_GPIO[2].PinPull = GPIO_PIN_FLOATING;
    Init_GPIO[3].Dir = GPIO_PIN_OUTPUT;
    Init_GPIO[3].Mode = GPIO_PIN_DIGITAL;
    Init_GPIO[3].Pin = GPIO_PIN5;
    Init_GPIO[3].Port = GPIO_PORTA;
    Init_GPIO[3].PinPull = GPIO_PIN_FLOATING;
    Init_GPIO[4].Dir = GPIO_PIN_OUTPUT;
    Init_GPIO[4].Mode = GPIO_PIN_DIGITAL;
    Init_GPIO[4].Pin = GPIO_PIN6;
    Init_GPIO[4].Port = GPIO_PORTA;
    Init_GPIO[4].PinPull = GPIO_PIN_FLOATING;
    Init_GPIO[5].Dir = GPIO_PIN_OUTPUT;
    Init_GPIO[5].Mode = GPIO_PIN_DIGITAL;
    Init_GPIO[5].Pin = GPIO_PIN7;
    Init_GPIO[5].Port = GPIO_PORTA;
    Init_GPIO[5].PinPull = GPIO_PIN_FLOATING;
    GPIO_Init(Init_GPIO, 6U);
    /* Enable PWM1 Clock */
    RCC_SetPrephralClockState(RCC_PWM1, RCC_CLK_ENABLE);
    /* Configure PWM */
    PWM_InitTypeDef Init_PWM = { };
    Init_PWM.Channel = PWM_Channel_2;
    Init_PWM.Channel_Action_Zero = PWM_DRIVE_HIGH;
    Init_PWM.Channel_Action_CompADowm = PWM_DRIVE_LOW;
    PWM_Init(PWM1, &Init_PWM);
    Init_PWM.Channel = PWM_Channel_3;
    Init_PWM.Channel_Action_CompADowm = PWM_DO_NOTHING;
    Init_PWM.Channel_Action_CompBDowm = PWM_DRIVE_LOW;
    PWM_Init(PWM1, &Init_PWM);
    /* Right Side Motors Halt */
    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN4, GPIO_PIN_LOW);
    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN5, GPIO_PIN_LOW);
    /* Left Side Motors Halt */
    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN6, GPIO_PIN_LOW);
    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN7, GPIO_PIN_LOW);
    /* Set PWM Load Value For 100 Hz Operation */
    PWM_Set_Load(PWM1, PWM_Generator1, 2500U);
}

void Motor_Start(void)
{
    /* Set Direction of Motors to Front */
    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN4, GPIO_PIN_LOW);
    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN5, GPIO_PIN_HIGH);
    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN6, GPIO_PIN_LOW);
    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN7, GPIO_PIN_HIGH);
    /* Set Motor Speed to 40% */
    PWM_Set_Comp(PWM1, PWM_Channel_2, 1000U);
    PWM_Set_Comp(PWM1, PWM_Channel_3, 1000U);
    /* Start PWM Generators */
    PWM_Start(PWM1, PWM_Generator1);
    /* Enable PWM Output */
    PWM_Output_Enable(PWM1, PWM_Channel_2 | PWM_Channel_3);
}

void Motor_Set_Speed(uint16_t Speed, uint8_t Motors)
{
    Speed *= 25U;
    switch (Motors)
    {
    case Right_Motors:
        PWM_Set_Comp(PWM1, PWM_Channel_2, Speed);
        break;
    case Left_Motors:
        PWM_Set_Comp(PWM1, PWM_Channel_3, Speed);
        break;
    default:
        break;
    }
}

void Motor_Set_Direction(uint8_t Direction)
{
    switch (Direction)
    {
    case Motor_Right_Forward:
        GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN4, GPIO_PIN_LOW);
        GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN5, GPIO_PIN_HIGH);
        break;
    case Motor_Right_Reverse:
        GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN4, GPIO_PIN_HIGH);
        GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN5, GPIO_PIN_LOW);
        break;
    case Motor_Left_Forward:
        GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN6, GPIO_PIN_LOW);
        GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN7, GPIO_PIN_HIGH);
        break;
    case Motor_Left_Reverse:
        GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN6, GPIO_PIN_HIGH);
        GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN7, GPIO_PIN_LOW);
        break;
    default:
        break;
    }
}

void Motor_Stop(void)
{
    /* Right Side Motors Halt */
    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN4, GPIO_PIN_LOW);
    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN5, GPIO_PIN_LOW);
    /* Left Side Motors Halt */
    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN6, GPIO_PIN_LOW);
    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN7, GPIO_PIN_LOW);
}
