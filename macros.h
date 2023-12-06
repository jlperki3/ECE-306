//------------------------------------------------------------------------------
//
//  Description: This file contains the macro definitions
//
//
//  Josh Perkins
//  Jan 2023
//  Built with TI Code Composer Studio 12.2.0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#ifndef HOMEWORK03_MACROS_H
#define HOMEWORK03_MACROS_H

#define ALWAYS              (1)
#define RESET_STATE         (1)
#define RED_LED             (0x01)
#define GRN_LED             (0x40)
#define TRUE                (0x01)
#define TEST_PROBE          (0x01)

// Port 1 Pins
#define RED_LED (0x01) // 0 RED LED 0
#define A1_SEEED (0x02) // 1 A1_SEEED
#define V_DETECT_L (0x04) // 2 V_DETECT_L
#define V_DETECT_R (0x08) // 3 V_DETECT_R
#define A4_SEEED (0x10) // 4 A4_SEEED
#define V_THUMB (0x20) // 5 V_THUMB
#define UCA0RXD (0x40) // 6 Back Channel UCA0RXD
#define UCA0TXD (0x80) // 7 Back Channel UCA0TXD

// Port 2 Pins
#define RESET_LCD (0x01) // 0 RESET LCD
#define CHECK_BAT (0x02) // 1 Check ADC Voltages
#define IR_LED (0x04) // 2 IR_LED
#define SW2 (0x08) // 3 SW2
#define IOT_RUN_RED (0x10) // 4 IOT_RUN_RED
#define DAC_ENB (0x20) // 5 DAC_ENB
#define LFXOUT (0x40) // 6 XOUTR
#define LFXIN (0x80) // 7 XINR
#define P2PUD (P2OUT)

// Port 3 Pins
#define TEST_PROBE (0x01) // 0 TEST PROBE
#define OA2O (0x02) // 1 OA2O
#define OA2N (0x04) // 2 OA2N
#define OA2P (0x08) // 3 OA2P
#define SMCLK (0x10) // 4 SMCLK
#define DAC_CNTL (0x20) // 5 DAC signal from Processor
#define IOT_LINK_GRN (0x40) // 6 IOT_LINK_GRN
#define IOT_EN (0x80) // 7 IOT_EN

// Port 4 Pins
#define DAC_CNTL1 (0x01) // 0 DAC_CNTR1
#define SW1 (0x02) // 1 SW1
#define UCA1RXD (0x04) // 2 Back Channel UCA1RXD
#define UCA1TXD (0x08) // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD (0x10) // 4 Chip Select
#define UCB1CLK (0x20) // 5 SPI mode - clock output—UCB1CLK
#define UCB1SIMO (0x40) // 6 UCB1SIMO
#define UCB1SOMI (0x80) // 7 UCB1SOMI
#define P4PUD (P4OUT)

//Port 5 Pins
#define V_BAT (0x01)
#define V_5_0 (0x02)
#define V_DAC (0x04)
#define V_3_3 (0x08)
#define IOT_BOOT_CPU (0x10)

//Port 6 Pins
#define LCD_BACKLITE (0x01)
#define R_FORWARD (0x02)
#define R_REVERSE (0x04)
#define L_FORWARD (0x08)
#define L_REVERSE (0x10)
#define P6_5 (0x20)
#define GRN_LED (0x40)

// STATES ======================================================================Z
#define NONE 			('N')
#define WAIT 			('W')
#define START 			('S')
#define FOLLOW_LINE 	('O')
#define LINE_UP 		('U')
#define TURN_IN 		('T')
#define REVERSE 		('X')
#define FORWARD 		('F')
#define PAUSE 			('P')
#define END 			('E')
#define GO_MIDDLE 		('G')
#define NEXT_PAD		('V')
#define FIND_LINE		('Y')
#define FOUND_WHITE		('Z')
// STATES2
#define TURN_RIGHT 		('R')
#define TURN_LEFT 		('L')
#define STRAIGHT 		('A')
#define BACK			('B')
#define START2 			('Q')
#define TWO_WHITE 		('C')

