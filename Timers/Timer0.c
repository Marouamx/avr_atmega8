/***************
    Marouamx

Timer registers in the ATmega8

bits WGM00 WGM01 WGM02 for changing modes

0CR0A -- 8bit register -- use this formula  F_CPU/2/prescaler/output_freq-1


*************/


#include<avr/io.h>
#include<avr/interrupt.h>

#define F_CPU 16000000UL

int times = 1;

void Setup_timer0 () {

    TCCR0A = (1<<WGM01) ; //CTC mode

    OCR0A = 194; // generate 40 Hz interruption -- 16000000/2/1024/40-1

    TIMSK0 = (1<< OCIE0A); // enabling interruptin of OCE0A

    TCCR0B = (5<<CS00); // start counting every 1024 MCs

}

ISR(TIMER0_COMP1_vect) {
    switch (times) {
        case 1 :
            times++;
        break;
        case 2 :
            PORTC ^= (1<<5); // change state of bit5
            times = 1;
        break;
    }
}

int int main() {

    DDRC |= (1<<5) ; // bit5 as outputs
    Setup_timer0() ;
    sei () ;
    while(1) {} ;
    return 0;
}
