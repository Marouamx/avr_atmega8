#ifndef ADC_H
#define ADC_H

unsigned int adc_reading = 0 ;


unsigned int adc_read(int channel) {
  
    ADMUX = 0x40; // v_ref : AVCC, channel : 0
 
    ADCSRA = 0x87; // bit7 : enable adc, prescaler: 128
  

    ADMUX = ADMUX|(channel & 0x0f) ; // set input channel to read 

    ADCSRA |= (1<<6) ; // start conversion set bit6
                                                     
    while ((ADCSRA & (1<<6)) != 0) {} // wait till bit6 is cleared 

    adc_reading =  ADCL | (ADCH<<8) ; // must start by ADCL n ADCH shifted by byte 
   

    return adc_reading;
} 
#endif

