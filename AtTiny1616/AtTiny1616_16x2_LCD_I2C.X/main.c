/* This example also uses UART0 to send Hello World and the value of a variable called counter from the UART Tx pin PB2 or the pin marked 7 on the board.
 * UART reference = https://onlinedocs.microchip.com/oxy/GUID-41EA2496-1EE8-4319-A387-9EC9318EF178-en-US-23/GUID-F7F7BDF5-134D-4F8A-B6A7-D368C8DDA312.html#GUID-717D892E-D29B-4934-8098-DCA579FEB908
 */

#include "mcc_generated_files/system/system.h"
#include <avr/io.h>
#include <util/delay.h>

// Define I2C LCD Address
#define I2C_LCD_ADDRESS 0x27  // Default I2C address of PCF8574 backpack

// Define LCD commands
#define LCD_CMD_CLEAR 0x01
#define LCD_CMD_HOME  0x02
#define LCD_CMD_ENTRY_MODE 0x06
#define LCD_CMD_DISPLAY_CONTROL 0x0C
#define LCD_CMD_FUNCTION_SET 0x28
#define LCD_CMD_SET_DDRAM_ADDR 0x80

// Function prototypes
void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(uint8_t data);
void LCD_Init(void);
void LCD_Command(uint8_t cmd);
void LCD_Char(char data);
void LCD_String(char *str);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_WriteNibble(uint8_t nibble, uint8_t mode);
void LCD_WriteByte(uint8_t byte, uint8_t mode);
void LCD_Send(uint8_t data);

int main(void) {
    // Initialize I2C and LCD
    I2C_Init();
    LCD_Init();

    // Display messages on LCD
    LCD_SetCursor(0, 0);  // Set cursor to first row, first column
    LCD_String("Hello, World!");

    _delay_ms(2000);

    LCD_SetCursor(1, 0);  // Set cursor to second row, first column
    LCD_String("ATtiny1616 I2C");

    while (1);
    return 0;
}

// initialise I2C
void I2C_Init(void) {
    // Set up I2C clock (100kHz)
    //TWI0.MBAUD = (uint8_t) TWI0_BAUD(100000, 0);  // Set baud rate for 100 kHz I2C
    TWI0.MBAUD = (uint8_t) (100000);  // Set baud rate for 100 kHz I2C
    TWI0.MCTRLA = TWI_ENABLE_bm;                  // Enable I2C master mode
}

// Start I2C communication
void I2C_Start(void) {
    TWI0.MADDR = I2C_LCD_ADDRESS << 1;  // Send start condition and slave address
    while (!(TWI0.MSTATUS & TWI_WIF_bm));  // Wait for transmission to complete
}

// Stop I2C communication
void I2C_Stop(void) {
    TWI0.MCTRLB |= TWI_MCMD_STOP_gc;  // Send stop condition
}

// Write data via I2C
void I2C_Write(uint8_t data) {
    TWI0.MDATA = data;  // Write data to data register
    while (!(TWI0.MSTATUS & TWI_WIF_bm));  // Wait for transmission to complete
}

// initialise LCD
void LCD_Init(void) {
    _delay_ms(50);  // Wait for LCD power up
    LCD_WriteNibble(0x03, 0);  // Initialize in 4-bit mode
    _delay_ms(5);
    LCD_WriteNibble(0x03, 0);
    _delay_ms(1);
    LCD_WriteNibble(0x03, 0);
    LCD_WriteNibble(0x02, 0);  // Set to 4-bit mode

    LCD_Command(LCD_CMD_FUNCTION_SET);     // 2-line display, 5x7 dots
    LCD_Command(LCD_CMD_DISPLAY_CONTROL);  // Display ON, cursor OFF
    LCD_Command(LCD_CMD_CLEAR);            // Clear display
    LCD_Command(LCD_CMD_ENTRY_MODE);       // Auto-increment cursor
}

// Send command to LCD
void LCD_Command(uint8_t cmd) {
    LCD_WriteByte(cmd, 0);
}

// Write character to LCD
void LCD_Char(char data) {
    LCD_WriteByte(data, 1);
}

// Send string to LCD
void LCD_String(char *str) {
    while (*str) {
        LCD_Char(*str++);
    }
}

// Set cursor position on LCD
void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? col : (col + 0x40);  // Set row and column
    LCD_Command(LCD_CMD_SET_DDRAM_ADDR | address);
}

// Send data nibble (4-bits) to LCD
void LCD_WriteNibble(uint8_t nibble, uint8_t mode) {
    uint8_t data = (nibble << 4) | (mode ? 0x01 : 0x00);
    I2C_Start();
    I2C_Write(data | 0x08);  // Set enable high
    I2C_Write(data);         // Set enable low
    I2C_Stop();
    _delay_ms(1);
}

// Write byte (8-bits) to LCD
void LCD_WriteByte(uint8_t byte, uint8_t mode) {
    LCD_WriteNibble(byte >> 4, mode);  // Send higher nibble
    LCD_WriteNibble(byte & 0x0F, mode);  // Send lower nibble
}