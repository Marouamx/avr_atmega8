
/****

Marouamx

15/04/2020 00:23

****/


//reg TCNT0 stores count value

//value given to OC0A F_clk/2/prescaler/F(OC0x)-1
//F(OC0x)pwm = F_clk/prescaler/256

#include<avr/io.h>
#define F_CPU 16000000

typedef struct {

    uint8_t _WGM0  : 2;
    uint8_t        : 2;
    uint8_t _COM0B : 2;
    uint8_t _COM0A : 2;

}TCCR0Abits_t ;

extern volatile TCCR0Abits_t config __asm__ ("0x44") ;

typedef struct {

    uint8_t _CS0   : 3;
    uint8_t _WGM02 : 1;
    uint8_t        : 4;

}TCCR0Bbits_t ;

extern volatile TCCR0Bbits_t clk_select __asm__ ("0x45") ;

typedef struct {

    uint8_t _Overflow_interrupt: 1;
    uint8_t _A_match_interrupt : 1;
    uint8_t _B_match_interrupt : 1;
    uint8_t                    : 5;

}TIMSK0bits_t ;

extern volatile TIMSK0bits_t enable __asm__ ("0x6E") ;

typedef struct {

    uint8_t _Overflow : 1;
    uint8_t _A_match : 1;
    uint8_t _B_match : 1;
    uint8_t          : 5;

}TIFR0bits_t ;

extern volatile TIFR0bits_t flag __asm__ ("0x35") ;

void Setup_CTC0(uint8_t clk,uint16_t prescaler,int F_OCROx, uint8_t _OC0A_mode) {

config._WGM0 = 2;

OCR0A= (uint8_t) F_CPU/2/prescaler/F_OCROx -1;

config._COM0A = _OC0A_mode;

clk_select._CS0 = clk; // start counting

}

void Setup_FastPWM0(uint8_t _OC0A_mode,uint8_t duty_cycleA,uint8_t _OC0B_mode,uint8_t duty_cycleB){

config._WGM0 = 3; // fast mode enabled

config._COM0A = _OC0A_mode;

config._COM0B = _OC0B_mode;

<<<<<<< HEAD
clk_select._CS0 = 5 ; //-- start counting
=======
clk_select._CS0 = 5 ; // no prescaling -- start counting
>>>>>>> 148d070277910071a8481399e348d7b1293fef62

OCR0A = (uint8_t) duty_cycleA/100 * 255 ;
OCR0B = (uint8_t) duty_cycleB/100 * 255 ;

}
