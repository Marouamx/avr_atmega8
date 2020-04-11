/*****

    Maroumx

compiler : avr-gcc

******/


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "UARTmx.h"

#define USART_BAUDRATE 9600
#define BUF_SIZE 50



unsigned char buff[BUF_SIZE];


//RX Complete interrupt service routine
ISR(USART_RXC_vect) {

    usart_receive_string(buff);
    //disable rx transmittion and interrupt
    enable._rx = 0;
    enable._rx_intp = 0;
    //enable empty Buffer interrupt and tx Receive
    enable._tx = 1;
    enable._Globl_intp =1;
}

//UDR0 Empty interrupt service routine
ISR(USART_UDRE_vect) {

    usart_transmit_string("well received");
    // disable empty Buffer interrupt and tx Receive
    enable._tx = 0;
    enable._Globl_intp =0;
    //enable rx and rx interrupt
    enable._rx =1;
    enable._rx_intp =1;

}

int main (void) {

   usart_init(USART_BAUDRATE);
   set_sleep_mode(SLEEP_MODE_IDLE);

   sei(); // Enable the Global Interrupt

   enable._rx_intp = 1 ;

    while (1) {

        sleep_mode();

    }
}

