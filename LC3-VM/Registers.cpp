#include "Registers.h"

const uint16_t RegistersController::readRegister(Register location) const
{
	auto reg = static_cast<uint16_t>(location);
	if (reg > static_cast<uint16_t>(Register::REGISTERS_TOTAL) - 1) {
		throw Error::CODES::INVALID_REG;
	}
	return this->registers[reg];
}

void RegistersController::writeRegister(Register location, uint16_t value)
{
	auto reg = static_cast<uint16_t>(location);
	if (reg > static_cast<uint16_t>(Register::REGISTERS_TOTAL) - 1) {
		throw Error::CODES::INVALID_REG;
	}
	this->registers[reg] = value;
}

void RegistersController::updateFlags(Register location)
{
	auto reg = static_cast<uint16_t>(location);

	if (reg > static_cast<uint16_t>(Register::REGISTERS_TOTAL) - 1) {
		throw Error::CODES::INVALID_REG;
	}

	if (this->registers[reg] == 0) {
		this->registers[static_cast<uint16_t>(Register::R_CONDF)] = ISA::FL_ZRO;
	}
	else if (this->registers[reg] >> 15) {
		this->registers[static_cast<uint16_t>(Register::R_CONDF)] = ISA::FL_NEG;
	}
	else {
		this->registers[static_cast<uint16_t>(Register::R_CONDF)] = ISA::FL_POS;
	}
}
