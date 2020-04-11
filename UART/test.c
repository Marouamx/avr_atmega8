#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "UARTmx.h"

#define USART_BAUDRATE 9600
#define BUF_SIZE 20

typedef struct{

    uint8_t buffer[BUF_SIZE];
    uint8_t index;

}buf_t;

buf_t buf;

void BufferInit(buf_t *buf)
{
    buf->index=0;
}
// write to  buffer
uint8_t BufferWrite(buf_t *buf, uint8_t u8data)
{
    if (buf->index<BUF_SIZE)
    {
        buf->buffer[buf->index] = u8data;
        buf->index++;
        return 0;
    }
        else return 1;
}
//read from buffer
uint8_t BufferRead(buf_t *buf, volatile uint8_t *u8data)
{
    if(buf->index>0)
    {
        buf->index--;
        *u8data=buf->buffer[buf->index];
        return 0;
    }
    else return 1;
}


//RX Complete interrupt service routine
ISR(USART_RX_vect) {
    uint8_t temp;

    temp=usart_receive();


    if ((BufferWrite(&buf,temp)==1)||(temp=='.')) {
        //disable reception and RX Complete interrupt
        enable._rx = 0;
        enable._rx_intp = 0;
        //enable transmission and UDR0 empty interrupt
        enable._tx = 1;
        UDRIE0 = 1;

    }
}
//UDR0 Empty interrupt service routine
ISR(USART_UDRE_vect)
{
    //if index is not at start of buffer
    if (BufferRead(&buf, &UDR0)==1)
    {
        //start over
        //reset buffer
        BufferInit(&buf);
        //disable transmission and UDR0 empty interrupt
        enable._tx = 0 ;
        UDRIE0 = 0;
        //enable reception and RC complete interrupt
        enable._rx = 1;
        enable._rx_intp = 1;
    }
}
int main (void)
{
    BufferInit(&buf);

    set_sleep_mode(SLEEP_MODE_IDLE);

    usart_init(USART_BAUDRATE);

    enable._rx_intp = 1;

    //enable global interrupts
    sei();

    while(1)
        {
            sleep_mode();
        }
}
