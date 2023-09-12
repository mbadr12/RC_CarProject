/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr - Adham El-Srougy- Hazem Magdy - Omar Ayman
 *	   	   File:  RC_Car.c
 *		  Layer:  App
 *       Module:  Car Application
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../LIB/Std_Types.h"
#include "../LIB/Bit_Math.h"

#include "../HAL/LCD/LCD.h"
#include "../HAL/LDR/LDR.h"
#include "../HAL/Ultrasonic/Ultrasonic.h"
#include "../HAL/Temperature/Temperature.h"
#include "../HAL/Switch/Switch.h"
#include "../HAL/Motor/Motor.h"

#include "../Service/Scheduler/Scheduler.h"

#include "RC_Car.h"

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static u8 APP_LCDX=0,APP_LCDY=0;
static LCD_Config_t APP_LCD={.ControlPins={GPIO_PIN0,GPIO_PIN7,GPIO_PIN1},.ControlPinsPorts={GPIO_PORTB,GPIO_PORTF,GPIO_PORTB},.Cursor=LCD_NO_CURSOR,
                             .DataPins={GPIO_PIN2,GPIO_PIN3,GPIO_PIN4,GPIO_PIN5},.Font=LCD_5_8_FONT,.LinesNum=LCD_TWO_LINES,.Mode=LCD_4BIT_MODE,
                             .XPosition=&APP_LCDX,.Yposition=&APP_LCDY,.DataPinsPorts={GPIO_PORTB,GPIO_PORTB,GPIO_PORTB,GPIO_PORTB}};
static u64 APP_Distance=0;

static Flag_State_t APP_UltrasonicGFlag=FLAG_LOW;

static Flag_State_t APP_Sw1Flag=FLAG_LOW;

static Flag_State_t APP_Sw2Flag=FLAG_LOW;

static Flag_State_t APP_StartFlag=FLAG_LOW;

static Flag_State_t APP_CarMoving=FLAG_LOW;

static u8 APP_CarTimer=0;

static u32 APP_LDRArr[2]={0};

static u32 APP_LDRDifference=0;

static Flag_State_t APP_AvoidFlag=FLAG_LOW;

static Flag_State_t APP_LDRFlag=FLAG_LOW;

static Flag_State_t APP_StopFlag=FLAG_LOW;

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/


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

void Ultrasonic_Notifaction(void)
{
    APP_UltrasonicGFlag=FLAG_HIGH;
}

void Switch1_Notification(void)
{
    /*check if the other button Was pressed or not*/
    if(APP_Sw1Flag==FLAG_HIGH)
    {
        /* Do Nothing */
    }
    /*check if the other button was pressed or not*/
    else if(APP_Sw2Flag==FLAG_HIGH)
    {
        /*Lower all Flags*/
        APP_StartFlag=FLAG_LOW;
        APP_CarMoving=FLAG_LOW;
        APP_Sw1Flag=FLAG_LOW;
        APP_Sw2Flag=FLAG_LOW;
    }
    else
    {
        /*Raise the system start flag*/
        APP_StartFlag=FLAG_HIGH;
        /*Raise flag once the button Pressed*/
        APP_Sw1Flag=FLAG_HIGH;
    }
}

void Switch2_Notification(void)
{
    /*check if the other button Was pressed or not*/
    if(APP_Sw2Flag==FLAG_HIGH)
    {
        /* Do Nothing */
    }
    /*check if the other button was pressed or not*/
    else if(APP_Sw1Flag==FLAG_HIGH)
    {
        APP_StartFlag=FLAG_LOW;
        APP_CarMoving=FLAG_LOW;
        APP_Sw1Flag=FLAG_LOW;
        APP_Sw2Flag=FLAG_LOW;
        APP_StopFlag=FLAG_LOW;
    }
    else
    {
        APP_StartFlag=FLAG_HIGH;
        /*Raise flag once the button Pressed*/
        APP_Sw2Flag=FLAG_HIGH;
    }
}

void CarStart_Task(void)
{
    if(APP_StartFlag==1)
    {
        Motor_Start();
        APP_StartFlag=FLAG_LOW;
        APP_CarMoving=FLAG_HIGH;
    }
}

void CarStop_Task(void)
{
    if((APP_CarTimer>=60) || ((APP_CarMoving==FLAG_LOW) && (APP_StopFlag==FLAG_LOW)))
    {
        Motor_Stop();
        APP_StopFlag=FLAG_HIGH;
        APP_CarTimer=0;
        APP_StartFlag=FLAG_LOW;
        APP_CarMoving=FLAG_LOW;
        APP_Sw1Flag=FLAG_LOW;
        APP_Sw2Flag=FLAG_LOW;
    }
}
void UltraSonic_Task(void)
{
    if(APP_UltrasonicGFlag==FLAG_HIGH)
    {
        ultrasonic_distance(&APP_Distance, Ultrasonic_Notifaction);
        APP_UltrasonicGFlag=FLAG_LOW;
    }
}

void Watch_Task(void)
{
    if(APP_CarMoving==FLAG_HIGH)
    {
        APP_CarTimer++;
    }
}

void Temperature_Task(void)
{
    static u8 Local_Temp=0;
    /*Read the Temperature*/
    Local_Temp=Temp_Send_Read();
    LCD_GoToXY(&APP_LCD, 5, 0);
    /*Send Temperature to LCD*/
    LCD_WriteNumber(&APP_LCD, (s64)Local_Temp);
}

