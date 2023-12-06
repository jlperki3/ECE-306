/*
 * statemachines.c
 *
 *  Created on: Feb 7, 2023
 *      Author: joshperkins
 */
#include "functions.h"
#include "macros.h"
#include "msp430.h"
#include "string.h"
#include "stdlib.h"
extern char state;
extern char state2;
extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;
extern unsigned int state_timer;
char last_state;
extern char IOT_State;
extern volatile unsigned char IOT_Ring_Rx[DISPLAY_LENGTH];
extern unsigned int iot_rx_wr;
char stop_save[] = "AT+SYSSTORE=0\r\n";
char multi_connect[] = "AT+CIPMUX=1\r\n";
char server_config[] = "AT+CIPSERVER=1,7999\r\n";
char get_ssid[] = "AT+CWJAP?\r\n";
char get_ip[] = "AT+CIFSR\r\n";
char ping[] = "AT+PING=\"www.google.com\"\r\n";
char pad_numbers[] = "012345678";
//char at[2] = "AT";
char last_IOT_state;
extern volatile unsigned char iot_TX_buf[BUFF_SIZE];
extern unsigned int IOT_flag;
unsigned int IOT_timer;
extern unsigned int onetime;
extern unsigned int newline_flag;
char move_direction = NONE;
unsigned int move_time = 0;
unsigned int movement_timer = 0;
extern char command[SIX];
extern unsigned int command_number;
char prev_state = NONE;
extern unsigned int five_seconds;
unsigned int pad_counter = 0;
unsigned int flag = 0;
unsigned int flag1 = 0;
unsigned int ping_flag = 0;
unsigned int process_state = 0;
extern unsigned int command_flag;
extern unsigned int course_timer;
unsigned int course_timer_helper = 0;
unsigned int arch_flag = 0;
unsigned int run_forward_flag = 0;
extern unsigned int white_counter;
extern unsigned int end_timer;
unsigned int end_flag;
extern unsigned int state_flag;
char LAST = NONE;

