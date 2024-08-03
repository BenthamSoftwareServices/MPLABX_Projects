
#include "mcc_generated_files/system/system.h"
#include <util/delay.h>

#define LED_PIN 3  //PA3 is the third pin (0-indexed)
#define Red_LED PIN0_bm //PIN0_bm, or PIN0 bit mask, translates to 0x01 - the first bit of a(ny) port, so Red_LED also = 0x01

int count = 0;

int main(void) {
    SYSTEM_Initialize();

    // Set PA3 as an output for an external LED
    PORTA.DIRSET = (1 << LED_PIN);
    // Set PC0 as an output for the onboard red lED
    PORTC.DIRSET = (Red_LED); //sets the direction of PC0 to output by writing 0x01 to the DIRSET register of port C

    while (1) {
        // Toggle the LEDs
        NOP();
        PORTA.OUTTGL = (1 << LED_PIN); //the external LED if used
        _delay_ms(1000); // 1000 milliseconds delay
        NOP();
        PORTC.OUTTGL = (Red_LED); //toggles the bit of PORTC defined by Red_LED i.e. 0x01 which equals PC0, the onboard LED
        _delay_ms(100); // 1000 milliseconds delay

        __asm("NOP"); //assembly type NOP
        NOP(); //function type NOP

        count++; //increment variable
    }
    return 0; //this is never reached unless the while() loop exits for some reason
}