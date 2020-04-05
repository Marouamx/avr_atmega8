/*
*** compiler : avr-gcc  
*** Last update : 5/4/2020 
*/  



#ifndef ADCmx_H
#define ADCmx_H


#include<avr/io.h>


typedef union {

    struct {

        unsigned  _ADPS0 : 1 ;
        unsigned  _ADPS1 : 1 ;
        unsigned  _ADPS2 : 1 ;
        unsigned  _ADIE  : 1 ;
        unsigned  _ADIF  : 1 ;
        unsigned  _ADATE : 1 ;
        unsigned  _ADCS  : 1 ;
        unsigned  _ADEN  : 1 ;

    };

    struct {

        unsigned _ADPS : 3 ;
        unsigned       : 5 ;
    };

    struct {
      unsigned  _all : 8 ;
    };

} ADCSRAbits_t;

extern volatile ADCSRAbits_t ADCSRAbits __asm__ ("0x7A") ;

typedef union {

    struct {

        unsigned  _MUX0  : 1;
        unsigned  _MUX1  : 1;
        unsigned  _MUX2  : 1;
        unsigned  _MUX3  : 1;
        unsigned  _MUX4  : 1;
        unsigned  _ADLAR : 1;
        unsigned  _REFS0 : 1;
        unsigned  _REFS1 : 1;

    };
    struct {

        unsigned  _MUX  : 5;
        unsigned        : 1;
        unsigned  _REFS : 2;
    };

    struct {
      unsigned  _all : 8;
    };

} ADMUXbits_t;

extern volatile ADMUXbits_t ADMUXbits __asm__ ("0x7C") ;



/*following struction about config options for ADC */

typedef struct {

    char channel; // 0b00110
    char right_adjust; // 0 ie left adjust
    char v_ref; // 0b01 for AVCC
    char enable_interrupt;
    char auto_trigger;
    char prescaler; // ex : 0b101

} ADC_t;

ADC_t config;


unsigned int adc_read(unsigned int channel) {

    ADMUXbits._MUX = config.channel = channel ;
    ADMUXbits._ADLAR = config.right_adjust = 0;
    ADMUXbits._REFS = config.v_ref = 0b01;
    ADCSRAbits._ADATE = config.auto_trigger = 0;
    ADCSRAbits._ADIE = config.enable_interrupt = 0;
    ADCSRAbits._ADPS = config.prescaler = 0b111;
    ADCSRAbits._ADEN = 1;
    ADCSRAbits._ADCS = 1 ; //begin conversion
    while (ADCSRAbits._ADCS != 0) {}

return ADCL | (ADCH<<8) ;

}


unsigned int adc_advanced_read(unsigned int channel, uint8_t v_ref, uint8_t prescaler ) {

    ADMUXbits._MUX = config.channel = channel ;
    ADMUXbits._ADLAR = config.right_adjust = 0;
    ADMUXbits._REFS = config.v_ref = v_ref;
    ADCSRAbits._ADATE = config.auto_trigger = 0;
    ADCSRAbits._ADIE = config.enable_interrupt = 0;
    ADCSRAbits._ADPS = config.prescaler = prescaler;
    ADCSRAbits._ADEN = 1;
    ADCSRAbits._ADCS = 1 ; //begin conversion
    while (ADCSRAbits._ADCS != 0) {}

return ADCL | (ADCH<<8) ;

}

#endif
