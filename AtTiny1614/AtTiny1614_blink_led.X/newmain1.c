/* 
 * File:   newmain1.c
 * Author: Steven
 *
 * Created on July 27, 2024, 2:17 PM
 */
//#define F_CPU 3333333UL // must be defined before including util/delay.h or the value will not be used and a default value of 1MHz will be used
#define F_CPU 2666666UL

#include <xc.h> // includes avr/io.h
#include <util/delay.h>

#define LED_PIN 3  // PA3 is the third pin (0-indexed)

//#define F_CPU 1000000UL
//#define _XTAL_FREQ 1000000UL

int count = 0;

int main(void) {
    
    // Set PA2 as an output
    PORTA.DIRSET = (1 << LED_PIN);

    while (1) {

        // Toggle the LED
        PORTA.OUTTGL = (1 << LED_PIN);
        _delay_ms(1000); // 1000 milliseconds delay i.e. flash cycle = 2 seconds

        __asm("NOP");    
        NOP();

        count++;
    }
    return 0;
}