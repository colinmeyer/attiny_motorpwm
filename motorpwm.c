// goal is to make a dc motor go faster & slower
// using pwm; play with an led first

//
//     Atmel ATtiny13 manual 
//     http://www.atmel.com/Images/doc8126.pdf 

#define F_CPU 9.6E6L / 8 // CPU Freq. Must come before delay.h include. 9.6MHz / 8
#include <util/delay.h>

#include <avr/io.h>





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
    

    static uint8_t pwm;

    while(1) {
        _delay_ms(450);

        pwm += 0x40;
        OCR0A = pwm;
    }

    return 0;
}
