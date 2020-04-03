#include<avr/io.h>


int main () {

 
  DDRC = 0x01; // bit0 output 

  PORTC = 0x02; // enable pullups
   
   while (1) {

    // (PINC & 0x02) returns 0 when  bit 1 is 0

    if (PINC & 0x02) { 
      
    PORTC |= 0x01 ; // led on
      
     }
    else PORTC &= ~0x01 ; // led off
    
  }



  return 0 ; 
}
