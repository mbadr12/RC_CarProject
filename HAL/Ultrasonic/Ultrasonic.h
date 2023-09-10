
#ifndef HAL_ULTRA_SONIC_H_
#define HAL_ULTRA_SONIC_H_

#include <stdint.h>
#include "../../LIB/Std_Types.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/GPTM/GPTM.h"
#include "../../MCAL/RCC/RCC.h"
#include "../../MCAL/NVIC/NVIC.h"

static void Delay_In_Us(u32 us);

void Ultra_Sonic_init(void);
void ultrasonic_distance(u64*distance_local,void (*ptr_func_local)(void));

#endif /* HAL_ULTRA_SONIC_H_ */