void Run_Forward(void){
    switch(state){
         case START: //Set all wheel speeds to off
//          Motors_Off();
             strcpy(display_line[0], " BL Start ");
             display_changed = TRUE;
        	 if (state_timer >= WAIT_TIME) {
        		 state = FORWARD;
        		 state_timer = 0;
        	 }
          break; //
//----------------------------------------------------------------------------
         case FORWARD: //set the car going straight forward
             P2OUT |= IR_LED;            // Initial Value = Low / Off
             Arch();
             if (state_timer >= WAIT_2_DETECT) {
				 if (ADC_Left_Detect <= WHITE || ADC_Right_Detect <= WHITE) {
					 white_counter++;
				 }
				 if (white_counter == COUNT_WHITE) {
					 state = FOUND_WHITE;
					 white_counter = 0;
					 state_timer = 0;
				     Motors_Off();
				 }
             }
             arch_flag = 1;
          break; //
//----------------------------------------------------------------------------
	   case FOUND_WHITE: //Shift car right
           strcpy(display_line[0], "  White  ");
           if (state_timer >= THREE_SECONDS) {
           Forward_Search();
           Change_State();  //Check sensor values to decide if the car should stop
           }
		break; //
//----------------------------------------------------------------------------

         case WAIT: //Shift car right
        	 Motors_Off();
        	 if (state_timer >= WAIT_TIME && state_flag == 1) {
        		 state_timer = 0;
                 state = FOLLOW_LINE;
                 state2 = START2;
        	 }
        	 if (state_timer >= WAIT_TIME && state_flag == 2) {
        		 state_timer = 0;
        		 state = FOLLOW_LINE;
        		 state2 = LAST;
        	 }
          break; //
//----------------------------------------------------------------------------
         case PAUSE: //This state stops the car for five seconds after it detects black line
        	 if (state_timer >= WAIT_TIME) {
        		 state = LINE_UP;
        	 }
             Motors_Off();
             strcpy(display_line[0], "Intercept ");
             display_changed = TRUE;

          break; //
//----------------------------------------------------------------------------
         case LINE_UP: //Shift car right
             strcpy(display_line[0], " BL TURN  ");
//             strcpy(display_line[2], "    UP    ");
             display_changed = TRUE;
             Line_Up();
          break; //
//----------------------------------------------------------------------------
         case FOLLOW_LINE:
        	 if (state_timer >= WAIT_4_CIRCLE && state_flag == 1) {
                 strcpy(display_line[0], "BL Circle ");
                 display_changed = TRUE;
        		 state_flag = 2;
        		 state_timer = 0;
        		 state = WAIT;
        		 state2 = NONE;
        	 }
             switch (state2) {
                 case START2:
                    strcpy(display_line[0], "BL Travel ");
//                    strcpy(display_line[2], "          ");
                    display_changed = TRUE;
                    if (ADC_Right_Detect >= TOP_ON_LINE || ADC_Right_Detect <= BOTTOM_ON_LINE) state2 = TURN_RIGHT; 	// if right sensor is on white turn right
                    if (ADC_Left_Detect >= TOP_ON_LINE || ADC_Left_Detect <= BOTTOM_ON_LINE) state2 = TURN_LEFT; 		// if left sensor is on left turn left
                    // if both are on black line go straight
                    if ((ADC_Right_Detect <= TOP_ON_LINE && ADC_Right_Detect >= BOTTOM_ON_LINE) && (ADC_Left_Detect <= TOP_ON_LINE && ADC_Left_Detect >= BOTTOM_ON_LINE)) state2 = STRAIGHT;
                    if ((ADC_Right_Detect < BOTTOM_ON_LINE) && (ADC_Left_Detect < BOTTOM_ON_LINE)) state2 = TURN_RIGHT; // if both are on white turn right
                    break;
                 case STRAIGHT:
                     Forward_Slow();
                     if (ADC_Right_Detect >= TOP_ON_LINE || ADC_Right_Detect <= BOTTOM_ON_LINE) state2 = TURN_LEFT;		// if right sensor is on white turn left
                     if (ADC_Left_Detect >= TOP_ON_LINE || ADC_Left_Detect <= BOTTOM_ON_LINE) state2 = TURN_RIGHT;		// if left sensor is on white turn right
                     // if both are on black line continue straight
                     if ((ADC_Right_Detect <= TOP_ON_LINE && ADC_Right_Detect >= BOTTOM_ON_LINE) && (ADC_Left_Detect <= TOP_ON_LINE && ADC_Left_Detect >= BOTTOM_ON_LINE)) state2 = STRAIGHT;
                     LAST = STRAIGHT;
                  break; //
                 case TURN_RIGHT:
                     Turn_Right();		// turning right
                     if (ADC_Right_Detect >= TOP_ON_LINE || ADC_Right_Detect <= BOTTOM_ON_LINE) state2 = TURN_LEFT;	// if right sensor is on white turn left
                     // if both are on black line continue straight
                     if ((ADC_Right_Detect <= TOP_ON_LINE && ADC_Right_Detect >= BOTTOM_ON_LINE) && (ADC_Left_Detect <= TOP_ON_LINE && ADC_Left_Detect >= BOTTOM_ON_LINE)) state2 = STRAIGHT;
                     if ((ADC_Right_Detect < BOTTOM_ON_LINE) && (ADC_Left_Detect < BOTTOM_ON_LINE)) state2 = TWO_WHITE; // if both are on white go two_white
                     last_state = TURN_RIGHT;
                     LAST = TURN_RIGHT;
                  break; //
                 case TURN_LEFT:
                     Turn_Left();		// turning left
                     if (ADC_Left_Detect >= TOP_ON_LINE || ADC_Left_Detect <= BOTTOM_ON_LINE) state2 = TURN_RIGHT;	// if left sensor is on white turn right
                     // if both are on black line continue straight
                     if ((ADC_Right_Detect <= TOP_ON_LINE && ADC_Right_Detect >= BOTTOM_ON_LINE) && (ADC_Left_Detect <= TOP_ON_LINE && ADC_Left_Detect >= BOTTOM_ON_LINE)) state2 = STRAIGHT;
                     if ((ADC_Right_Detect < BOTTOM_ON_LINE) && (ADC_Left_Detect < BOTTOM_ON_LINE)) state2 = TWO_WHITE; // if both are on white go two_white
                     last_state = TURN_LEFT;
                     LAST = TURN_LEFT;
                  break; //
                 case TWO_WHITE:
                     if (last_state == TURN_RIGHT) state2 = TURN_RIGHT;
                     if (last_state == TURN_LEFT) state2 = TURN_LEFT;
                     LAST = TWO_WHITE;
                  break;
                 default: break;
             }
          break; //
//----------------------------------------------------------------------------
          case TURN_IN:
              strcpy(display_line[0], " TURN IN  ");
              display_changed = TRUE;
              Turn_In();
           break;
//----------------------------------------------------------------------------
          case GO_MIDDLE:
              strcpy(display_line[0], "GO MIDDLE ");
              display_changed = TRUE;
              Forward_Move();
           break;
//----------------------------------------------------------------------------
         case END: // End
             Motors_Off();
             strcpy(display_line[0], " BL Exit  ");
             display_changed = TRUE;
             state = NONE;
          break; //
          default: break;
//----------------------------------------------------------------------------
     }
}

