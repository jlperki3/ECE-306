/*
 * Movement.c
 *
 *  Created on: Feb 7, 2023
 *      Author: joshperkins
 */
#include "functions.h"
#include "macros.h"
#include "msp430.h"

extern unsigned int cycle_time;
extern unsigned int time_change;
//unsigned int delay_start;
//char event;
char state;
char state2;
unsigned int left_motor_count;
unsigned int right_motor_count;
unsigned int segment_count;