void ldr_swing_car(void)
{
    if(APP_CarMoving==FLAG_HIGH)
    {
        LDR_Read(APP_LDRArr);
        if(APP_LDRArr[0]>=APP_LDRArr[1])
        {
            APP_LDRDifference=APP_LDRArr[0]-APP_LDRArr[1];
            APP_LDRFlag=FLAG_HIGH;
        }
        else
        {
            APP_LDRDifference=APP_LDRArr[0]-APP_LDRArr[1];
        }
        //TODO: :  Adham Go to Car.h and set the MAcro with the value you want
        if(APP_LDRDifference>=LDR_DIFF)
        {
            if(APP_LDRFlag==FLAG_HIGH)
            {
                //TODO: :  Adham Implement swing Mechanism Case 0 is Greater
            }
            else
            {
                //TODO: :  Adham Implement swing Mechanism Case 1 is Greater
            }
        }
        else
        {
            /*MISRA*/
        }
    }
    else
    {
        /*MISRA*/
    }
}

void LCD_Distancedisplay(void)
{
    static u64 Local_Distance=0;
    if(Local_Distance != APP_Distance)
    {
        //TODO: : Adham choose the place that you will print the Distance on it
        LCD_GoToXY(&APP_LCD, 1, 0);
        LCD_WriteNumber(&APP_LCD, (s64)APP_Distance);
        Local_Distance=APP_Distance;
    }
    else
    {
        /*MISRA*/
    }
}

void LCD_LDRDisplay(void)
{
    static u32 Local_LDRDifference=0;
    if(Local_LDRDifference!=APP_LDRDifference)
    {
        //TODO: : Adham choose the place that you will print the LDR difference on it
        LCD_GoToXY(&APP_LCD, 1, 0);
        LCD_WriteNumber(&APP_LCD, (s64)APP_LDRDifference);
        Local_LDRDifference=APP_LDRDifference;
    }
}

void avoid_obstacles(void)
{
    if(APP_CarMoving==FLAG_HIGH)
    {
        //TODO: :  Adham Go and Check the Minimum Distance in car.h and check the behavior of this Task
        if(APP_Distance<=MIN_DISTANCE)
        {
            /*Its Time to avoid obstacle*/
            APP_AvoidFlag=FLAG_HIGH;
        }
        if(APP_AvoidFlag==FLAG_HIGH)
        {
            if((APP_Distance>=30)&&(APP_Distance<=50))
            {
                Motor_Set_Direction(Motor_Left_Forward);
                Motor_Set_Direction(Motor_Right_Forward);
                Motor_Set_Speed(5, Right_Motors);
            }
            else if(APP_Distance>50)
            {
                APP_AvoidFlag=FLAG_LOW;
            }
            else
            {
                Motor_Set_Direction(Motor_Left_Reverse);
                Motor_Set_Direction(Motor_Right_Reverse);
            }
        }
    }
    else
    {
        /*MISRA*/
    }
}

void LCD_TimeDiplay(void)
{
    //TODO: : Adham choose the place that you will print the elapsed Time on it
    LCD_GoToXY(&APP_LCD, 1, 0);
    LCD_WriteNumber(&APP_LCD, (s64)APP_CarTimer);
}

void CAR_Init(void)
{
    EXTI_Config_t Local_Switch1={.Port=EXTI_PORTF, .Pin=EXTI_PIN0,.TrigTye=EXTI_RAISING_EDGE};
    EXTI_Config_t Local_Switch2={.Port=EXTI_PORTF, .Pin=EXTI_PIN4,.TrigTye=EXTI_RAISING_EDGE};
    /*Initialize the system Hardware*/
    LCD_Init(&APP_LCD);
    Ultra_Sonic_init();
    LDR_Init();
    Temperature_Init();
    Motor_Init();
    Switch_Init(GPIO_PORTF, GPIO_PIN0, GPIO_PIN_PULLUP);
    Switch_Init(GPIO_PORTF, GPIO_PIN4, GPIO_PIN_PULLUP);
    LCD_SendString(&APP_LCD, "Temp ");
    LCD_GoToXY(&APP_LCD, 7, 0);
    LCD_SendChar(&APP_LCD, 248);
    LCD_SendChar(&APP_LCD, 'C');
    LCD_GoToXY(&APP_LCD, 10, 0);
    LCD_SendString(&APP_LCD, "T ");
    Switch_IntConfig(&Local_Switch1, Switch1_Notification);
    Switch_IntConfig(&Local_Switch2, Switch2_Notification);
    /*Create ultrasonic task to get reading every 100 MS*/
    Create_Task(UltraSonic_Task, 2, 0, 0);
    /*Create LDR difference Display task to be Displayed every 150 MS*/
    Create_Task(LCD_LDRDisplay, 3, 1, 7);
    /*Create Time elapsed Display task to be Displayed every 1 S*/
    Create_Task(LCD_TimeDiplay, 20, 0, 8);
    /*Create Distance Display task to be Displayed every 100 MS*/
    Create_Task(LCD_Distancedisplay, 2, 1, 6);
    /*Create Avoid obstacles task to be executed every 100 MS*/
    Create_Task(avoid_obstacles, 2, 0, 1);
    /*Create LDR swing task to be executed every 150 MS*/
    Create_Task(ldr_swing_car, 3, 0, 5);
    /*Create Temperature Task to be executed every 4 S*/
    Create_Task(Temperature_Task, 80, 2, 9);
    /*Create Car start Task to be executed every 50 MS*/
    Create_Task(CarStart_Task, 1, 0, 2);
    /*Create Car Stop Task to be executed every 50 MS*/
    Create_Task(CarStop_Task, 1, 0, 3);
    /*Create Watch Task to calculate the elapsed time every 1 S*/
    Create_Task(Watch_Task, 20, 0, 4);
    /*Start scheduler*/
    Tasks_Sceduler();
}

/**********************************************************************************************************************
 *  END OF FILE: RC_Car_Program.c
 *********************************************************************************************************************/
