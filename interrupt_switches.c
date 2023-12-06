/*
 * switches.c
 *
 *  Created on: Feb 9, 2023
 *      Author: joshperkins
 */

//------------------------------------------------------------------------------
//
//  Description: This file contains the left and right switch interrupt implementations
//
//
//  Josh Perkins
//  Feb 2023
//  Built with TI Code Composer Studio 12.2.0
//------------------------------------------------------------------------------

#include "functions.h"
#include "macros.h"
#include "msp430.h"
#include "string.h"
extern volatile unsigned int count_debounce_SW1;
extern volatile unsigned int count_debounce_SW2;
extern unsigned int SW1_pressed;
extern unsigned int SW2_pressed;
extern unsigned int switch_state1;
extern unsigned int switch_state2;
extern char state;
extern char IOT_Data[4][BUFF_SIZE];
extern unsigned int line;

//------------------------------------------------------------------------------
// Switch 1 Configurations

#pragma vector=PORT4_VECTOR
__interrupt void switchP4_interrupt(void){
// Switch 1
    if (P4IFG & SW1) {
        P4IE &= ~SW1;               //disable switch 1
        P4IFG &= ~SW1;              //clear switch 1 flag
        TB0CCTL1 &= ~CCIFG;         //Clear CCR1 flag
        TB0CCTL1 |= CCIE;           //enable CCR1 timer
        TB0CCTL0 &= ~CCIE;          //disable CCR0 timer

        if (switch_state1 == 0) {
			strcpy(display_line[0], " Waiting  ");
			strcpy(display_line[1], "for input ");
        display_changed = TRUE;
        }
        else {
			strcpy(display_line[0], " Waiting  ");
			strcpy(display_line[1], "for input ");
        display_changed = TRUE;
        }

        SW1_pressed = OKAY;

        TB0CCR1 += TB0CCR1_INTERVAL;
    }
}

// Switch 2 Configurations
#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
// Switch 2
    if (P2IFG & SW2) {
        P2IE &= ~SW2;               //disable switch 2
        P2IFG &= ~SW2;              //clear switch 2 flag
        TB0CCTL2 &= ~CCIFG;         //Clear CCR2 flag
        TB0CCTL2 |= CCIE;           //enable CCR2 timer
        TB0CCTL0 &= ~CCIE;          //disable CCR0 timer

        TB0CCR2 += TB0CCR2_INTERVAL;
    }
}

