//------------------------------------------------------------------------------
//
//  Description: This file contains the serial interrupt definitions
//
//
//  Josh Perkins
//  Feb 2023
//  Built with TI Code Composer Studio 12.2.0
//------------------------------------------------------------------------------

#include "functions.h"
#include "msp430.h"
#include "string.h"
#include "macros.h"

volatile unsigned char IOT_2_PC[SMALL_RING_SIZE];
extern char process_buffer_T[DISPLAY_LENGTH];     // Size for appropriate Command Length
extern char process_buffer_R[DISPLAY_LENGTH];     // Size for appropriate Command Length

char pb_index;               // Index for process_buffer
unsigned int temp;
volatile unsigned char PC_2_IOT[SMALL_RING_SIZE];
volatile unsigned char receive_ring[SMALL_RING_SIZE];
volatile unsigned int usb_rx_wr;
volatile unsigned int iot_rx_wr;
volatile unsigned int iot_rx_rd;
unsigned int usb_rx_rd;
unsigned int direct_usb;
unsigned int direct_iot;
extern char IOT_Data[BUFFER_COUNT][DISPLAY_LENGTH];
extern unsigned int newline_flag;
extern unsigned int line;
volatile unsigned char IOT_Ring_Rx[SMALL_RING_SIZE];
volatile unsigned char iot_TX_buf[BUFF_SIZE];
volatile unsigned char USB_Ring_Rx[SMALL_RING_SIZE];
volatile unsigned char usb_TX_buf[DISPLAY_LENGTH];
extern unsigned int iot_tx;
unsigned int command_flag = 0;


#pragma vector = EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){ //This interrupt is the interrupt relating to serial communication port UCA0
//------------------------------------------------------------------------------
// Interrupt name: eUSCI_A0_ISR
// Description: This interrupt transmits and receives through UCA0
//------------------------------------------------------------------------------
	char iot_receive;
// int temp_char;
// int i;
	switch(__even_in_range(UCA0IV,0x08)){
	case 0: break; //Vector 0 - no interrupt
	case 2:{ // Vector 2 – Rx0IFG
		iot_receive = UCA0RXBUF;
		IOT_Ring_Rx[iot_rx_wr++] = iot_receive; // Add to Ring Buffer
		if(iot_rx_wr >= sizeof(IOT_Ring_Rx)){
			iot_rx_wr = BEGINNING;
		}
        if (iot_receive == 0x0A) {
            newline_flag = 1;
        }
        if (iot_receive == '!') {
        	command_flag = 1;
        }
		// UCA1IE |= UCTXIE;
		UCA1TXBUF = iot_receive;
	}break;
	case 4:{ // Vector 4 – Tx0IFG
		UCA0TXBUF = iot_TX_buf[iot_tx];
		iot_TX_buf[iot_tx++] = 0;
		if(iot_TX_buf[iot_tx] == 0x00){
			UCA0IE &= ~UCTXIE;
			iot_tx = 0;
		}
	}break;
	default: break;
	}
}//------------------------------------------------------------------------------

#pragma vector = EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){ //This interrupt is the interrupt relating to serial communication port UCA1
//------------------------------------------------------------------------------
// Interrupt name: eUSCI_A1_ISR
// Description: This interrupt transmits and receives through UCA1
//------------------------------------------------------------------------------
	char usb_value;
	switch(__even_in_range(UCA1IV,0x08)){
	case 0: break; //Vector 0 - no interrupt
	case 2:{ // Vector 2 - Rx1IFG
		usb_value = UCA1RXBUF;
		USB_Ring_Rx[usb_rx_wr++] = usb_value; // Add to Ring Buffer
		if(usb_rx_wr >= sizeof(USB_Ring_Rx)){
			usb_rx_wr = BEGINNING;
		}
		UCA0TXBUF = usb_value; 			//value of the transmit pin to the iot is set to be the same as whatever was sent via usb
		//UCA0TXBUF = USB_Ring_Rx[usb_rx_wr-1];
		// UCA0IE |= UCTXIE;
	}break;
	case 4:{ // Vector 4 - TX1IFG
		UCA1TXBUF = IOT_Ring_Rx[direct_iot++];
		IOT_Ring_Rx[direct_iot++]= 0;
		if(direct_iot >= sizeof(IOT_Ring_Rx)){
			direct_iot = BEGINNING;
		}
		if(iot_rx_wr == direct_iot){
			UCA1IE &= ~UCTXIE;
		}
	}break;
	default:
		break;
}
//------------------------------------------------------------------------------
}








