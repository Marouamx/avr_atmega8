
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#define USART_BAUDRATE 9600
#define BUF_SIZE 20

int main (void)
{
   UCSRB = (1 << RXEN) | (1 << TXEN);   // Turn on the transmission and reception circuitry
   UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); // Use 8-bit character sizes

   UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
   UBRRL = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register

   UCSRB |= (1 << RCXIE); // Enable the USART Recieve Complete interrupt (USART_RXC)
   sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed

   for (;;) // Loop forever
   {
         // Do nothing - echoing is handled by the ISR instead of in the main loop
   }
}

ISR(USART_RXC_vect)
{
   char ReceivedByte;
   ReceivedByte = UDR; // Fetch the received byte value into the variable "ByteReceived"
   UDR = ReceivedByte; // Echo back the received byte back to the computer
}