void Configure_IOT (void) {
	switch (IOT_State) {
	 case WAIT:
		 last_IOT_state = WAIT;
		 if (IOT_flag == 1 && iot_TX_buf[9] == 'I' && iot_TX_buf[10] == 'P') {
			 IOT_State = FORTY_NINE;
			 IOT_flag = 0;
			 IOT_timer = 0;
		 }
	 break;
 //----------------------------------------------------------------------------
	 case PAUSE:
		 if(iot_TX_buf[0] == 'O' && iot_TX_buf[1] == 'K' && last_IOT_state == FORTY_NINE) {
			 IOT_State = FIFTY;
			 for (int i = 0; i < sizeof(iot_TX_buf); i++) {
				 iot_TX_buf[i] = 0x00;
			 }
		 }
		 if(iot_TX_buf[0] == 'O' && iot_TX_buf[1] == 'K' && last_IOT_state == FIFTY) {
			 IOT_State = FIFTY_ONE;
			 for (int i = 0; i < sizeof(iot_TX_buf); i++) {
				 iot_TX_buf[i] = 0x00;
			 }
		 }
		 if(iot_TX_buf[0] == 'O' && iot_TX_buf[1] == 'K' && last_IOT_state == FIFTY_ONE) {
			 IOT_State = SSID;
			 for (int i = 0; i < sizeof(iot_TX_buf); i++) {
				 iot_TX_buf[i] = 0x00;
			 }
		 }
		 if(iot_TX_buf[0] == '+' && iot_TX_buf[1] == 'C' && iot_TX_buf[2] == 'W' && iot_TX_buf[3] == 'J' && iot_TX_buf[4] == 'A' && iot_TX_buf[5] == 'P' && last_IOT_state == SSID) {
			 IOT_State = IP_ADDRESS;
			 for (int i = 0; i < sizeof(iot_TX_buf); i++) {
				 iot_TX_buf[i] = 0x00;
			 }
		 }
		 if(iot_TX_buf[0] == 'O' && iot_TX_buf[1] == 'K' && last_IOT_state == IP_ADDRESS) {
			 onetime = 1;
		     newline_flag = 0;
			 IOT_State = END;
			 P2OUT |= IOT_RUN_RED;
			 for (int i = 0; i < sizeof(iot_TX_buf); i++) {
				 iot_TX_buf[i] = 0x00;
			 }
		 }
		 if(iot_TX_buf[0] == 'O' && iot_TX_buf[1] == 'K' && last_IOT_state == END) {
			 for (int i = 0; i < sizeof(iot_TX_buf); i++) {
				 iot_TX_buf[i] = 0x00;
			 }
			 ping_flag = 1;
		 }
		 if (five_seconds >= 80 && last_IOT_state == END && ping_flag == 1) {
			 IOT_State = END;
			 ping_flag = 0;
		 }
	 break;
 //----------------------------------------------------------------------------
	 case FORTY_NINE:
		 if (IOT_timer >= TWO) {
		 Send_2_IOT(stop_save);
		 last_IOT_state = FORTY_NINE;
		 IOT_State = PAUSE;
		 IOT_timer = 0;
		 }
     break;
 //----------------------------------------------------------------------------
	 case FIFTY:
		 if (IOT_timer >= TWO) {
		 Send_2_IOT(multi_connect);
		 last_IOT_state = FIFTY;
		 IOT_State = PAUSE;
		 IOT_timer = 0;
		 }
	 break;
//----------------------------------------------------------------------------
	 case FIFTY_ONE:
		 if (IOT_timer >= TWO) {
		 Send_2_IOT(server_config);
		 last_IOT_state = FIFTY_ONE;
		 IOT_State = PAUSE;
		 IOT_timer = 0;
		 }
	 break;
//----------------------------------------------------------------------------
	 case SSID:
		 if (IOT_timer >= SEVEN) {
		 Send_2_IOT(get_ssid);
		 last_IOT_state = SSID;
		 IOT_State = PAUSE;
		 IOT_timer = 0;
		 }
	 break;
//----------------------------------------------------------------------------
	 case IP_ADDRESS:
		 if (IOT_timer >= SEVEN) {
		 Send_2_IOT(get_ip);
		 last_IOT_state = IP_ADDRESS;
		 IOT_State = PAUSE;
		 IOT_timer = 0;
		 }
	 break;
//----------------------------------------------------------------------------
	 case END:
		 if (IOT_timer >= SEVEN) {
		 Send_2_IOT(ping);
		 P2OUT ^= IOT_RUN_RED;
		 last_IOT_state = END;
		 IOT_State = PAUSE;
		 five_seconds = 0;
		 IOT_timer = 0;
		 }
	 break;
//----------------------------------------------------------------------------
	 default: break;
//----------------------------------------------------------------------------
	}
}

