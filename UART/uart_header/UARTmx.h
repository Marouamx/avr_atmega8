/*******

   Marouamx

   sat 01:11 11/04/2020

*******/

#ifndef USARTmx_H
#define USARTmx_H

#include<avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif


typedef struct {

    unsigned _9th_Tdata  : 1 ; // used for diffrentiating adresses from data  multi processor mode
    unsigned _9th_Rdata  : 1 ;
    unsigned _charSize   : 1 ;
    unsigned _tx  : 1 ;
    unsigned _rx  : 1 ;
    unsigned _Globl_intp : 1 ;
    unsigned _tx_intp    : 1 ;
    unsigned _rx_intp    : 1 ;
} UCSR0Bbits_t ;

extern volatile UCSR0Bbits_t enable __asm__ ("0xC1");

typedef struct {

    unsigned          : 1 ;
    unsigned _charSize: 2 ;
    unsigned _stopBit : 1 ;
    unsigned _Parity  : 2 ;
    unsigned _mode    : 2 ;

} UCSR0Cbits_t ;

extern volatile UCSR0Cbits_t config __asm__ ("0xC2");

typedef struct {

    unsigned               : 2 ; // multiSlave option
    unsigned _Parity_error : 1 ; // R n T parity dont match
    unsigned _OverRun      : 1 ; //R buffer full (2chars) but new start bit is detected
    unsigned _Frame_error  : 1 ; // stop bit not received
    unsigned _UDRE0 : 1 ; // UDRE0 data register empty interrupt
    unsigned _T_complete   : 1 ; // set when T buffer cleared- automatically cleared when transmit interrupt is excuted
    unsigned _R_complete   : 1 ; // set for unread data in buffer


} UCSR0Abits_t ;

extern volatile UCSR0Abits_t debug __asm__ ("0xC0");

extern volatile char BD_low_bits __asm__ ("0xC4");
extern volatile char BD_high_bits __asm__ ("0xC5");

void usart_init(unsigned long Baud_rate) {

    unsigned int ubrr = F_CPU/16/Baud_rate - 1 ;
    BD_high_bits = (unsigned char) (ubrr>>8) ;
    BD_low_bits = (unsigned char) ubrr;
    enable._tx = 1 ;
    enable._rx = 1 ;
    config._charSize =  3 ; // 8 bits data

}

void usart_advanced_init (unsigned long Baud_rate, char _Parity , char _stopBit , char _mode , char _charSize ) {

    unsigned int ubrr = F_CPU/16/Baud_rate - 1 ;

    config._charSize = _charSize;
    config._mode = _mode;
    config._stopBit = _stopBit ;
    config._Parity = _Parity ;

    BD_high_bits = (unsigned char) (ubrr>>8) ;
    BD_low_bits = (unsigned char) ubrr;

    enable._tx = 1 ;
    enable._rx = 1 ;


}

void usart_transmit_int(unsigned int data) {


    while (debug._UDRE0 == 0) ; // wait for empty T buffer

    if (config._charSize > 3) { // bigger than 8 bits
        enable._9th_Tdata = 0 ;
        if ( data & 0x100) {
            enable._9th_Tdata = 1 ;
            UDR0 = data ;
        }
    }
    else  UDR0 = data ;

}

void usart_transmit(unsigned char data) {

    while (debug._UDRE0 == 0) ; // wait for empty T buffer
    UDR0 = data ;

}

void usart_transmit_string (char* data) {

    for (int i =0 ; data[i] != 0 ; i++) {

        usart_transmit(data[i]);

    }
}

unsigned char usart_receive () {

    while (debug._R_complete == 0) ; // wait for empty R buffer

    if (debug._Parity_error == 1 || debug._Frame_error == 1 ) return 0;
    if (debug._OverRun == 1 ) return -1;


    return UDR0 ;
}

void usart_receive_string(unsigned char *string)  {
    //Receive a character until carriage return or newline

    unsigned char i=0,J=0;

    do {
        *(string+i)= usart_receive();
        J = *(string+i);
        i++;
    } while((J!='\n') && (J!='\r'));

    i++;
    *(string+i) = '\0';

}

#endif
