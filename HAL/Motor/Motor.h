#ifndef HAL_MOTOR_MOTOR_H_
#define HAL_MOTOR_MOTOR_H_

#include <stdint.h>
#include "MCAL/GPIO/GPIO.h"
#include "MCAL/PWM/PWM.h"
#include "MCAL/RCC/RCC.h"

#define Right_Motors                    0U
#define Left_Motors                     1U

#define Motor_Right_Forward             0U
#define Motor_Right_Reverse             1U
#define Motor_Left_Forward              2U
#define Motor_Left_Reverse              3U

void Motor_Init(void);
void Motor_Start(void);
void Motor_Set_Speed(uint16_t Speed, uint8_t Motors);
void Motor_Set_Direction(uint8_t Direction);
void Motor_Stop(void);

#endif /* HAL_MOTOR_MOTOR_H_ */
