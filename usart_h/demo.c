



#include<avr</io.h>
#include "UARTmx.h"


int int main() {

    char k ;

    unsigned char buffer[100] ;

    usart_advanced_init(9600,0,1,0,3);

    // or

    usart_init(9600);

    while(1) {

        usart_transmit('c');

        usart_transmit_string("Big C now");

        k = usart_receive() ;

        usart_receive_string(buffer);

        // To print the buffer in serial moniter
        int j = 0;

        do {
          usart_transmit((char) buffer[j]);
          j++;
        }while (buffer[j] != '\0' );




    }



    return 0;
}
