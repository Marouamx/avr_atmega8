#include<avr/io.h> 
#include<util/delay.h>


int main () {

  DDRC |= 0x07 ; // bit0,1,2 as outputs 
  PORTC = 0x00 ; // all bits low

  while(1) {
    
    for (int i =0; i<3 ; i++) {
      
      PORTC |= (1<<i) ; // set bit i  
    
      _delay_ms(200);
    }  

    
    for (int i =0; i<3 ; i++) {
      
      PORTC &= ~(1<<i) ; //clear bit i 
    
      _delay_ms(200);
    }  
 
  }
  
 
  return 0 ; 

}
