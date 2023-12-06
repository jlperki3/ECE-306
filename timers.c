/*
 * timers.c
 *
 *  Created on: Feb 17, 2023
 *      Author: joshperkins
*/
//------------------------------------------------------------------------------
//
//  Description: This file contains the interrupt timer initializations
//
//
//  Josh Perkins
//  Feb 2023
//  Built with TI Code Composer Studio 12.2.0
//------------------------------------------------------------------------------

#include "functions.h"
#include "msp430.h"
#include "macros.h"

// Timer B0 initialization sets up both B0_0, B0_1-B0_2 and overflow
void Init_Timer_B0(void) {
    TB0CTL = TBSSEL__SMCLK; // SMCLK source
    TB0CTL |= TBCLR; // Resets TB0R, clock divider, count direction
    TB0CTL |= MC__CONTINOUS; // Continuous up

    TB0CTL |= ID__2; // Divide clock by 2
    TB0EX0 = TBIDEX__8; // Divide clock by an additional 8

    TB0CCR0 = TB0CCR0_INTERVAL; // CCR0
    TB0CCTL0 &= ~CCIFG;
    TB0CCTL0 |= CCIE; // CCR0 enable interrupt

    TB0CCR1 = TB0CCR1_INTERVAL; // CCR1
    TB0CCTL1 &= ~CCIFG;
    TB0CCTL1 |= CCIE; // CCR1 enable interrupt

    TB0CCR2 = TB0CCR2_INTERVAL; // CCR2
    TB0CCTL2 &= ~CCIFG;
    TB0CCTL2 |= CCIE; // CCR2 enable interrupt

    TB0CTL &= ~TBIFG; // Clear Overflow Interrupt flag
    TB0CTL &= ~TBIE; // Enable Overflow Interrupt

}
//------------------------------------------------------------------------------
// Timer B2 initialization sets up both B2_0, B2_1-B2_2 and overflow
void Init_Timer_B2(void) {
    TB2CTL = TBSSEL__SMCLK; // SMCLK source
    TB2CTL |= TBCLR; // Resets TB0R, clock divider, count direction
    TB2CTL |= MC__CONTINOUS; // Continuous up

    TB2CTL |= ID__2; // Divide clock by 2
    TB2EX0 = TBIDEX__8; // Divide clock by an additional 8

    TB2CCR0 = TB2CCR0_INTERVAL; // CCR0
    TB2CCTL0 &= ~CCIFG;
	TB2CCTL0 |= CCIE; // TB2CCR0 enable interrupt

    TB2CCR1 = TB2CCR1_INTERVAL; // CCR1
    TB2CCTL1 &= ~CCIFG;
    TB2CCTL1 &= ~CCIE; // CCR1 enable interrupt

    TB2CCR2 = TB2CCR2_INTERVAL; // CCR2
    TB2CCTL2 &= ~CCIE; // CCR2 disable interrupt

    TB2CTL &= ~TBIFG; // Clear Overflow Interrupt flag
    TB2CTL &= ~TBIE; // Disable Overflow Interrupt
}
void Init_Timer_B3(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Right Side
// TB3.1 P6.0 LCD_BACKLITE
// TB3.2 P6.1 R_FORWARD
// TB3.3 P6.2 R_REVERSE
// TB3.4 P6.3 L_FORWARD
// TB3.5 P6.4 L_REVERSE
//------------------------------------------------------------------------------
    TB3CTL = TBSSEL__SMCLK; // SMCLK
    TB3CTL |= MC__UP; // Up Mode
    TB3CTL |= TBCLR; // Clear TAR

    PWM_PERIOD = WHEEL_PERIOD; // PWM Period [Set this to 50005]

    TB3CCTL1 = OUTMOD_7; // CCR1 reset/set
    LCD_BACKLITE_DIMING = PERCENT_50; // P6.0 Right Forward PWM duty cycle

    TB3CCTL2 = OUTMOD_7; // CCR2 reset/set
    RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Right Forward PWM duty cycle

    TB3CCTL3 = OUTMOD_7; // CCR3 reset/set
    RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM duty cycle

    TB3CCTL4 = OUTMOD_7; // CCR4 reset/set
    LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.3 Left Forward PWM duty cycle

    TB3CCTL5 = OUTMOD_7; // CCR5 reset/set
    LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.4 Left Reverse PWM duty cycle
//------------------------------------------------------------------------------
}
