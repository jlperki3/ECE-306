/*
 * switches.c
 *
 *  Created on: Mar 28, 2023
 *      Author: joshperkins
 */
#include "functions.h"
#include "msp430.h"
#include "string.h"
#include "macros.h"
extern unsigned int SW1_pressed;
extern unsigned int SW2_pressed;
extern unsigned int switch_state1;
extern unsigned int switch_state2;
extern char state;
unsigned int switch_flag;


void Switch1_Process(void) {

//    if (SW1_pressed == OKAY) {
//        if (switch_state1 == 0) {
//        UCA1BRW = 4 ; // 115,200 baud
//        UCA1MCTLW = 0x5551 ;
//        USCI_A1_transmit();
//        switch_state1 = 1;
//        strcpy(display_line[2], "BAUD      ");
//        strcpy(display_line[3], "115,200   ");
//        display_changed = TRUE;
//    //        update_display = 1;
//    //        strcpy(display_line[0], "        ON");
//    //        display_changed = TRUE;
//        switch_flag = 0;
//        }
//        else {
//        UCA1BRW = 17 ; // 460,800 baud
//        UCA1MCTLW = 0x4A00 ;
//        USCI_A1_transmit();         //set pb index to 0, clear tx interrupt flag, enable tx interrupt
//        switch_state1 = 0;
//        //strcpy(display_line[0], IOT_DATA);
//        strcpy(display_line[2], "BAUD      ");
//        strcpy(display_line[3], "460,800   ");
//        display_changed = TRUE;
//    //        update_display = 1;
//    //        strcpy(display_line[0], "       OFF");
//    //        display_changed = TRUE;
//        //switch_flag = 0;
//        }
//    }
}

void Switch2_Process(void) {

}

void Switches_Process(void) {
    Switch1_Process();
    Switch2_Process();
}

