//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Josh Perkins
//  Jan 2023
//  Built with TI Code Composer Studio 12.2.0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include "functions.h"
#include "msp430.h"
#include "string.h"
#include "macros.h"


// Function Prototypes
void main(void);
void Display_Process(void);

// Global Variables
extern char display_line[BUFFER_COUNT][ELEVEN];
extern char *display[BUFFER_COUNT];
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern char state;
unsigned int startup = 0;
unsigned int display_counter = 0;
volatile unsigned int count_debounce_SW1 = DEBOUNCE_RESTART;
volatile unsigned int count_debounce_SW2 = DEBOUNCE_RESTART;
char adc_char[BUFFER_COUNT];
char timer_char[FIVE];
unsigned int switch_state1 = 0;
unsigned int switch_state2 = 0;
unsigned int state_timer = 0;
unsigned int circle_timer_s = 0;
unsigned int circle_timer_s2 = 0;
unsigned int max_right = 0;
unsigned int max_left = 0;
volatile unsigned int usb_rx_ring_wr;
volatile char USB_Char_Rx[SMALL_RING_SIZE];
char RingBuffer[RING_SIZE];
unsigned int ProcessBuf[RING_SIZE];
char process_buffer_T[DISPLAY_LENGTH] = " NCSU  #1\n";
char process_buffer_R[BUFFER_COUNT][DISPLAY_LENGTH];
unsigned int rd;
unsigned int wr;
char serial_init;
unsigned int newline_flag = 0;
extern volatile unsigned int iot_rx_wr;
unsigned int print_flag = 0;
char IOT_State;
extern char last_IOT_state;
unsigned int IOT_flag = 0;
unsigned int onetime = 0;
extern unsigned int command_flag;
unsigned int parse_flag = 0;
extern unsigned int command_number;
extern unsigned int command_count;
extern unsigned int flag;
extern unsigned int course_timer;
extern unsigned int run_forward_flag;


void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    Init_Ports();                // Initialize Ports
    Init_Clocks();               // Initialize Clock System
    Init_Conditions();           // Initialize Variables and Initial Conditions
    Init_Timer_B0();
    Init_Timer_B2();
    Init_Timer_B3();
    Init_ADC();
    Init_LCD();                  // Initialize LCD
    Init_Serial_UCA0(serial_init);
    Init_Serial_UCA1(serial_init);
    Init_DAC();
    Init_REF();

    // Place the contents of what you want on the display, in between the quotes
    // Limited to 10 characters per line
    //strcpy(display_line[0], "   NCSU   ");
    //strcpy(display_line[1], " WOLFPACK ");
    //strcpy(display_line[2], "  ECE306  ");
    //strcpy(display_line[3], "  GP I/O  ");

    // This line identifies the text on the Display is to change.
    display_changed = TRUE;

//------------------------------------------------------------------------------
// Beginning of the "While" Operating System
//------------------------------------------------------------------------------
    state = WAIT;
    IOT_State = WAIT;
    last_IOT_state = WAIT;
    while(ALWAYS) {                        // Can the Operating system run
        Display_Process();                 // Update Display
        P3OUT ^= TEST_PROBE;               // Change State of TEST_PROBE OFF
        Configure_IOT();
        IOT_Command();
        Process_State();
        Start_Course();
        if (run_forward_flag == 1) {
        Run_Forward();                     //call the run forward state machine
        }

        switch (startup) {
         case 10:
            P3SEL0 &= ~IOT_EN;
            P3SEL1 &= ~IOT_EN;
            P3OUT  |=  IOT_EN;
            P3DIR  |=  IOT_EN;
            P3OUT  |=  IOT_LINK_GRN;
            break;
         case 25:
             IOT_flag = 1;
        	 break;
         case 30:
            P6OUT |= LCD_BACKLITE;     //turn on back light after 3 seconds
            switch_state1 = 1;
//            strcpy(display_line[0], " WAITING  ");
//            strcpy(display_line[1], "          ");
//            strcpy(display_line[2], " 115,200  ");
//            strcpy(display_line[3], "          ");
//            display_changed = TRUE;
            break;
         case 45:
        	 TB0CTL |= TBIE;		//Enable overflow interrupt so dac can begin power up
        	 P2OUT |= DAC_ENB;		// enable dac
             break;
         case 150:
//     	     strcpy(display_line[0], " Waiting  ");
//     	     strcpy(display_line[1], "for input ");
             break;
         case 200:
             break;
         default: break;
        }
    }
//------------------------------------------------------------------------------
}

void Display_Process(void){
    if(update_display){
        update_display = 0;
        if(display_changed){
            display_changed = 0;
            Display_Update(0,0,0,0);
        }
    }
}




