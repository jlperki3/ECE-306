// ------------------------------------------------------------------------------
//
//  Description: This file contains the Clock Initialization
//
//  Josh Perkins
//  Jan 2023
//  Built with TI Code Composer Studio 12.2.0
// ------------------------------------------------------------------------------
#include "functions.h"
#include "macros.h"
#include "msp430.h"

//------------------------------------------------------------------------------


//Init_Conditions Declaration
void Init_Conditions(void){
//------------------------------------------------------------------------------
    extern char display_line[4][11];
    extern char *display[4];
    extern unsigned char display_mode;
    extern volatile unsigned char display_changed;
    extern volatile unsigned char update_display;
    extern volatile unsigned int update_display_count;
    extern volatile unsigned int Time_Sequence;
    extern volatile char one_time;
    extern unsigned int test_value;
    extern char chosen_direction;
    extern char change;

    Motors_Off();

    int i;
    for(i=0;i<11;i++){
        display_line[0][i] = RESET_STATE;
        display_line[1][i] = RESET_STATE;
        display_line[2][i] = RESET_STATE;
        display_line[3][i] = RESET_STATE;
    }
    display_line[0][10] = 0;
    display_line[1][10] = 0;
    display_line[2][10] = 0;
    display_line[3][10] = 0;

    display[0] = &display_line[0][0];
    display[1] = &display_line[1][0];
    display[2] = &display_line[2][0];
    display[3] = &display_line[3][0];
    update_display = 0;


    // Interrupts are disabled by default, enable them.
    enable_interrupts();
//------------------------------------------------------------------------------
}

