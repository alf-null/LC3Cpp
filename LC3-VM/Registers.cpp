#include "Registers.h"

const uint16_t RegistersController::readRegister(Register location) const
{
	auto reg = static_cast<uint16_t>(location);
	if (reg > static_cast<uint16_t>(Register::REGISTERS_TOTAL) - 1) {
		throw regException.INVALID_REGISTER();
	}
	return this->registers[reg];
}

void RegistersController::writeRegister(Register location, uint16_t value)
{
	auto reg = static_cast<uint16_t>(location);
	if (reg > static_cast<uint16_t>(Register::REGISTERS_TOTAL) - 1) {
		throw regException.INVALID_REGISTER();
	}
	this->registers[reg] = value;
}
