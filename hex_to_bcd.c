/*
 * hextobcd.c
 *
 *  Created on: Feb 28, 2023
 *      Author: joshperkins
 */




//-----------------------------------------------------------------
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//-----------------------------------------------------------------
#include "functions.h"
#include "msp430.h"
#include "string.h"
#include "macros.h"

extern char thousands;
extern char hundreds;
extern char tens;
extern char ones;
extern char adc_char[4];
extern char timer_char[5];
extern char display_line[4][11];


void HEXtoBCD(int hex_value){
    int value = 0;
    int i;
    for(i=0; i < 4; i++) {
        adc_char[i] = '0';
    }
    while (hex_value >= THOUSANDS){
        hex_value = hex_value - THOUSANDS;
        value = value + 1;
        adc_char[0] = 0x30 + value;
    }
    value = 0;
    while (hex_value >= HUNDREDS){
        hex_value = hex_value - HUNDREDS;
        value = value + 1;
        adc_char[1] = 0x30 + value;
    }
    value = 0;
    while (hex_value >= TENS){
        hex_value = hex_value - TENS;
        value = value + 1;
        adc_char[2] = 0x30 + value;
    }
    adc_char[3] = 0x30 + hex_value;
    }
//-----------------------------------------------------------------

//-------------------------------------------------------------
// ADC Line insert
// Take the HEX to BCD value in the array adc_char and place it
// in the desired location on the desired line of the display.
// char line => Specifies the line 1 thru 4
// char location => Is the location 0 thru 9
//
//-------------------------------------------------------------
void adc_line(char line, char location){
//-------------------------------------------------------------
    int i;
    unsigned int real_line;
    real_line = line - 1;
    for(i=0; i < 4; i++) {
        display_line[real_line][i+location] = adc_char[i];
        display_changed = TRUE;

    }
}
//-------------------------------------------------------------


void HEXtoBCD_TIMER(int hex_value){
    int value = 0;
    int i;
    for(i=0; i < 4; i++) {
        timer_char[i] = '0';
    }
    while (hex_value >= THOUSANDS){
        hex_value = hex_value - THOUSANDS;
        value = value + 1;
        timer_char[0] = 0x30 + value;
    }
    value = 0;
    while (hex_value >= HUNDREDS){
        hex_value = hex_value - HUNDREDS;
        value = value + 1;
        timer_char[1] = 0x30 + value;
    }
    value = 0;
    while (hex_value >= TENS){
        hex_value = hex_value - TENS;
        value = value + 1;
        timer_char[2] = 0x30 + value;
    }
    timer_char[3] = '.';
    timer_char[4] = 0x30 + hex_value;


    }

//-----------------------------------------------------------------

//-------------------------------------------------------------
// ADC Line insert
// Take the HEX to BCD value in the array adc_char and place it
// in the desired location on the desired line of the display.
// char line => Specifies the line 1 thru 4
// char location => Is the location 0 thru 9
//
//-------------------------------------------------------------
void adc_line_timer(char line, char location){
//-------------------------------------------------------------
    int i;
    unsigned int real_line;
    real_line = line - 1;
    for(i=0; i < 5; i++) {
        display_line[real_line][i+location] = timer_char[i];
        display_changed = TRUE;
    }
}
//-------------------------------------------------------------
