#include <avr/io.h>
#include "TCmx.h"
#inlcude<util/delay.h>


int duty = 0;
int main () {

    DDRD = 0b01100000;

    Setup_FastPWM0(2,0,3,0); //1st non-inverted 2nd inverted

    enable._Overflow_interrupt= 1;

    sei();

        while(1) {

            duty +=10;
            _delay_ms(100);
            if(duty>100) duty = 0;


        }

    return 0 ;

}

ISR(TIMER0_OVF_vect) {

    OCR0A = (uint8_t) duty/100 * 255;
    OCR0B = (uint8_t) duty/100 * 255;

}