// IOT STATES
#define FORTY_NINE 		('D')
#define FIFTY 			('H')
#define FIFTY_ONE 		('I')
#define SSID 			('J')
#define IP_ADDRESS		('K')

// Switches
#define PRESSED                  (0)
#define OKAY                     (1)
#define RELEASED                 (1)
#define NOT_OKAY                 (0)
#define DEBOUNCE_RESTART         (0)
#define DEBOUNCE_TIME            (10)


//timer B0 configuration
#define TB0CCR0_INTERVAL (50000)
#define TB0CCR1_INTERVAL (50000)
#define TB0CCR2_INTERVAL (50000)

//timer B0 configuration
#define TB2CCR0_INTERVAL (62500)
#define TB2CCR1_INTERVAL (25000)
#define TB2CCR2_INTERVAL (50000)

//timer B3 configuration
#define WHEEL_OFF 		 (0)

#define SLOWEST_RIGHT    (9000)
#define SLOWEST_LEFT     (11000)

#define ARCH_LEFT		 (18750)
#define ARCH_RIGHT       (22500)

#define SLOW_RIGHT       (19000)
#define SLOW_LEFT        (25000)

#define SEARCH_RIGHT	 (10000)
#define SEARCH_LEFT		 (12000)

#define LINEUP_RIGHT	 (10000)
#define LINEUP_LEFT		 (10000)

#define PERCENT_100      (50000)
#define PERCENT_80       (45000)
#define PERCENT_50		 (25000)

#define WHEEL_PERIOD     (50005)
#define BOT              (9000)

//numbers
#define THOUSANDS   (1000)
#define HUNDREDS    (100)
#define TENS        (10)
#define ONES        (1)

//PWM
#define PWM_PERIOD          (TB3CCR0)
#define LCD_BACKLITE_DIMING (TB3CCR1)
#define RIGHT_FORWARD_SPEED (TB3CCR4)
#define RIGHT_REVERSE_SPEED (TB3CCR5)
#define LEFT_FORWARD_SPEED  (TB3CCR2)
#define LEFT_REVERSE_SPEED  (TB3CCR3)

//Sensor Ranges
#define TOP_CUTOFF       (950)
#define BOTTOM_CUTOFF    (200)

#define TOP_ON_LINE      (1000)
#define BOTTOM_ON_LINE   (500)

//#define TOP_ON_LINE      (900)
//#define BOTTOM_ON_LINE   (450)

#define WHITE			 (64)

//Timer
#define TRAVEL_TIME (350)

//Serial
#define SMALL_RING_SIZE (65)
#define IP_LENGTH		(16)
#define SSID_LENGTH		(10)
#define BUFF_SIZE 		(65)
#define RING_SIZE       (16)
#define RED_LED_ON      (1)
#define GRN_LED_OFF     (0)
#define BEGINNING 		(0)

// IOT Commands
#define START_COMMAND 			(10)
#define COMMAND_DIFFERENCE 		(18)
#define COMMAND_DATA			(15)

//Project 10
#define COUNT_WHITE 			(60)
#define WAIT_TIME				(50)

// mass defs
#define INITIAL_DAC 		(4000)
#define BUFFER_COUNT 		(4)
#define DISPLAY_LENGTH 		(10)
#define	TWO_HUNDRED_MS		(2)
#define TEN_SECONDS			(100)
#define FIFTY_SECONDS		(500)
#define DAC_DECREMENT		(50)
#define FINAL_DAC			(2250)
#define LONG_BUFFER			(40)
#define RING_SIZE			(16)
#define FIVE				(5)
#define ELEVEN				(11)
#define SIX					(6)
#define WAIT_2_DETECT		(37)
#define	THREE_SECONDS		(30)
#define	WAIT_4_CIRCLE		(125)
#define TWO 				(2)
#define	SEVEN				(7)


#endif
