/**
 * Generated Ports header File
 * 
 * @file port.h
 * 
 * @ingroup pinsdriver
 * 
 * @brief This Source file provides APIs. 
 *
 * @version Driver Version  1.0.1
*/

/*
� [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/


#ifndef PORT_INCLUDED
#define PORT_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "utils/compiler.h"

/* @ingroup pinsdriver
 * @enum port_pull_mode
 * Defines the pullup modes.
 */
enum port_pull_mode {
	PORT_PULL_OFF,
	PORT_PULL_UP,
};

/* @ingroup pinsdriver
 * @enum port_dir
 * Defines the port directions.
 */
enum port_dir {
	PORT_DIR_IN,
	PORT_DIR_OUT,
	PORT_DIR_OFF,
};

/**
 * @ingroup  pinsdriver
 * @brief Set port pin pull mode, Configure pin to pull up, down or disable pull mode, supported pull modes are defined by device used.
 * @param pin The pin number within port
 * @param pull_mode Pin pull mode
 * @return none
 */
static inline void PORTA_set_pin_pull_mode(const uint8_t pin, const enum port_pull_mode pull_mode)
{
	volatile uint8_t *port_pin_ctrl = ((uint8_t *)&PORTA + 0x10 + pin);

	if (pull_mode == PORT_PULL_UP) {
		*port_pin_ctrl |= PORT_PULLUPEN_bm;
	} else if (pull_mode == PORT_PULL_OFF) {
		*port_pin_ctrl &= ~PORT_PULLUPEN_bm;
	}
}

/**
 * @ingroup  pinsdriver
 * @brief Set port pin inverted mode, Configure pin invert I/O or not.
 * @param pin The pin number within port
 * @param inverted Pin inverted mode
 * @return none
 */
static inline void PORTA_pin_set_inverted(const uint8_t pin, const bool inverted)
{
	volatile uint8_t *port_pin_ctrl = ((uint8_t *)&PORTA + 0x10 + pin);

	if (inverted) {
		*port_pin_ctrl |= PORT_INVEN_bm;
	} else {
		*port_pin_ctrl &= ~PORT_INVEN_bm;
	}
}

/**
 * @ingroup  pinsdriver
 * @brief Set port pin input/sense configuration, Enable/disable digital input buffer and pin change interrupt,
 * 		  select pin interrupt edge/level sensing mode 
 * @param The pin number within port
 * @param isc PORT_ISC_t
 * @return none
 */
static inline void PORTA_pin_set_isc(const uint8_t pin, const PORT_ISC_t isc)
{
	volatile uint8_t *port_pin_ctrl = ((uint8_t *)&PORTA + 0x10 + pin);

	*port_pin_ctrl = (*port_pin_ctrl & ~PORT_ISC_gm) | isc;
}

/**
 * @ingroup  pinsdriver
 * @brief Set port data direction, Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * @param mask      Bit mask where 1 means apply direction setting to the
 *                      corresponding pin
 * @param dir port_dir
 * @return none
 */
