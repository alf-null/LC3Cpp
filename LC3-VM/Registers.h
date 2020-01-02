#pragma once

#include <exception>
#include "Error.h"

typedef unsigned short uint16_t;

class RegistersController
{
public:
	static enum class Register : unsigned int {
		R_0,
		R_1,
		R_2,
		R_3,
		R_4,
		R_5,
		R_6,
		R_7,
		R_PC,
		R_CONDF,
		REGISTERS_TOTAL
	};

	static enum class IORegister : uint16_t {
		KBSR	= 0xFE00,	/* The ready bit (bit [15]) indicates if 
								the keyboard has received a new character */
		
		KBDR	= 0xFE02,	/* Bits [7:0] contain the last character typed on the keyboard. */
		
		DSR		= 0xFE04,	/*  The ready bit (bit [15]) indicates if the display 
								device is ready to receive another character to print on the screen */
		
		DDR		= 0xFE06,	/*  A character written in the low byte
								of this register will be displayed on the screen. */
		
		MCR		= 0xFFFE	/*  Bit [15] is the clock enable bit.
								When cleared, instruction processing stops. */
	};

	enum {
		FL_POS = 1 << 0, // Positive flag 
		FL_ZRO = 1 << 1, // Zero flag */
		FL_NEG = 1 << 2 // Negative flag */
	};

	const uint16_t readRegister(Register location) const;
	void writeRegister(Register location, uint16_t value);
	void updateFlags(Register location);

private:
	uint16_t registers[10U];
};