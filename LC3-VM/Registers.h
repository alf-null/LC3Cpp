#pragma once

#include <exception>
#include "ISA.h"
#include "Error.h"

typedef unsigned short  suint16_t;

class RegException: public std::exception
{
public:
	virtual const char* what() const throw() {
		return "Invalid register access";
	}
};


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

	const uint16_t readRegister(Register location) const;
	void writeRegister(Register location, uint16_t value);
	void updateFlags(Register location);

private:
	RegException regException;
	uint16_t registers[10U];
};