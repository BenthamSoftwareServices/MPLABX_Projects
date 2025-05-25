/*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
 */
/* This code flashes the onboard Red LED on PC0 of an Adafruit ATtiny1616
 * breakout board and also an external Blue LED on PA3, if fitted. The MPLAB
 * Code Configurator (MCC) sets the state of the two pins as can be viewed in
 * pins.c located at: Source Files > MCC Generated Files > System > src > pins.c
 * and also generates a set of aliases to easily manipulate the pins as listed
 * in pins.h located at: Header Files > MCC Generated Files > System > pins.h
 *
 * Two methods to toggle an LED are shown here. #define Red_LED 0x01 tells the
 * compiler to replace any occurrence of the word Red_LED with the value 0x01,
 * this is not the same as declaring a variable e.g. int Red_LED = 0x01;
 * although this would also work and then toggles the pin PC0 using explicit
 * code PORTC.OUTTGL = (Red_LED); A second easier method is the use the alias
 * from pins.h i.e. Blu_LED_Toggle(); which is equivalent to PORTA_OUTTGL = 0x8;
 * so it is also unnecessary to define Blu_LED 0x08 as the alias knows it is on
 * PA3.
 *
 * Note: when defining names and values it is not necessary to work out the hex
 * value of the pin position in the port, instead there is another type of alias
 * called pin bit mask, so e.g. PIN0_bm translates to simply 0x01 and is
 * applicable to any port.  somewhere in the MCC Generated Files will be a
 * define like this: #define PIN0_bm (1 << 0), meaning bit 0 becomes a logic 1
 * making the bit mask 0b00000001 or 0x01 in hexadecimal.
 *
 * This example also uses UART0 to send Hello World and the value of a variable
 * called counter from the UART Tx pin PB2 or the pin marked 7 on the board.
 * UART reference =
 * https://onlinedocs.microchip.com/oxy/GUID-41EA2496-1EE8-4319-A387-9EC9318EF178-en-US-23/GUID-F7F7BDF5-134D-4F8A-B6A7-D368C8DDA312.html#GUID-717D892E-D29B-4934-8098-DCA579FEB908
 *
 */

#define F_CPU 20000000UL  // 20 MHz clock speed
// Note: Actual system clock is F_CPU/6 = 3.33MHz due to prescaler

#include "mcc_generated_files/system/system.h"
//#include <util/delay.h>
#include <avr/io.h>

/**
 * @brief Simple delay function using a decrementing counter
 * 
 * Creates an approximate 1-second delay by decrementing a counter.
 * Calibrated for 20MHz clock with x6 prescaler (3.33MHz system clock).
 * Protected against compiler optimizations.
 */
void __attribute__((noinline, optimize("O0"))) my_delay_1s(void) {
    // Counter variable for 1 second delay
    volatile uint32_t S1_delay;

    // Value calibrated for approximately 1 second at 3.33MHz (20MHz/6)
    //S1_delay = 111000; // 1 Second
    S1_delay = 7000;

    // Decrement counter until zero
    while (S1_delay > 0) {
        S1_delay--;
        // Add a compiler barrier to prevent optimization
        __asm__ volatile("" :: : "memory");
    }
}

#define Red_LED 0x01 // Onboard Red LED on PC0 i.e. Port C Bit 0 (starting at 0) which is the
// first bit and in binary 0b00000001
#define Blue_LED 0x08 //External Blue LED on PA3 i.e. Port A Bit 3 (starting
// at 0) which is the fourth bit and in binary 0b00001000

int counter = 0;

int main(void) {
    SYSTEM_Initialize();
    while (1) {
        // Toggle the LEDs
        PORTC.OUTTGL = (Red_LED); // Toggles the bit of Port C defined by the value of Red_LED i.e. 0x01 or PC0
        //_delay_ms(500); // milliseconds delay
        my_delay_1s();

        PORTA.OUTTGL = (Blue_LED);
        //_delay_ms(500); // milliseconds delay
        my_delay_1s();

        counter++;
    }
    return 0; // this is never reached unless the while() loop exits for some
    // reason
}