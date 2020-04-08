#ifndef USARTmx_H
#define USARTmx_H

#include<avr/io.h>

#define F_CPU 16000000UL


typedef struct {

    unsigned _9th_Tdata  : 1 ;
    unsigned _9th_Rdata  : 1 ;
    unsigned _charSize   : 1 ;
    unsigned _enable_tx  : 1 ;
    unsigned _enable_rx  : 1 ;
    unsigned             : 3 ;

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

    unsigned               : 2 ;
    unsigned _Parity_error : 1 ; // R n T parity dont match
    unsigned _OverRun      : 1 ; //R buffer full (2chars) but new start bit is detected
    unsigned _Frame_error  : 1 ; // stop bit not received
    unsigned _Buffer_empty : 1 ; // ie ready to receive new data
    unsigned _T_complete   : 1 ; // set when T buffer cleared
    unsigned _R_complete   : 1 ; // set for unread data in buffer


} UCSR0Abits_t ;

extern volatile UCSR0Abits_t debug __asm__ ("0xC0");

extern volatile char BD_low_bits __asm__ ("0xC4");
extern volatile char BD_high_bits __asm__ ("0xC5");


void usart_init(long  Baud_rate) {

  unsigned int ubrr = F_CPU/16/Baud_rate - 1 ;
  BD_high_bits = (unsigned char) (ubrr>>8) ;
  BD_low_bits = (unsigned char) ubrr;
  enable._enable_tx = 1 ;
  enable._enable_rx = 1 ;
  config._charSize =  3 ; // 8 bits data

}


void usart_advanced_init (long  Baud_rate, char _Parity , char _stopBit , char _mode , char _charSize ) {

  unsigned int ubrr = F_CPU/16/Baud_rate - 1 ;

  config._charSize = _charSize;
  config._mode = _mode;
  config._stopBit = _stopBit ;
  config._Parity = _Parity ;

  BD_high_bits = (unsigned char) (ubrr>>8) ;
  BD_low_bits = (unsigned char) ubrr;

  enable._enable_tx = 1 ;
  enable._enable_rx = 1 ;


}

void usart_transmit_int(unsigned int data) {


  while (!(debug._T_complete == 0)) ; // wait for empty T buffer

  if (config._charSize > 3) { // bigger than 8 bits
      enable._9th_Tdata = 0 ;
      if ( data & 0x100) {
          enable._9th_Tdata = 1 ;
          UDR = data ;
      }
  }
  else  UDR = data ;

}


void usart_transmit(unsigned char data) {

  while (!(debug._T_complete == 0)) ; // wait for empty T buffer
  UDR = data ;

}


unsigned char usart_receive () {

  while (!(debug._R_complete == 0)) ; // wait for empty R buffer

  if (debug._Parity_error = 1 ) return 0;
  if (debug._Frame_error =  1 ) return-1;
  if (debug._OverRun =      1 ) return 1;


  return UDR ;
}

void usart_transmit_string (unsigned char* data) {

    for (int i =0 ; data[i] != '/n' ; i++) {

        while (!(debug._T_complete == 0)) ; // wait for empty T buffer
        UDR = data[i];
    }
}


char* usart_receive_string () {

    char buffer[10000] ;
    int i = 0;
    do {
        while (!(debug._R_complete == 0)) ; // wait for empty R buffer
        buffer[i]= (char) UDR;
        i++;
    } while (UDR != '\n');


    return buffer;
}



#endif
