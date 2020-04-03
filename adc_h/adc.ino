#include<avr/io.h>
#include<util/delay.h>
#include"adc.h"


int main () {

  Serial.begin(9600);

  while(1) {
  
    Serial.print("value 1 : ");Serial.println(adc_read(1)); 
    Serial.print("value 2 : ");Serial.println(adc_read(2));
    
    _delay_ms(100);
    
  
  }


  return 0;
}