static inline void PORTA_set_port_dir(const uint8_t mask, const enum port_dir dir)
{
	switch (dir) {
	case PORT_DIR_IN:
		VPORTA.DIR &= ~mask;
		break;
	case PORT_DIR_OUT:
		VPORTA.DIR |= mask;
		break;
	case PORT_DIR_OFF:
		/*/ should activate the pullup for power saving
		  but a bit costly to do it here */
		{
			for (uint8_t i = 0; i < 8; i++) {
				if (mask & 1 << i) {
					*((uint8_t *)&PORTA + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
				}
			}
		}
		break;
	default:
		break;
	}
}

/**
 * @ingroup  pinsdriver
 * @brief Set port pin data direction, Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * @param pin       The pin number within port
 * @param dir port_dir
 * @return none
 */
static inline void PORTA_set_pin_dir(const uint8_t pin, const enum port_dir dir)
{
	switch (dir) {
	case PORT_DIR_IN:
		VPORTA.DIR &= ~(1 << pin);
		break;
	case PORT_DIR_OUT:
		VPORTA.DIR |= (1 << pin);
		break;
	case PORT_DIR_OFF:
		*((uint8_t *)&PORTA + 0x10 + pin) |= 1 << PORT_PULLUPEN_bp;
		break;
	default:
		break;
	}
}

/**
 * @ingroup  pinsdriver
 * @brief Set port level, Sets output level on the pins defined by the bit mask.
 *
 * @param mask  Bit mask where 1 means apply port level to the corresponding
 *                  pin
 * @param level -boolean value that defines the logic state of the pin level
 *                  false = Pin levels set to "low" state
 * @return none
 */
static inline void PORTA_set_port_level(const uint8_t mask, const bool level)
{
	if (level == true) {
		VPORTA.OUT |= mask;
	} else {
		VPORTA.OUT &= ~mask;
	}
}

/**
 * @ingroup  pinsdriver
 * @brief Set port level, Sets output level on a pin.
 *
 * @param pin       The pin number within port
 * @param level -boolean value that defines the logic state of the pin level
 * @return none
 */
static inline void PORTA_set_pin_level(const uint8_t pin, const bool level)
{
	if (level == true) {
		VPORTA.OUT |= (1 << pin);
	} else {
		VPORTA.OUT &= ~(1 << pin);
	}
}

/**
 * @ingroup  pinsdriver
 * @brief Toggle out level on pins, Toggle the pin levels on pins defined by bit mask.
 *
 * @param mask  Bit mask where 1 means toggle pin level to the corresponding
 *                  pin
 * @return none
 */
static inline void PORTA_toggle_port_level(const uint8_t mask)
{
	PORTA.OUTTGL = mask;
}

/**
 * @ingroup  pinsdriver
 * @brief Toggle output level on pin, Toggle the pin levels on pins defined by bit mask.
 *
 * @param pin       The pin number within port
 * @return none
 */
static inline void PORTA_toggle_pin_level(const uint8_t pin)
{
	PORTA.OUTTGL = 1 << pin;
}

/**
 * @ingroup  pinsdriver
 * @brief Get input level on pins, Read the input level on pins connected to a port.
 *
 * @param none
 * @return none
 */
static inline uint8_t PORTA_get_port_level()
{
	return VPORTA.IN;
}

/**
 * @ingroup  pinsdriver
 * @brief Get level on pin, Reads the level on pins connected to a port.
 *
 * @param pin       The pin number within port
 * @return none
 */
static inline bool PORTA_get_pin_level(const uint8_t pin)
{
	return VPORTA.IN & (1 << pin);
}

/**
 * @ingroup  pinsdriver
 * @brief Write value to Port, Write directly to the port OUT register.
 *
 * @param value Value to write to the port register
 * @return none
 */
static inline void PORTA_write_port(const uint8_t value)
{
	VPORTA.OUT = value;
}

/**
 * @ingroup  pinsdriver
 * @brief Set port pin pull mode, Configure pin to pull up, down or disable pull mode, supported pull modes are defined by device used.
 * @param pin The pin number within port
 * @param pull_mode Pin pull mode
 * @return none
 */
static inline void PORTB_set_pin_pull_mode(const uint8_t pin, const enum port_pull_mode pull_mode)
{
	volatile uint8_t *port_pin_ctrl = ((uint8_t *)&PORTB + 0x10 + pin);

	if (pull_mode == PORT_PULL_UP) {
		*port_pin_ctrl |= PORT_PULLUPEN_bm;
	} else if (pull_mode == PORT_PULL_OFF) {
		*port_pin_ctrl &= ~PORT_PULLUPEN_bm;
	}
}

/**
 * @ingroup  pinsdriver
 * @brief Set port pin inverted mode, Configure pin invert I/O or not.
 * @param pin The pin number within port
 * @param inverted Pin inverted mode
 * @return none
 */
static inline void PORTB_pin_set_inverted(const uint8_t pin, const bool inverted)
{
	volatile uint8_t *port_pin_ctrl = ((uint8_t *)&PORTB + 0x10 + pin);

	if (inverted) {
		*port_pin_ctrl |= PORT_INVEN_bm;
	} else {
		*port_pin_ctrl &= ~PORT_INVEN_bm;
	}
}

/**
 * @ingroup  pinsdriver
 * @brief Set port pin input/sense configuration, Enable/disable digital input buffer and pin change interrupt,
 * 		  select pin interrupt edge/level sensing mode 
 * @param The pin number within port
 * @param isc PORT_ISC_t
 * @return none
 */
static inline void PORTB_pin_set_isc(const uint8_t pin, const PORT_ISC_t isc)
{
	volatile uint8_t *port_pin_ctrl = ((uint8_t *)&PORTB + 0x10 + pin);

	*port_pin_ctrl = (*port_pin_ctrl & ~PORT_ISC_gm) | isc;
}

/**
 * @ingroup  pinsdriver
 * @brief Set port data direction, Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * @param mask      Bit mask where 1 means apply direction setting to the
 *                      corresponding pin
 * @param dir port_dir
 * @return none
 */
static inline void PORTB_set_port_dir(const uint8_t mask, const enum port_dir dir)
{
	switch (dir) {
	case PORT_DIR_IN:
		VPORTB.DIR &= ~mask;
		break;
	case PORT_DIR_OUT:
		VPORTB.DIR |= mask;
		break;
	case PORT_DIR_OFF:
		/*/ should activate the pullup for power saving
		  but a bit costly to do it here */
		{
			for (uint8_t i = 0; i < 8; i++) {
				if (mask & 1 << i) {
					*((uint8_t *)&PORTB + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
				}
			}
		}
		break;
	default:
		break;
	}
}

/**
 * @ingroup  pinsdriver
 * @brief Set port pin data direction, Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * @param pin       The pin number within port
 * @param dir port_dir
 * @return none
 */
static inline void PORTB_set_pin_dir(const uint8_t pin, const enum port_dir dir)
{
	switch (dir) {
	case PORT_DIR_IN:
		VPORTB.DIR &= ~(1 << pin);
		break;
	case PORT_DIR_OUT:
		VPORTB.DIR |= (1 << pin);
		break;
	case PORT_DIR_OFF:
		*((uint8_t *)&PORTB + 0x10 + pin) |= 1 << PORT_PULLUPEN_bp;
		break;
	default:
		break;
	}
}

/**
 * @ingroup  pinsdriver
 * @brief Set port level, Sets output level on the pins defined by the bit mask.
 *
 * @param mask  Bit mask where 1 means apply port level to the corresponding
 *                  pin
 * @param level -boolean value that defines the logic state of the pin level
 *                  false = Pin levels set to "low" state
 * @return none
 */
static inline void PORTB_set_port_level(const uint8_t mask, const bool level)
{
	if (level == true) {
		VPORTB.OUT |= mask;
	} else {
		VPORTB.OUT &= ~mask;
	}
}

/**
 * @ingroup  pinsdriver
 * @brief Set port level, Sets output level on a pin.
 *
 * @param pin       The pin number within port
 * @param level -boolean value that defines the logic state of the pin level
 * @return none
 */
static inline void PORTB_set_pin_level(const uint8_t pin, const bool level)
{
	if (level == true) {
		VPORTB.OUT |= (1 << pin);
	} else {
		VPORTB.OUT &= ~(1 << pin);
	}
}

/**
 * @ingroup  pinsdriver
 * @brief Toggle out level on pins, Toggle the pin levels on pins defined by bit mask.
 *
 * @param mask  Bit mask where 1 means toggle pin level to the corresponding
 *                  pin
 * @return none
 */
static inline void PORTB_toggle_port_level(const uint8_t mask)
{
	PORTB.OUTTGL = mask;
}

/**
 * @ingroup  pinsdriver
 * @brief Toggle output level on pin, Toggle the pin levels on pins defined by bit mask.
 *
 * @param pin       The pin number within port
 * @return none
 */
static inline void PORTB_toggle_pin_level(const uint8_t pin)
{
	PORTB.OUTTGL = 1 << pin;
}

/**
 * @ingroup  pinsdriver
 * @brief Get input level on pins, Read the input level on pins connected to a port.
 *
 * @param none
 * @return none
 */
static inline uint8_t PORTB_get_port_level()
{
	return VPORTB.IN;
}

/**
 * @ingroup  pinsdriver
 * @brief Get level on pin, Reads the level on pins connected to a port.
 *
 * @param pin       The pin number within port
 * @return none
 */
static inline bool PORTB_get_pin_level(const uint8_t pin)
{
	return VPORTB.IN & (1 << pin);
}

/**
 * @ingroup  pinsdriver
 * @brief Write value to Port, Write directly to the port OUT register.
 *
 * @param value Value to write to the port register
 * @return none
 */
static inline void PORTB_write_port(const uint8_t value)
{
	VPORTB.OUT = value;
}
#ifdef __cplusplus
}
#endif

#endif /* PORT_INCLUDED */