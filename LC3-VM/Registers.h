#pragma once

#include <exception>
#include "Error.h"

typedef unsigned short uint16_t;

class RegistersController
{
public:
	enum class Register : unsigned int
	{
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

	enum {
		FL_POS = 1 << 0, /* Positive flag */
		FL_ZRO = 1 << 1, /* Zero flag */
		FL_NEG = 1 << 2 /* Negative flag */
	};

	const uint16_t readRegister(Register location) const;
	void writeRegister(Register location, uint16_t value);
	void updateFlags(Register location);

private:
	uint16_t registers[10U];
};