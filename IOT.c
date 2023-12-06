/*
 * IOT.c
 *
 *  Created on: Mar 24, 2023
 *      Author: joshperkins
 */

#include "functions.h"
#include "msp430.h"
#include "string.h"
#include "macros.h"


volatile unsigned char IOT_2_PC[SMALL_RING_SIZE];
volatile unsigned int iot_rx_wr;
unsigned int iot_rx_rd;
unsigned int direct_iot;
volatile unsigned char PC_2_IOT[SMALL_RING_SIZE];
unsigned int line;
char IOT_Data[BUFFER_COUNT][LONG_BUFFER];
//char IOT_Data[4][BUFF_SIZE];
volatile unsigned char IOT_Ring_Rx[SMALL_RING_SIZE];
unsigned int character;
unsigned int nextline;
unsigned int test_Value;
unsigned int IOT_parse;
char AT[LONG_BUFFER];
unsigned int boot_state;
unsigned int ip_mac[LONG_BUFFER];
unsigned int iot_tx;
unsigned int ip_address_found;
unsigned int iot_index;
extern volatile unsigned char iot_TX_buf[BUFF_SIZE];




void IOT_Process(void) { // Process IOT messages
    int i;
    unsigned int iot_rx_wr_temp;
    iot_rx_wr_temp = iot_rx_wr;         //NEED A WAY TO GET THE WR TO UPDATE SO IT CAN ACCESS NEXT CODE
    while (iot_rx_wr_temp != iot_rx_rd){ // Determine if IOT is available
        iot_TX_buf[character] = IOT_Ring_Rx[iot_rx_rd];
        iot_rx_rd++;
        character++;

        if(iot_rx_rd >= sizeof(IOT_Ring_Rx)){
            iot_rx_rd = BEGINNING;
        }
        if(iot_TX_buf[character-1] == 0x0A){
            character = 0;
        }
    }
}

