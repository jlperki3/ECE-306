//------------------------------------------------------------------------------
//
//  Description: This file contains the the port.c function defintions
//
//
//  Josh Perkins
//  Jan 2023
//  Built with TI Code Composer Studio 12.2.0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include "functions.h"
#include "macros.h"
#include "msp430.h"

//Init_Ports declaration
void Init_Ports (void) {
    Init_Port1();
    Init_Port2();
    Init_Port3('c');
    Init_Port4();
    Init_Port5();
    Init_Port6();
}

//Port 1 configuration
void Init_Port1(void){
//-------------------------------------------------------
//Configure Port 1
// Port 1 Pins
// RED_LED (0x01) // 0 RED LED 0
// A1_SEEED (0x02) // 1 A1_SEEED
// V_DETECT_L (0x04) // 2 V_DETECT_L
// V_DETECT_R (0x08) // 3 V_DETECT_R
// A4_SEEED (0x10) // 4 V_A4_SEEED
// V_THUMB (0x20) // 5 V_THUMB
// UCA0RXD (0x40) // 6 Back Channel UCA0RXD
// UCA0TXD (0x80) // 7 Back Channel UCA0TXD
//-------------------------------------------------------
    P1DIR = 0x00; // Set P1 direction to input
    P1OUT = 0x00; // P1 set Low

    // Pin 0
    P1SEL0 &= ~RED_LED; // Set RED_LED as GP I/O
    P1SEL1 &= ~RED_LED; // Set RED_LED as GP I/O
    P1OUT |= RED_LED; // Set Red LED On
    P1DIR &= ~RED_LED; // Set Red LED direction to output

    // Pin 1
    P1SELC |= A1_SEEED; // ADC input for A1_SEEED

    // Pin 2
    P1SELC |= V_DETECT_L; // ADC input for V_DETECT_L

    // Pin 3
    P1SELC |= V_DETECT_R; // ADC input for V_DETECT_R

    // Pin 4
    P1SELC |= A4_SEEED; // ADC input for V_A4_SEEED

    // Pin 5
    P1SELC |= V_THUMB; // ADC input for V_THUMB

    // Pin 6
    P1SEL0 |= UCA0TXD; // UCA0TXD pin
    P1SEL1 &= ~UCA0TXD; // UCA0TXD pin

    // Pin 7
    P1SEL0 |= UCA0RXD; // UCA0RXD pin
    P1SEL1 &= ~UCA0RXD; // UCA0RXD pin
//-------------------------------------------------------
}

void Init_Port2(void){ // Configure Port 2
//------------------------------------------------------------------------------
    P2OUT = 0x00; // P2 set Low
    P2DIR = 0x00; // Set P2 direction to output

    // Pin 0
    P2SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
    P2SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
    P2OUT &= ~RESET_LCD; // Initial Value = Low / Off
    P2DIR |= RESET_LCD; // Direction = output

    // Pin 1
    P2SEL0 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
    P2SEL1 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
    P2OUT &= ~CHECK_BAT; // Initial Value = Low / Off
    P2DIR |= CHECK_BAT; // Direction = output

    // Pin 2
    P2SEL0 &= ~IR_LED; // P2_2 GPIO operation
    P2SEL1 &= ~IR_LED; // P2_2 GPIO operation
    P2OUT &= ~IR_LED; // Initial Value = Low / Off
    P2DIR |= IR_LED; // Direction = output

    // Pin 3
    P2SEL0 &= ~SW2; // SW2 set as I/0
    P2SEL1 &= ~SW2; // SW2 set as I/0
    P2DIR &= ~SW2; // SW2 Direction = input
    P2OUT |= SW2; // Configure pull-up resistor SW2
    P2REN |= SW2; // Enable pull-up resistor SW2
    P2IES |= SW2; // SW2 Hi/Lo edge interrupt
    P2IFG &= ~SW2; // IFG SW2 cleared
    P2IE |= SW2; // SW2 interrupt Enabled

    // Pin 4
    P2SEL0 &= ~IOT_RUN_RED; // IOT_RUN_CPU GPIO operation
    P2SEL1 &= ~IOT_RUN_RED; // IOT_RUN_CPU GPIO operation
    P2OUT &= ~IOT_RUN_RED; // Initial Value = Low / Off    ///////////////
    P2DIR |= IOT_RUN_RED; // Direction = input

    // Pin 5
    P2SEL0 &= ~DAC_ENB; // DAC_ENB GPIO operation
    P2SEL1 &= ~DAC_ENB; // DAC_ENB GPIO operation
    P2OUT &= ~DAC_ENB; // Initial Value = High
    P2DIR |= DAC_ENB; // Direction = output

    // Pin 6
    P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
    P2SEL1 |= LFXOUT; // LFXOUT Clock operation

    // Pin 7
    P2SEL0 &= ~LFXIN; // LFXIN Clock operation
    P2SEL1 |= LFXIN; // LFXIN Clock operation
//------------------------------------------------------------------------------
}

