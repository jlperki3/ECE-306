/*
 * movementfunctions.c
 *
 *  Created on: Feb 17, 2023
 *      Author: joshperkins
 */

#include "functions.h"
#include "macros.h"
#include "msp430.h"
#include "string.h"
#include "stdlib.h"
extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;
extern char state;
extern char state2;
extern unsigned int state_timer;
extern unsigned int switch_state2;
extern unsigned int circle_timer_s;
extern unsigned int circle_timer_s2;
extern unsigned int circle_timer_ms;
unsigned int course_timer = 0;
unsigned int course_timer2 = 0;
unsigned int white_counter = 0;
unsigned int state_flag = 0;



//Turn off motors
void Motors_Off(void) {
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;
}

// State control functions
void Change_State(void) {
//	Forward_Move();
	if ((ADC_Left_Detect <= TOP_CUTOFF && ADC_Left_Detect >= BOTTOM_CUTOFF) || (ADC_Right_Detect <= TOP_CUTOFF && ADC_Right_Detect >= BOTTOM_CUTOFF)) {
		Motors_Off();
		state = PAUSE;
		switch_state2 = 0;
//		white_counter = 0;
		state_timer = 0;
	}
}

void Line_Up(void) {
        Motors_Off();
        RIGHT_REVERSE_SPEED = LINEUP_RIGHT;
//        LEFT_FORWARD_SPEED = LINEUP_LEFT;
        if ((ADC_Right_Detect <= TOP_ON_LINE && ADC_Right_Detect >= BOTTOM_ON_LINE)) {
            Motors_Off();
            state = WAIT;
//            state = FOLLOW_LINE;
//            state2 = START2;
            state_timer = 0;
            state_flag = 1;
//            state = END;
        }
}

//Forward Functions
void Forward_Move(void) {
//	strcpy(display_line[1], " FORWARD  ");
//	display_changed = TRUE;
//	lcd_BIG_mid();
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = SLOW_RIGHT;
    LEFT_FORWARD_SPEED = SLOW_LEFT;
}

void Forward_Search (void) {
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = SEARCH_RIGHT;
    LEFT_FORWARD_SPEED = SEARCH_LEFT;
}

void Forward_Slow(void) {
//    strcpy(display_line[1], "  FORWARD ");
//    strcpy(display_line[2], "   SLOW   ");
//    display_changed = TRUE;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = BOT;
    LEFT_FORWARD_SPEED = BOT;
}


//Reverse Functions
void Reverse_Move(void) {
//	strcpy(display_line[1], " REVERSE  ");
//	display_changed = TRUE;
//	lcd_BIG_mid();
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = SLOW_RIGHT;
    LEFT_REVERSE_SPEED = SLOW_LEFT;
}

//Turn Functions

void Turn_Right(void) {
//    strcpy(display_line[2], "  RIGHT   ");
//	display_changed = TRUE;
//	lcd_BIG_mid();
	RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = SLOWEST_LEFT;
}

void Turn_Right_IOT (void) {
	RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = SLOW_LEFT;
}
void Turn_Left(void) {
//    strcpy(display_line[2], "  LEFT   ");
//	display_changed = TRUE;
//	lcd_BIG_mid();
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = SLOWEST_RIGHT;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
}

void Turn_Left_IOT (void) {
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = SLOW_RIGHT;
    LEFT_FORWARD_SPEED = WHEEL_OFF;

}

void Turn_In(void) {
    Motors_Off();
    RIGHT_REVERSE_SPEED = SLOW_RIGHT;
    LEFT_FORWARD_SPEED = SLOW_LEFT;
}

void Arch (void) {
//    Motors_Off();
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = ARCH_RIGHT;
    LEFT_FORWARD_SPEED = ARCH_LEFT;
}
void Wait (void) {
//	strcpy(display_line[1], "   WAIT   ");
	display_changed = TRUE;
	lcd_BIG_mid();
}

//Display clock function
void Display_Clock(void) {
        circle_timer_s2 = circle_timer_s;
        HEXtoBCD_TIMER(circle_timer_s2); // Convert result to String
        adc_line_timer(3, 0); // Place String in Display
}

void Course_Timer(void) {
	course_timer2 = course_timer;
    HEXtoBCD_TIMER(course_timer); // Convert result to String
    adc_line_timer(2, 5); // Place String in Display
}

