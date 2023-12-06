/*
 * interrupt_ADC.c
 *
 *  Created on: Feb 28, 2023
 *      Author: joshperkins
 */

#include "functions.h"
#include "msp430.h"
#include "string.h"
#include "macros.h"
unsigned int ADC_Channel;
unsigned int ADC_Left_Detect;
unsigned int ADC_Right_Detect;
unsigned int ADC_Thumb;
extern unsigned int switch_state1;




#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
    case ADCIV_NONE:
        break;
    case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
// before its previous conversion result was read.
        break;
    case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
        break;
    case ADCIV_ADCHIIFG: // Window comparator interrupt flags
        break;
    case ADCIV_ADCLOIFG: // Window comparator interrupt flag
        break;
    case ADCIV_ADCINIFG: // Window comparator interrupt flag
        break;
    case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
        ADCCTL0 &= ~ADCENC; // Disable ENC bit.
       switch (ADC_Channel++){
        case 0x00: // Channel A2 Interrupt
            ADC_Left_Detect = ADCMEM0; // Move result into Global
            ADC_Left_Detect = ADC_Left_Detect >> 2; // Divide the result by 4
//            HEXtoBCD(ADC_Left_Detect); // Convert result to String
//            adc_line(4, 6); // Place String in Display
            ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
            ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
            break;
        case 0x01:
            //Replicate for each channel being read
            ADC_Right_Detect = ADCMEM0; // Move result into Global
            ADC_Right_Detect = ADC_Right_Detect >> 2; // Divide the result by 4
//            HEXtoBCD(ADC_Right_Detect); // Convert result to String
//            adc_line(4, 0); // Place String in Display
            ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A3
            ADCMCTL0 |= ADCINCH_5; // Enable Next channel A5
            //ADC_Channel = 0;
            break;
        case 0x02:
            ADC_Thumb = ADCMEM0; // Channel A5
//            HEXtoBCD(ADC_Thumb); // Convert result to String
//            adc_line(1, 0); // Place String in Display

            ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A5
            ADCMCTL0 |= ADCINCH_2; // Enable next channel A2
            ADC_Channel = 0;
        break;
        default: break;
        }
        //ADCCTL0 |= ADCENC; // Enable Conversions
        //ADCCTL0 |= ADCSC;
        break;
        default: break;
    }
}

