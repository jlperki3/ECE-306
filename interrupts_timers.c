/*
 * interrupts_timers.c
 *
 *  Created on: Feb 23, 2023
 *      Author: joshperkins
 */
//------------------------------------------------------------------------------
//
//  Description: This file contains the timer interrupt definitions
//
//
//  Josh Perkins
//  Feb 2023
//  Built with TI Code Composer Studio 12.2.0
//------------------------------------------------------------------------------
#include "functions.h"
#include "msp430.h"
#include "macros.h"
extern unsigned int display_counter;
extern unsigned int startup;
extern volatile unsigned int count_debounce_SW1;
extern volatile unsigned int count_debounce_SW2;
unsigned int SW1_pressed;
unsigned int SW2_pressed;
extern unsigned int state_timer;
extern char state;
extern unsigned int switch_state2;
extern unsigned int circle_timer_s;
extern unsigned int circle_timer_s2;
extern unsigned int switch_flag;
extern unsigned int IOT_timer;
unsigned int DAC_startup = 0;
extern unsigned int DAC_data;
extern unsigned int movement_timer;
extern char move_direction;
extern unsigned int move_time;
extern char command[10];
unsigned int five_seconds = 0;
extern unsigned int course_timer;
unsigned int course_timer_flag = 0;
extern unsigned int course_timer_helper;
unsigned int end_timer = 0;


#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
    startup++;
    display_counter++;
	course_timer++;
	course_timer_helper++;
	state_timer++;
	end_timer++;
// Code to update display every 200ms
    if (display_counter > TWO_HUNDRED_MS) {
    update_display = 1;
    display_counter = 0;
    IOT_timer++;
    if (IOT_timer >= TEN_SECONDS) IOT_timer = 0;
    if (state_timer >= FIFTY_SECONDS) state_timer = 0;
    if (end_timer >= TEN_SECONDS) end_timer = 0;
    }


    TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
}

#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
switch(__even_in_range(TB0IV,14)) {

    case 0: break; // No interrupt


    case 2: // CCR1
        if (count_debounce_SW1 >= DEBOUNCE_TIME) {
            TB0CCTL1 &= ~CCIE;          //Disable Timer B0 CCR1
            P4IFG &= ~SW1;              //clear flag
            P4IE |= SW1;                //enable switch 1
            TB0CCTL0 |= CCIE;            //enable CCR0 timer
            count_debounce_SW1 = 0;
            SW1_pressed = NOT_OKAY;
            //switch_flag = 1;
        }
        if (SW1_pressed == OKAY) {
            count_debounce_SW1++;
            TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TB0CCR1
        }
        break;


    case 4: // CCR2

        if (count_debounce_SW2 >= DEBOUNCE_TIME) {
            TB0CCTL2 &= ~CCIE;          //Disable Timer B0 CCR2
            P2IFG &= ~SW2;              //clear flag
            P2IE |= SW2;                //enable switch 2
            TB0CCTL0 |= CCIE;           //enable CCR0 timer
            count_debounce_SW2 = 0;
            SW2_pressed = NOT_OKAY;
            if (switch_state2 == 0) {
                //state = FORWARD;
                switch_state2 = 1;
            }
            else {
                //state = WAIT;
                switch_state2 = 0;
            }
        }
        if (SW2_pressed == OKAY) {
            count_debounce_SW2++;
            TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TB0CCR2
        }
        break;

    case 14: // overflow
    	switch (DAC_startup) {
    	case 0:
    		DAC_data -= DAC_DECREMENT;
    		SAC3DAT = DAC_data;
    		if (DAC_data <= FINAL_DAC) DAC_startup++;
    		break;
    	case 1:
    		TB0CTL &= ~TBIE;		//Disable overflow interrupt
    		break;
    	default: break;
    	}

    break;
    default: break;
    }
//----------------------------------------------------------------------------
}
#pragma vector = TIMER2_B0_VECTOR
__interrupt void Timer2_B0_ISR(void){
	if (movement_timer > 0) {
		movement_timer--;
	}

	five_seconds++;

	TB2CCR0 += TB2CCR0_INTERVAL; // Add Offset to TB2CCR0

}

#pragma vector=TIMER2_B1_VECTOR
__interrupt void TIMER2_B1_ISR(void){
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
switch(__even_in_range(TB2IV,14)) {

    case 0: break; // No interrupt


    case 2: // CCR1 not used
        ADCCTL0 |= ADCENC; // Enable Conversions
        ADCCTL0 |= ADCSC;
        TB2CCR1 += TB2CCR1_INTERVAL; // Add Offset to TB2CCR1
        break;


    case 4: // CCR2 not used


        break;

    case 14: // overflow

//...... Add What you need happen in the interrupt ......

    break;
    default: break;
    }
//----------------------------------------------------------------------------
}