//Port 3 configuration
void Init_Port3(char smclk){
    P3DIR = 0x00;
    P3OUT = 0x00;

    //Pin 0
    P3SEL0 &= ~TEST_PROBE;
    P3SEL1 &= ~TEST_PROBE;
    P3OUT &= ~TEST_PROBE;
    P3DIR |= TEST_PROBE;

    // Pin 1
    P3SEL0 &= ~OA2O;
    P3SEL1 &= ~OA2O;
    P3OUT  &= ~OA2O;
    P3DIR  |=  OA2O;

    // Pin 2
    P3SEL0 &= ~OA2N;
    P3SEL1 &= ~OA2N;
    P3OUT  &= ~OA2N;
    P3DIR  |=  OA2N;

    //Pin 3
    P3SEL0 &= ~OA2P;
    P3SEL1 &= ~OA2P;
    P3OUT  &= ~OA2P;
    P3DIR  |=  OA2P;

    // Pin 4
    P3SEL1 &= ~SMCLK;
    P3SEL0 &= ~SMCLK;
    P3OUT  &= ~SMCLK;
    P3DIR  |=  SMCLK;

    // Pin 5
    P3SEL0 &= ~DAC_CNTL;
    P3SEL1 &= ~DAC_CNTL;
    P3OUT  &= ~DAC_CNTL;
    P3DIR  &= ~DAC_CNTL;

    // Pin 6
    P3SEL0 &= ~IOT_LINK_GRN;
    P3SEL1 &= ~IOT_LINK_GRN;
    P3OUT  &= ~IOT_LINK_GRN; /////////////
    P3DIR  |=  IOT_LINK_GRN;

    // Pin 7
    P3SEL0 &= ~IOT_EN;
    P3SEL1 &= ~IOT_EN;
    P3OUT  &=  ~IOT_EN;
    P3DIR  |=  IOT_EN;
}


void Init_Port4(void){ // Configure PORT 4
//------------------------------------------------------------------------------
    P4OUT = 0x00; // P4 set Low
    P4DIR = 0x00; // Set P4 direction to output

    // Pin 0
    P4SEL0 &= ~DAC_CNTL1;
    P4SEL1 &= ~DAC_CNTL1;
    P4DIR  &= ~DAC_CNTL1;

    // Pin 1
    P4SEL0 &= ~SW1;
    P4SEL1 &= ~SW1;
    P4OUT  |=  SW1;
    P4DIR  &= ~SW1;
    P4REN  |=  SW1;
    P4IES  |=  SW1;
    P4IFG  &= ~SW1;
    P4IE   |=  SW1;

    // Pin 2
    P4SEL0 |=  UCA1TXD;
    P4SEL1 &= ~UCA1TXD;

    // Pin 3
    P4SEL0 |=  UCA1RXD;
    P4SEL1 &= ~UCA1RXD;

    // Pin 4
    P4SEL0 &= ~UCB1_CS_LCD;
    P4SEL1 &= ~UCB1_CS_LCD;
    P4OUT  |=  UCB1_CS_LCD;
    P4DIR  |=  UCB1_CS_LCD;

    // Pin 5
    P4SEL0 |=  UCB1CLK;
    P4SEL1 &= ~UCB1CLK;

    // Pin 6
    P4SEL0 |=  UCB1SIMO;
    P4SEL1 &= ~UCB1SIMO;

    // Pin 7
    P4SEL0 |=  UCB1SOMI;
    P4SEL1 &= ~UCB1SOMI;
//------------------------------------------------------------------------------
}

//Port 5 configuration
void Init_Port5(void){
//--------------------------------------------------------
// Port 5 Pins
// V_BAT (0x01) // 0 V_BAT
// V_5_0 (0x02) // 1 V_5_0
// V_DAC (0x04) // 2 V_DAC
// V_3_3 (0x08) // 3 V_3.3
// IOT_PROG_MODE (0x10) // 4 IOT_PROGRAM_MODE
//--------------------------------------------------------
    P5DIR = 0x00; // Set P1 direction to input
    P5OUT = 0x00; // P1 set Low

    // Pin 0
    P5SELC |= V_BAT; // ADC input for V_BAT

    // Pin 1
    P5SELC |= V_5_0; // ADC input for V_BAT

    // Pin 2
    P5SELC |= V_DAC; // ADC input for V_DAC

    // Pin 3
    P5SELC |= V_3_3; // ADC input for V_3_3

    // Pin 4
    P5SEL0 &= ~IOT_BOOT_CPU; // IOT_BOOT GPIO operation
    P5SEL1 &= ~IOT_BOOT_CPU; // IOT_BOOT GPIO operation
    P5OUT |= IOT_BOOT_CPU; // Set Output value inactive
    P5DIR |= IOT_BOOT_CPU; // Set direction to output
//------------------------------------------------------
}

//Port 6 configuration
void Init_Port6(void){
    P6DIR = 0x00;
    P6OUT = 0x00;
    // Pin 0
    P6SEL0 |=  LCD_BACKLITE;
    P6SEL1 &= ~LCD_BACKLITE;
    P6DIR  |=  LCD_BACKLITE;

    // Pin 1
    P6SEL0 |=  L_FORWARD;
    P6SEL1 &= ~L_FORWARD;
    P6DIR  |=  L_FORWARD;

    // Pin 2
    P6SEL0 |=  R_FORWARD;
    P6SEL1 &= ~R_FORWARD;
    P6DIR  |=  R_FORWARD;

    // Pin 3
    P6SEL0 |=  R_REVERSE;
    P6SEL1 &= ~R_REVERSE;
    P6DIR  |=  R_REVERSE;

    // Pin 4
    P6SEL0 |=  L_REVERSE;
    P6SEL1 &= ~L_REVERSE;
    P6DIR  |=  L_REVERSE;

    // Pin 5
    P6SEL0 &= ~P6_5;
    P6SEL1 &= ~P6_5;
    P6DIR  &= ~P6_5;

    // Pin 6
    P6SEL0 &= ~GRN_LED;
    P6SEL1 &= ~GRN_LED;
    P6OUT &= ~GRN_LED;
    P6DIR |= GRN_LED;

}

