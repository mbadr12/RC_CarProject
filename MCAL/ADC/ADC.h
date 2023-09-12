#ifndef MCAL_ADC_DRIVERS_ADC_H_
#define MCAL_ADC_DRIVERS_ADC_H_

/* Includes */
#include "../../LIB/Std_Types.h"
#include "../../LIB/TM4C123xx.h"
#include <stdint.h>

/* Defines */

#define ADC_SEQUENCER0                  0U
#define ADC_SEQUENCER1                  1U
#define ADC_SEQUENCER2                  2U
#define ADC_SEQUENCER3                  3U

#define ADC_CONTINOUS_SAMPLING          0xFU
#define ADC_PROCESSOR_TRIGGER           0U

#define ADC_TEMP_SENSOR                 8U
#define ADC_SAMPLE_INTERRUPT            4U
#define ADC_END_OF_SEQUENCE             2U

#define ADC_AIN0                        0U
#define ADC_AIN1                        1U
#define ADC_AIN2                        2U
#define ADC_AIN3                        3U
#define ADC_AIN4                        4U
#define ADC_AIN5                        5U
#define ADC_AIN6                        6U
#define ADC_AIN7                        7U
#define ADC_AIN8                        8U
#define ADC_AIN9                        9U
#define ADC_AIN10                       10U
#define ADC_AIN11                       11U

#define ADC_OVERSAMPLING_0X             0U
#define ADC_OVERSAMPLING_2X             1U
#define ADC_OVERSAMPLING_4X             2U
#define ADC_OVERSAMPLING_8X             3U
#define ADC_OVERSAMPLING_16X            4U
#define ADC_OVERSAMPLING_32X            5U
#define ADC_OVERSAMPLING_64X            6U

/* ADC Struct */

typedef struct
{
    uint8_t Sequencer;
    uint8_t Trigger;
    uint8_t Oversampling;
} ADC_Sequencer_InitTypeDef;

typedef struct
{
    uint8_t Sequencer;
    uint8_t Sequence0[8];
    uint8_t Sequence0_Control[8];
    uint8_t Sequence1[4];
    uint8_t Sequence1_Control[4];
    uint8_t Sequence2[4];
    uint8_t Sequence2_Control[4];
    uint8_t Sequence3;
    uint8_t Sequence3_Control;
} ADC_Sequencer_ConfigTypeDef;

/* Interrupt Pointers */

void (*ptr_ADC[8])(void);

/* Function Prototypes */

void ADC_SequencerInit(ADC_RegDef_t *ADCx,
                       ADC_Sequencer_InitTypeDef *Sequencer_Config);
void ADC_SequencerConfig(ADC_RegDef_t *ADCx,
                         ADC_Sequencer_ConfigTypeDef *Sequence);
void ADC_SequenceIntEnable(ADC_RegDef_t *ADCx, uint8_t Sequencer);
void ADC_SequencerEnable(ADC_RegDef_t *ADCx, uint8_t Sequencer);
void ADC_SequencerDisable(ADC_RegDef_t *ADCx, uint8_t Sequencer);
void ADC_StartConversion(ADC_RegDef_t *ADCx, uint8_t Sequencer);
uint16_t ADC_GetData(ADC_RegDef_t *ADCx, uint8_t Sequencer);
void ADC_Clear_Interrupt(ADC_RegDef_t *ADCx, uint8_t Sequencer);
void ADC_IntRegister(ADC_RegDef_t *ADCx, uint8_t Sequencer,
                     void (*pfnIntHandler)(void));

#endif /* MCAL_ADC_DRIVERS_ADC_H_ */
