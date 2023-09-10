
#include "Ultrasonic.h"

u64 risingEdgeTime = 0;
u64 fallingEdgeTime = 0;
u64 difference = 0;
f64 time = 0;
u64 distance = 0;

void (*ptr_func_gobal)(void);
u64* distance_global = NULL;

u8 captureFlag = 0;



static GPTM_Config_t GPTM_config = {.TimerBlock = GPTM_WTIMER5,.TimerConc = GPTM_INDIVIDUAL,.TimerChannel = GPTM_TIMERA,
                                    .TimerConState = GPTM_CAPUTURE , .TimerMode = GPTM_MODE_EDGE_TIME , .CountUpDown = GPTM_COUNT_DOWN,.Prescaler = 0};


static void Delay_In_Us(u32 us){
    uint32_t count = (us * 3) / 10;  // Adjust this value based on your system clock frequency
    while (count != 0) {
        count--;
    }
}

void Get_Distance(void){

    if(captureFlag == 0){
        GPTM_GetTimerValue(&GPTM_config,&risingEdgeTime);
        captureFlag=1;
    }
    else{
        GPTM_GetTimerValue(&GPTM_config,&fallingEdgeTime);
        difference = risingEdgeTime - fallingEdgeTime ;
        time = (f64)(difference) / (f64)(16000000);
        *distance_global = (time * 34300) / 2 ;
        ptr_func_gobal();
        captureFlag = 0;
    }
}


void ultrasonic_distance(u64*distance_local,void (*ptr_func_local)(void)){
    distance_global = distance_local;
    ptr_func_gobal = ptr_func_local ;
    GPTM_SetInterruptState(GPTM_WTIMER5,GPTM_TIMERA,GPTM_CAPUTURE_EVENT_INT,GPTM_INT_ENABLE);
    GPIO_SetPinValue(GPIO_PORTE, GPIO_PIN0, GPIO_PIN_HIGH);
    Delay_In_Us(10);
    GPIO_SetPinValue(GPIO_PORTE, GPIO_PIN0, GPIO_PIN_LOW);
}





void Ultra_Sonic_init(void){

    RCC_SetPrephralClockState(RCC_GPIOE,RCC_CLK_ENABLE);
    RCC_SetPrephralClockState(RCC_GPIOD,RCC_CLK_ENABLE);
    RCC_SetPrephralClockState(RCC_wGPTM5,RCC_CLK_ENABLE);


    /*GPIO configuration*/

    GPIO_Config_t GPIO_config_E0 = {.Port = GPIO_PORTE , .Pin = GPIO_PIN0 , .Dir = GPIO_PIN_OUTPUT , .Mode = GPIO_PIN_DIGITAL,
                                    .PinState = GPIO_PIN_PUSHPULL,.PinPull = GPIO_PIN_FLOATING};
    GPIO_Config_t GPIO_config_D6 = {.Port = GPIO_PORTD , .Pin = GPIO_PIN6 , .Dir = GPIO_PIN_INPUT , .Mode = GPIO_PIN_ALTFUNC,
                                    .PinState = GPIO_PIN_PUSHPULL , .PinPull = GPIO_PIN_FLOATING, .AltFuncNum = GPIO_ALTFUNC7};
    GPIO_Init(&GPIO_config_E0,1);
    GPIO_Init(&GPIO_config_D6,1);


    /*GPTM configuration*/

    GPTM_Init(&GPTM_config,1);
    GPTM_SetEventTrigger(GPTM_WTIMER5,GPTM_TIMERA,GPTM_EVENT_BOTH_EDGES);
    GPTM_SetTimerLoadValue(&GPTM_config,0xFFFFFFFF);
    GPTM_SetState(GPTM_WTIMER5,GPTM_TIMERA,GPTM_START);
    GPTM_SetCallBack(GPTM_WTIMER5,GPTM_TIMERA,GPTM_CAPUTURE_EVENT_INT,Get_Distance);
    NVIC_SetInterruptState(NVIC_TIMER5A_32_64_IRQ, NVIC_INT_ENABLE);

}