void IOT_Command (void) {
	char temp[2];
	switch (move_direction) {
	 case START:
		Motors_Off();
		flag1 = 1;
//		strcpy(display_line[0], "          ");
		strcpy(display_line[1], "          ");
		strcpy(display_line[0], "Arrived   ");
		display_line[0][8] = pad_numbers[pad_counter];
		display_changed = TRUE;
		move_direction = command[0];
		temp[0] = command[1];
		temp[1] = command[2];
		move_time = atoi(temp);
		if (move_time == 11) movement_timer = 1; //.25 seconds at .25 second increments
		if (move_time == 10) movement_timer = 4; //1 second at .25 second increments
		if (move_time == 13) movement_timer = 5; //1.25 second at .25 second increments
		if (move_time == 15) movement_timer = 6; //1.5 seconds at .25 second increments
		if (move_time == 18) movement_timer = 7; //1.75 seconds at .25 second increments
		if (move_time == 20) movement_timer = 8; //2 seconds at .25 second increments
		if (move_time == 23) movement_timer = 9; //1.5 seconds at .25 second increments
		if (move_time == 25) movement_timer = 10; //2.5 seconds at .25 second increments
		if (move_time == 28) movement_timer = 11; //1.5 seconds at .25 second increments
		if (move_time == 30) movement_timer = 12; //3 seconds at .25 second increments
		if (move_time == 60) movement_timer = 24; //6 seconds at .25 second increments
	 break;
//----------------------------------------------------------------------------
	case START2:
		Motors_Off();
		move_direction = command[3];
		temp[0] = command[4];
		temp[1] = command[5];
		move_time = atoi(temp);
		if (move_time == 11) movement_timer = 1; //.25 seconds at .25 second increments
		if (move_time == 10) movement_timer = 4; //1 second at .25 second increments
		if (move_time == 13) movement_timer = 5; //1.25 second at .25 second increments
		if (move_time == 15) movement_timer = 6; //1.5 seconds at .25 second increments
		if (move_time == 18) movement_timer = 7; //1.75 seconds at .25 second increments
		if (move_time == 20) movement_timer = 8; //2 seconds at .25 second increments
		if (move_time == 23) movement_timer = 9; //1.5 seconds at .25 second increments
		if (move_time == 25) movement_timer = 10; //2.5 seconds at .25 second increments
		if (move_time == 28) movement_timer = 11; //1.5 seconds at .25 second increments
		if (move_time == 30) movement_timer = 15; //3 seconds at .25 second increments
		if (move_time == 60) movement_timer = 24; //6 seconds at .25 second increments
		prev_state = START2;
	break;
//----------------------------------------------------------------------------
	 case WAIT:
//		 Motors_Off();///////////////////////////////////////////////////////////////////////////////
//	 	 strcpy(display_line[1], "   WAIT   ");
//		 display_changed = TRUE;
	 break;
//----------------------------------------------------------------------------
	 case FORWARD:
		 Motors_Off();
//	 	 strcpy(display_line[1], " FORWARD  ");
//		 display_changed = TRUE;
		 Forward_Move();
		 move_direction = PAUSE;
	 break;
//----------------------------------------------------------------------------
	 case BACK:
		 Motors_Off();
//	 	 strcpy(display_line[1], " REVERSE  ");
//		 display_changed = TRUE;
		 Reverse_Move();
		 move_direction = PAUSE;
	 break;
//----------------------------------------------------------------------------
	 case TURN_RIGHT:
		 Motors_Off();
//	 	 strcpy(display_line[1], "  RIGHT   ");
//		 display_changed = TRUE;
		 Turn_Right_IOT();
		 move_direction = PAUSE;
	 break;
//----------------------------------------------------------------------------
	 case TURN_LEFT:
		 Motors_Off();
//	 	 strcpy(display_line[1], "   LEFT   ");
//		 display_changed = TRUE;
		 Turn_Left_IOT();
		 move_direction = PAUSE;
	 break;

//----------------------------------------------------------------------------
	 case PAUSE:
		 if (movement_timer > 0) {
			  move_direction = PAUSE;
		 }
		 if (movement_timer == 0 && arch_flag == 0) {
			 Motors_Off();
			 for (int i = 0; i < 3; i++) {
				 display_line[1][i] = command[i];
			 }
		        display_changed = TRUE;

			 if (command[3] == 0x00) { // no second command
				 move_direction = WAIT;
				 for (int i = 0; i < sizeof(command); i++) {
					 command[i] = 0x00;
				 }
			 }
			 if (command[3] != 0x00 && prev_state != START2) {
				 move_direction = START2;
			 }
			 if (command[3] != 0x00 && prev_state == START2) {
				 prev_state = NONE;
				 move_direction = WAIT;
				 for (int i = 0; i < 3; i++) {
					 display_line[1][i] = command[i+3];
				 }
			        display_changed = TRUE;
				 for (int i = 0; i < sizeof(command); i++) {
					 command[i] = 0x00;
				 }
			 }
		 }
		 if (arch_flag == 1) {
//			 Motors_Off();///////////////////////////////////////////////////////////////////////////////
			 for (int i = 0; i < 3; i++) {
				 display_line[1][i] = command[i];
			 }
				display_changed = TRUE;

			 if (command[3] == 0x00) { // no second command
				 move_direction = WAIT;
				 for (int i = 0; i < sizeof(command); i++) {
					 command[i] = 0x00;
				 }
		 }

	 break;
//----------------------------------------------------------------------------
	 case NEXT_PAD:
		 Motors_Off();
		 pad_counter++;
		 if (pad_counter > 8) pad_counter = 0;
		 display_line[0][8] = pad_numbers[pad_counter];
		 display_changed = TRUE;
		 move_direction = PAUSE;
	 break;
	 //----------------------------------------------------------------------------
	 case FIND_LINE:
		 TB2CCTL1 |= CCIE; // CCR1 enable interrupt
		 state = START;
		 state_timer = 0;
		 move_direction = PAUSE;
		 run_forward_flag = 1;
	 break;
//----------------------------------------------------------------------------
	 case END:
		 Motors_Off();
		 state_timer = 0;
		 state = END;
		 state2 = END;
		 move_direction = FIFTY;

	 break;
//----------------------------------------------------------------------------
	 case FIFTY:
		 if (state_timer >= 50) {
			 Forward_Move();
			 end_timer = 0;
			 move_direction = FORTY_NINE;
		 }

	 break;
//----------------------------------------------------------------------------
	 case FORTY_NINE:
		 if (end_timer >= 25) {
			 arch_flag = 0;
			 run_forward_flag = 0;
			 end_flag = 0;
			 flag = 2;
             strcpy(display_line[0], " BL Stop  ");
             strcpy(display_line[2], "Finally I ");
             strcpy(display_line[3], "Can Sleep ");
             display_changed = TRUE;
			 Motors_Off();
			 move_direction = PAUSE;
		 }

	 break;
//----------------------------------------------------------------------------
	 default: break;
//----------------------------------------------------------------------------
		 }
	}
}

void Process_State (void) {
    if (newline_flag == 0 && command_flag == 0) { //Nothing to process yet
    	process_state = 3;
    }
    if (newline_flag == 1 && onetime == 0) { //ALL startup stuff
    process_state = 0;
    newline_flag = 0;
    }
    if (newline_flag == 1 && command_flag == 0 && onetime == 1) { //0,CONNECT for example
    	process_state = 1;
    	newline_flag = 0;
    }
    if (newline_flag == 1 && command_flag == 1) { 		//Command received process and parse it
    	process_state = 2;
    	newline_flag = 0;
    	command_flag = 0;
    	command_number = 1;
    }
    switch (process_state) {
    case 0:
    	IOT_Process();
    	populate();
    break;
    case 1:
    	IOT_Process();
	break;
    case 2:
    	IOT_Process();
    	Count_Commands();
    	Parse_Command();
	break;
    case 3:
	break;
    default: break;
    }
}

void Start_Course (void) {
	switch (flag) {
	case 0:
		if (flag1 > 0) {
			flag = 1;
			course_timer = 0;
		}
	break;
	case 1:
		if (course_timer_helper >= 2) {
		Course_Timer();
		course_timer_helper = 0;
		}
	break;
	case 2:

	break;
	default: break;
	}
}


