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
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : void Ultrasonic_Notifaction(void)
 * \Description     : Notification Function of the ultrasonic reading completion
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void Ultrasonic_Notifaction(void)
{
    APP_UltrasonicGFlag=FLAG_HIGH;
}

/******************************************************************************
 * \Syntax          : void Switch1_Notification(void)
 * \Description     : Notification Function of the Pressing Switch 1
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
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

/******************************************************************************
 * \Syntax          : void Switch2_Notification(void)
 * \Description     : Notification Function of the Pressing Switch 2
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
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

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : void CAR_Init(void)
 * \Description     : Initialization of hardware and creation of tasks
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
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
    LCD_SendString(&APP_LCD, "Temp: ");
    LCD_GoToXY(&APP_LCD, 8, 0);
    LCD_SendChar(&APP_LCD, 248);
    LCD_SendChar(&APP_LCD, 'C');
    Switch_IntConfig(&Local_Switch1, Switch1_Notification);
    Switch_IntConfig(&Local_Switch2, Switch2_Notification);
    ultrasonic_distance(&APP_Distance, Ultrasonic_Notifaction);
    /*Create ultrasonic task to get reading every 50 MS*/
    Create_Task(UltraSonic_Task, 1, 0, 0);
    /*Create Avoid obstacles task to be executed every 50 MS*/
    Create_Task(avoid_obstacles, 1, 0, 1);
    /*Create Car start Task to be executed every 50 MS*/
    Create_Task(CarStart_Task, 1, 0, 2);
    /*Create Car Stop Task to be executed every 50 MS*/
    Create_Task(CarStop_Task, 1, 0, 3);
    /*Create Watch Task to calculate the elapsed time every 1 S*/
    Create_Task(Watch_Task, 20, 0, 4);
    /*Create LDR swing task to be executed every 150 MS*/
    Create_Task(ldr_swing_car, 3, 0, 5);
    /*Create Distance Display task to be Displayed every 100 MS*/
    Create_Task(LCD_Distancedisplay, 2, 1, 6);
    /*Create LDR difference Display task to be Displayed every 150 MS*/
    Create_Task(LCD_LDRDisplay, 3, 1, 7);
    /*Create Time elapsed Display task to be Displayed every 1 S*/
    Create_Task(LCD_TimeDisplay, 20, 0, 8);
    /*Create Temperature Task to be executed every 4 S*/
    Create_Task(Temperature_Task, 80, 2, 9);
    /*Start scheduler*/
    Tasks_Sceduler();
}

/******************************************************************************
 * \Syntax          : void UltraSonic_Task(void)
 * \Description     : Get the Ultrasonic Reading
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void UltraSonic_Task(void)
{
    if(APP_UltrasonicGFlag==FLAG_HIGH)
    {
        ultrasonic_distance(&APP_Distance, Ultrasonic_Notifaction);
        APP_UltrasonicGFlag=FLAG_LOW;
    }
}

/******************************************************************************
 * \Syntax          : void avoid_obstacles(void)
 * \Description     : A task Implements the logic of obstacles avoid
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void avoid_obstacles(void)
{
    static u8 Timeout = 0;
    if(APP_CarMoving==FLAG_HIGH)
    {
        if(APP_Distance<=MIN_DISTANCE)
        {
            /*Its Time to avoid obstacle*/
            APP_AvoidFlag=FLAG_HIGH;
        }
        else if(APP_AvoidFlag == FLAG_LOW)
        {
            Motor_Set_Direction(Motor_Left_Forward);
            Motor_Set_Direction(Motor_Right_Forward);
            Motor_Set_Speed(65, Right_Motors);
            Motor_Set_Speed(65, Left_Motors);
        }
        else{
            /* MISRA */
        }
        if (APP_AvoidFlag == FLAG_HIGH)
        {
            if (APP_Distance > 30)
            {
                Motor_Set_Direction(Motor_Left_Reverse);
                Motor_Set_Direction(Motor_Right_Forward);
                if(APP_CarTimer-Timeout > 0){
                    APP_AvoidFlag = FLAG_LOW;
                }

            }
            else
            {
                Motor_Set_Speed(80, Right_Motors);
                Motor_Set_Speed(80, Left_Motors);
                Motor_Set_Direction(Motor_Left_Reverse);
                Motor_Set_Direction(Motor_Right_Reverse);
                Timeout=APP_CarTimer;
            }
        }
    }
    else
    {
        /*MISRA*/
    }
}

