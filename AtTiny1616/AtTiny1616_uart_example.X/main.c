/*
 * MAIN Generated Driver File
 * @file main.c
 * @defgroup main MAIN
 * @brief This is the generated driver implementation file for the MAIN driver.
 * @version MAIN Driver Version 1.0.2
 * @version Package Version: 3.1.2
 */

// Format code = Alt Shift F or Menu > Source > Format

#include "mcc_generated_files/system/system.h"
#include <stdint.h> // stdint.h is a header file in the C standard library to enable more portable code by providing a set of typedefs that specify exact-width integer types

#define Blue_LED 0x08 //External Blue LED on PA3 i.e. Port A Bit 3 (starting at 0) which is the fourth bit and in binary 0b00001000
#define DELAY_CALC(seconds) ((uint32_t)((seconds) * 111000))
//Usage examples:
//custom_delay(DELAY_CALC(0.5));    // 0.5 seconds ? 55,500
//custom_delay(DELAY_CALC(1.0));    // 1.0 seconds ? 111,000
//custom_delay(DELAY_CALC(2.5));    // 2.5 seconds ? 277,500
//custom_delay(DELAY_CALC(0.1));    // 0.1 seconds ? 11,100

int counter = 0; // A variable that can be printed

// A delay function that can be used instead of _delay_ms which does not work when compiler optimisation is set to 0 to enable correct debugging operations.
void __attribute__((noinline, optimize("O0"))) custom_delay(uint32_t S1_delay) {
    // Counter variable for delay
    volatile uint32_t delay_counter = S1_delay;
    
    // Decrement counter until zero
    while (delay_counter > 0) {
        delay_counter--;
        // Add a compiler barrier to prevent optimization
        __asm__ volatile("" ::: "memory");
    }
}

void UART_print_loop(
        uint8_t count) // the passed parameter 7 is allocated to the variable count
{
    // print Hello World count(7) times)
    int i;
    for (i = 0; i < count; i++) {
        printf("%d. Hello World!\n\r", i);
    }
    printf("\n\r"); // print new line and carriage return
    printf("Counter value = %d \n\r", counter); // print text and value of counter
    printf("\n\r"); // print new line and carriage return
}

/*
    Main application
 */

int main(void) {
    SYSTEM_Initialize();

    while (1) {
        counter++; // Increment the variable counter
        UART_print_loop(7); // run and pass the parameter value 7
        PORTA.OUTTGL = (Blue_LED); // PORTA.OUTTGL is a register that controls pin toggling on PORT A
        custom_delay(DELAY_CALC(0.5));    // 0.5 seconds ? 55,500 // see line 16
    }
    return 0; // this is never reached unless the while() loop exits for some reason
}