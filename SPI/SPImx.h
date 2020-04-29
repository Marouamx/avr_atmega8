#ifndefine SPImx_H
#define SPImx_H

#include<avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif


void init_SPI_master() {

    DDRB = (1<<5)|(1<<3); // MOSI and clk pins as output
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); // enable SPI,master mode,prescaler 16
};

void init_SPI_slave(){

    DDRB |= (1<<4); // MISO output
    SPCR = (1<<SPE);
};

/* enable SPI interrupt */
void enable_SPI_intp() {

    SPCR = (1<<SPIE);
};


void SPI_transmit(char data){

    SPDR = data  ;
    while (!(SPSR & (1<<SPIF))); // wait for transmition complete
};
unsigned char SPI_receive() {

    while (!(SPSR & (1<<SPIF)));  // wait for reception complete
    return SPDR ;
};





#endif