/******************************************************************************
 * \Syntax          : void CarStart_Task(void)
 * \Description     : Start Moving the Car
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void CarStart_Task(void)
{
    if(APP_StartFlag==1)
    {
        Motor_Start();
        APP_StartFlag=FLAG_LOW;
        APP_CarMoving=FLAG_HIGH;
    }
}

/******************************************************************************
 * \Syntax          : void CarStop_Task(void)
 * \Description     : Stop Moving the Car
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
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

/******************************************************************************
 * \Syntax          : void Watch_Task(void)
 * \Description     : Calculate the elapsed time of the car moving
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void Watch_Task(void)
{
    if(APP_CarMoving==FLAG_HIGH)
    {
        APP_CarTimer++;
    }
}

/******************************************************************************
 * \Syntax          : void ldr_swing_car(void)
 * \Description     : A task that Implements the logic of Swing of car
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void ldr_swing_car(void)
{
    if((APP_CarMoving==FLAG_HIGH)&&(APP_AvoidFlag != FLAG_HIGH))
    {
        LDR_Read(APP_LDRArr);
        if(APP_LDRArr[0]>=APP_LDRArr[1])
        {
            APP_LDRDifference=APP_LDRArr[0]-APP_LDRArr[1];
            APP_LDRFlag=FLAG_HIGH;
        }
        else
        {
            APP_LDRDifference=APP_LDRArr[1]-APP_LDRArr[0];
            APP_LDRFlag=FLAG_LOW;
        }
        Motor_Set_Direction(Motor_Left_Forward);
        Motor_Set_Direction(Motor_Right_Forward);
        if(APP_LDRDifference>=LDR_DIFF)
        {
            if(APP_LDRFlag==FLAG_HIGH)
            {
                Motor_Set_Speed(0, Right_Motors);
                Motor_Set_Speed(80, Left_Motors);
            }
            else
            {
                Motor_Set_Speed(0, Left_Motors);
                Motor_Set_Speed(80, Right_Motors);
            }
        }
        else
        {
            Motor_Set_Speed(65, Left_Motors);
            Motor_Set_Speed(65, Right_Motors);
        }
    }
    else
    {
        /*MISRA*/
    }
}

/******************************************************************************
 * \Syntax          : void LCD_Distancedisplay(void)
 * \Description     : Display the Distance on LCD
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void LCD_Distancedisplay(void)
{
    static u64 Local_Distance=0;
    if(Local_Distance != APP_Distance)
    {
        LCD_GoToXY(&APP_LCD, 8, 1);
        LCD_WriteNumber(&APP_LCD, (s64)APP_Distance);
        Local_Distance=APP_Distance;
    }
    else
    {
        /*MISRA*/
    }
}

/******************************************************************************
 * \Syntax          : void LCD_LDRDisplay(void)
 * \Description     : Display the Difference of the 2 LDRs Reading on LCD
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void LCD_LDRDisplay(void)
{
    static u32 Local_LDRDifference=0;
    if(Local_LDRDifference!=APP_LDRDifference)
    {
        LCD_GoToXY(&APP_LCD, 12, 0);
        LCD_WriteNumber(&APP_LCD, (s64)APP_LDRDifference);
        Local_LDRDifference=APP_LDRDifference;
    }
    else
    {
        /*MISRA*/
    }
}

/******************************************************************************
 * \Syntax          : void LCD_TimeDisplay(void)
 * \Description     : Display the Difference of the 2 LDRs Reading on LCD
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void LCD_TimeDisplay(void)
{
    LCD_GoToXY(&APP_LCD, 0, 1);
    LCD_WriteNumber(&APP_LCD, (s64)APP_CarTimer);
}

/******************************************************************************
 * \Syntax          : void Temperature_Task(void)
 * \Description     : Get the temperature every 4 Seconds
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void Temperature_Task(void)
{
    static u8 Local_Temp=0;
    /*Read the Temperature*/
    Local_Temp=Temp_Send_Read();
    LCD_GoToXY(&APP_LCD, 6, 0);
    /*Send Temperature to LCD*/
    LCD_WriteNumber(&APP_LCD, (s64)Local_Temp);
}

/**********************************************************************************************************************
 *  END OF FILE: RC_Car_Program.c
 *********************************************************************************************************************/
