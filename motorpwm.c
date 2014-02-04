// goal is to make a dc motor go faster & slower
// using pwm; play with an led first

//
//     Atmel ATtiny13 manual 
//     http://www.atmel.com/Images/doc8126.pdf 

#define F_CPU 9.6E6L / 8 // CPU Freq. Must come before delay.h include. 9.6MHz / 8
#include <util/delay.h>
#include <util/delay_basic.h>

#include <avr/io.h>


uint8_t lfsr_next() {
    static uint8_t lfsr = (uint8_t)0xcb;
    lfsr = (lfsr >> 1) ^ (-(uint8_t)(lfsr & 1) & 0b10111000);
    return lfsr;
}

void delay_some_ms(uint8_t loops) { 
   while (loops--) 
     _delay_ms(3); 
}

int main(void) {
    //====================================================
    // chip setup


    // PORTB output for pin 5, OC0A PWM
    DDRB = (1<<DDB0);

    // Set Fast PWM mode
    // 11.7.3 p.65 Fast PWM Mode
    // 11.9.1 registers 

    TCCR0A =
        (1<<WGM00)|(1<<WGM01) // fast PWM 
        | (1<<COM0A1)         // on until counter matches OCR0A
    ;

    TCCR0B = (1<<CS00);

    OCR0A = 0;

    // 
    //====================================================
    


    while(1) {
        uint8_t rand = lfsr_next();
        OCR0A = rand & 0x7f; // just the lower 7 bits - up to 50% 

        delay_some_ms(rand);
    }

    return 0;
}
