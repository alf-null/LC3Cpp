#include "Registers.h"

const uint16_t RegistersController::readRegister(Register location) const
{
	if (location > Register::REGISTERS_TOTAL - 1) {
		throw regException.INVALID_REGISTER();
	}
	return this->registers[location];
}

void RegistersController::writeRegister(Register location, uint16_t value)
{
	if (location > Register::REGISTERS_TOTAL - 1) {
		throw regException.INVALID_REGISTER();
	}
	this->registers[location] = value;
}
