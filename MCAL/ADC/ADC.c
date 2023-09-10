#include "ADC.h"

void ADC_SequencerInit(ADC_RegDef_t *ADCx,
                       ADC_Sequencer_InitTypeDef *Sequencer_Config)
{
    ADCx->ACTSS &= ~(1U << Sequencer_Config->Sequencer); /* Disable Sequencer */
    ADCx->SAC &= ~7UL; /* Clear Sample Averaging Control */
    ADCx->SAC |= Sequencer_Config->Oversampling; /* Set Sample Averaging Control */
    ADCx->EMUX &= ~(0xFU << (4U * Sequencer_Config->Sequencer)); /* Clear Trigger source */
    ADCx->EMUX |= (Sequencer_Config->Trigger
            << (4U * Sequencer_Config->Sequencer)); /* Set Trigger source for Sequencer */
}

void ADC_SequencerConfig(ADC_RegDef_t *ADCx,
                         ADC_Sequencer_ConfigTypeDef *Sequence)
{
    uint8_t i;
    switch (Sequence->Sequencer)
    {
    case ADC_SEQUENCER0:
        ADCx->SSMUX0 = 0U; /* Clear Sequence */
        ADCx->SSCTL0 = 0U; /* Clear Control */
        for (i = 8U;
                (i > 0U)
                        && (((Sequence->Sequence0_Control[8U - i])
                                & ADC_END_OF_SEQUENCE) == 0U); i--)
        {
            ADCx->SSMUX0 |= (Sequence->Sequence0[8U - i] << ((8U - i) * 4U));
            ADCx->SSCTL0 |= (Sequence->Sequence0_Control[8U - i]
                    << ((8U - i) * 4U));
        }
        break;
    case ADC_SEQUENCER1:
        ADCx->SSMUX1 = 0U; /* Clear Sequence */
        ADCx->SSCTL1 = 0U; /* Clear Control */
        for (i = 4U;
                (i > 0U)
                        && (((Sequence->Sequence1_Control[4U - i])
                                & ADC_END_OF_SEQUENCE) == 0U); i--)
        {
            ADCx->SSMUX1 |= (Sequence->Sequence1[4U - i] << ((4U - i) * 4U));
            ADCx->SSCTL1 |= (Sequence->Sequence1_Control[4U - i]
                    << ((4U - i) * 4U));
        }
        break;
    case ADC_SEQUENCER2:
        ADCx->SSMUX2 = 0U; /* Clear Sequence */
        ADCx->SSCTL2 = 0U; /* Clear Control */
        for (i = 4U;
                (i > 0U)
                        && (((Sequence->Sequence2_Control[4U - i])
                                & ADC_END_OF_SEQUENCE) == 0U); i--)
        {
            ADCx->SSMUX2 |= (Sequence->Sequence2[4U - i] << ((4U - i) * 4U));
            ADCx->SSCTL2 |= (Sequence->Sequence2_Control[4U - i]
                    << ((4U - i) * 4U));
        }
        break;
    case ADC_SEQUENCER3:
        ADCx->SSMUX3 = 0U; /* Clear Sequence */
        ADCx->SSCTL3 = 0U; /* Clear Control */
        ADCx->SSMUX3 |= Sequence->Sequence3;
        ADCx->SSCTL3 |= Sequence->Sequence3_Control;
        break;
    default:
        break;
    }
}

void ADC_SequenceIntEnable(ADC_RegDef_t *ADCx, uint8_t Sequencer)
{
    ADCx->IM |= (1U << Sequencer); /* Set Interrupt Mask */
}

void ADC_SequencerEnable(ADC_RegDef_t *ADCx, uint8_t Sequencer)
{
    ADCx->ACTSS |= (1U << Sequencer); /* Enable Sequencer */
}

void ADC_SequencerDisable(ADC_RegDef_t *ADCx, uint8_t Sequencer)
{
    ADCx->ACTSS &= ~(1U << Sequencer); /* Disable Sequencer */
}

void ADC_StartConversion(ADC_RegDef_t *ADCx, uint8_t Sequencer)
{
    ADCx->PSSI |= (1U << Sequencer); /* Processor Trigger to start conversion */
}

uint16_t ADC_GetData(ADC_RegDef_t *ADCx, uint8_t Sequencer)
{
    uint16_t data;
    while ((ADCx->RIS & (1U << Sequencer)) == 0)
        ; /* Wait for end of conversion */
    switch (Sequencer)
    {
    case ADC_SEQUENCER0:
        data = ADCx->SSFIFO0; /* Get data of Sequencer 0 */
        break;
    case ADC_SEQUENCER1:
        data = ADCx->SSFIFO1; /* Get data of Sequencer 1 */
        break;
    case ADC_SEQUENCER2:
        data = ADCx->SSFIFO2; /* Get data of Sequencer 2 */
        break;
    case ADC_SEQUENCER3:
        data = ADCx->SSFIFO3; /* Get data of Sequencer 3 */
        break;
    default:
        break;
    }
    ADCx->ISC |= (1U << Sequencer); /* Clear Interrupt flag */
    return data;
}

void ADC_IntRegister(ADC_RegDef_t *ADCx, uint8_t Sequencer,
                     void (*pfnIntHandler)(void))
{
    switch ((uint32_t) &(*ADCx))
    {
    case ADC0_BASE_ADDRESS:
        ptr_ADC[Sequencer] = pfnIntHandler;
        break;
    case ADC1_BASE_ADDRESS:
        ptr_ADC[4U + Sequencer] = pfnIntHandler;
        break;
    default:
        break;
    }
}
