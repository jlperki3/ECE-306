//------------------------------------------------------------------------------
//
//  Description: This file contains the serial code
//
//
//  Josh Perkins
//  Jan 2023
//  Built with TI Code Composer Studio 12.2.0
//------------------------------------------------------------------------------
#include "functions.h"
#include "msp430.h"
#include "string.h"
#include "macros.h"

extern char pb_index;               // Index for process_buffer
extern char process_buffer_T[DISPLAY_LENGTH];     // Size for appropriate Command Length
extern volatile unsigned char PC_2_IOT[SMALL_RING_SIZE];
extern volatile unsigned char IOT_2_PC[SMALL_RING_SIZE];
extern char process_buffer_R[FIVE][DISPLAY_LENGTH];
unsigned int last;
extern char IOT_Data[BUFFER_COUNT][BUFF_SIZE];
extern unsigned int line;
extern unsigned int print_flag;
extern volatile unsigned char iot_TX_buf[BUFF_SIZE];
extern volatile unsigned char usb_TX_buf[BUFFER_COUNT][DISPLAY_LENGTH];
extern unsigned int iot_tx;
char ip_address[IP_LENGTH];
char ssid[SSID_LENGTH];
unsigned int two_dots = 0;
char security[] = "3857";
char command[SIX];
extern char move_direction;
unsigned int command_count = 0;
unsigned int command_number = 0;
extern unsigned int running_flag;
//unsigned int start_command = START_COMMAND;

void Init_Serial_UCA0(char speed){
//------------------------------------------------------------------------------
// TX error (%) RX error (%)
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
// 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
// 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
// 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
// 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
// 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
//------------------------------------------------------------------------------
// Configure eUSCI_A0 for UART mode
    UCA0CTLW0 = 0;
    UCA0CTLW0 |= UCSWRST ; // Put eUSCI in reset
    UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
    UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
    UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
    UCA0CTLW0 &= ~UCPEN; // No Parity
    UCA0CTLW0 &= ~UCSYNC;
    UCA0CTLW0 &= ~UC7BIT;
    UCA0CTLW0 |= UCMODE_0;
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
// UCA?MCTLW = UCSx + UCFx + UCOS16
    UCA0BRW = 4 ; // 115,200 baud
    UCA0MCTLW = 0x5551 ;
    UCA0CTLW0 &= ~UCSWRST ; // release from reset
//    UCA0TXBUF = 0x00; // Prime the Pump
    UCA0IE |= UCRXIE; // Enable RX interrupt
    UCA0IE &= ~UCTXIE; // Disable TX interrupt

//------------------------------------------------------------------------------
}

void Init_Serial_UCA1(char speed){
//------------------------------------------------------------------------------
// TX error (%) RX error (%)
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
// 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
// 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
// 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
// 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
// 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
//------------------------------------------------------------------------------
// Configure eUSCI_A0 for UART mode
    UCA1CTLW0 = 0;
    UCA1CTLW0 |= UCSWRST ; // Put eUSCI in reset
    UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
    UCA1CTLW0 &= ~UCMSB; // MSB, LSB select
    UCA1CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
    UCA1CTLW0 &= ~UCPEN; // No Parity
    UCA1CTLW0 &= ~UCSYNC;
    UCA1CTLW0 &= ~UC7BIT;
    UCA1CTLW0 |= UCMODE_0;
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
// UCA?MCTLW = UCSx + UCFx + UCOS16
    UCA1BRW = 4; // 115,200 baud
    UCA1MCTLW = 0x5551;
    UCA1CTLW0 &= ~UCSWRST; // release from reset
//    UCA1TXBUF = 0x00; // Prime the Pump
    UCA1IE |= UCRXIE; // Enable RX interrupt
    UCA1IE &= ~UCTXIE; // Disable TX interrupt
//------------------------------------------------------------------------------
}

void USCI_A0_transmit(void){ // Transmit Function for USCI_A0
// Contents must be in process_buffer
// End of Transmission is identified by NULL character in process_buffer
// process_buffer includes Carriage Return and Line Feed
    pb_index = 0;       // Set Array index to first location
    UCA0IE |= UCTXIE;   // Enable TX interrupt
}

