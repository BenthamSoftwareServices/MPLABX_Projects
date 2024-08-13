/* This code flashes the onboard Red LED on PC0 of an Adafruit ATtiny1616 breakout board and also an external Blue LED
 * on PA3, if fitted. The MPLAB Code Configurator (MCC) sets the state of the two pins as can be viewed in pins.c located at:
 *      Source Files > MCC Generated Files > System > src > pins.c
 * and also generates a set of aliases to easily manipulate the pins as listed in pins.h located at:
 *      Header Files > MCC Generated Files > System > pins.h
 * 
 * Two methods to toggle an LED are shown here. #define Red_LED 0x01 tells the compiler to replace any occurence of the word
 * Red_LED with the value 0x01, this is not the same as declaring a variable e.g. int Red_LED = 0x01; although this would also work
 * and then toggles the pin PC0 using explicit code PORTC.OUTTGL = (Red_LED); A second easier method is the use the alias from pins.h
 * i.e. Blu_LED_Toggle(); which is equivalent to PORTA_OUTTGL = 0x8; so it is also unnecessary to define Blu_LED 0x08 as the alias
 * knows it is on PA3.
 * 
 * Note: when defining names and values it is not necessary to work out the hex value of the pin position in the port, instead there is
 * another type of alias called pin bit mask, so e.g. PIN0_bm translates to simply 0x01 and is applicable to any port.  somewhere in the
 * MCC Generated Files will be a define like this: #define PIN0_bm (1 << 0), meaning bit 0 becomes a logic 1 making the bit mask 0b00000001
 * or 0x01 in hexadecimal.
 */

#include "mcc_generated_files/system/system.h"
#include <util/delay.h>

#define Red_LED 0x01 //Onboard Red LED on PC0 i.e. Port C Bit 0 (starting at 0) which is the first bit and in binary 0b00000001
//#define Blu_LED 0x08 //External Blue LED on PA3 i.e. Port A Bit 3 (starting at 0) which is the fourth bit and in binary 0b00001000

int count = 0;

int main(void) {
    SYSTEM_Initialize();
    while (1) {
        // Toggle the LEDs
        NOP();
        PORTC.OUTTGL = (Red_LED); //Toggles the bit of Port C defined by the value of Red_LED i.e. 0x01 or PC0
        _delay_ms(1000); // 1000 milliseconds delay
        NOP();
        //PORTA.OUTTGL = (Blu_LED);
        Blu_LED_Toggle();
        _delay_ms(1000); // 1000 milliseconds delay 
        count++;
    }
    return 0; //this is never reached unless the while() loop exits for some reason 
}