void USCI_A1_transmit(void){ // Transmit Function for USCI_A0
// Contents must be in process_buffer
// End of Transmission is identified by NULL character in process_buffer
// process_buffer includes Carriage Return and Line Feed

    //strcpy(PC_2_IOT, process_buffer_T); //Put the contents of the process buffer into the PC_2_IOT array
    pb_index = 0;       // Set Array index to first location
    UCA1IE |= UCTXIE;   // Enable TX interrupt
}

void print_USB(void) {
    for (int i = 0; i < sizeof(PC_2_IOT); i++) {
        display_line[0][i] = process_buffer_R[0][i];
        display_changed = TRUE;
    }
}

void print_IOT(unsigned int thisLine) {
    //strcpy(display_line[0], " RECEIVED ");
    //strcpy(display_line[3], "          ");
//    for (int i = 0; i < sizeof(iot_TX_buf[line]); i++) {
//        if (iot_TX_buf[line][i] == 0x00) {
//            print_flag = i;
//            break;
//        }
//        display_line[thisLine][i] = iot_TX_buf[line][i];
//    }
//    for (int i = print_flag; i < sizeof(iot_TX_buf[line]); i++) {
//            display_line[thisLine][i] = ' ';
//    }
//    print_flag = 0;
//    display_changed = TRUE;
}

void populate (void) {
	if (iot_TX_buf[0] == '+') {
		if (iot_TX_buf[5] == 'P' && iot_TX_buf[6] == ':' && iot_TX_buf[7] == '"') {
				int x = 8;
				int y = 0;
				while (iot_TX_buf[x] != '"') {
					ssid[y] = iot_TX_buf[x];
					x++;
					y++;
				}
				for (int i = 0; i < sizeof(ssid); i++) {
					display_line[0][i+3] = ssid[i];
				}
				display_changed = TRUE;
		}
		if (iot_TX_buf[10] == 'I' && iot_TX_buf[11] == 'P' && iot_TX_buf[13] == '"') {
				int j = 14;
				int i = 0;
				//IP_found = 1;
				while (iot_TX_buf[j] != '"') {
					ip_address[i] = iot_TX_buf[j];
					j++;
					i++;
				}
				ip_address[i] = iot_TX_buf[j];
				//line above puts the quote at the end of the ip address
				strcpy(display_line[1], "IP address");
				int a = 0;
				int b = 0;
				while (two_dots != 2) {
					display_line[2][a+2] = ip_address[a];
					if (ip_address[a] == '.') two_dots++;
					a++;
				}
				b = a;
				a = 0;
				while (ip_address[b] != '"') {
					display_line[3][a+2] = ip_address[b];
					a++;
					b++;
				}
				display_changed = TRUE;
		}
	}
}

void Count_Commands (void) {
	command_count = 0;
	for (int i = 0; i < sizeof(iot_TX_buf); i++) {
		if (iot_TX_buf[i] == '!') command_count++;
	}
}

void Parse_Command (void) {
	if (iot_TX_buf[0] == '+' && iot_TX_buf[1] == 'I' && iot_TX_buf[2] == 'P' && iot_TX_buf[3] == 'D') {
		if (iot_TX_buf[10] == '!' && iot_TX_buf[11] == security[0] && iot_TX_buf[12] == security[1] && iot_TX_buf[13] == security[2] && iot_TX_buf[14] == security[3]) {
			for (int i = 0; i < sizeof(command); i++) {
				command[i] = iot_TX_buf[i+15];		//Puts the direction and time of the first command into the array
			}
			for (int i = 3; i < sizeof(command); i++) {
				command[i] = iot_TX_buf[i+20];		//Puts the direction and time of the second command into the array
			}
			 for (int i = 0; i < sizeof(iot_TX_buf); i++) {
				 iot_TX_buf[i] = 0x00;
			 }
			move_direction = START;
		}
	}
}

void Send_2_IOT (char command[]) {
	strcpy(iot_TX_buf, command);
	iot_tx = 0;
	UCA0IE |= UCTXIE;
}
