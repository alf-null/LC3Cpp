#include "Memory.h"

bool checkKey() {
	return false;
}

uint16_t* MemoryController::pMemory() const
{
	return this->memory;
}

void MemoryController::cleanMemory()
{
	delete[] this->memory;
}

const uint16_t MemoryController::readMemory(const uint16_t location) const
{
	if (location > MEM_MAX_SIZE -1) {
		throw Error::CODES::OUTSIDE_OF_MEM_SPACE;
	}

	if (static_cast<RegistersController::IORegister>(location) == RegistersController::IORegister::KBSR) {
		
		if (checkKey()) {
			this->memory[static_cast<uint16_t>(RegistersController::IORegister::KBSR)] = (1 << 15);
			this->memory[static_cast<uint16_t>(RegistersController::IORegister::KBDR)] = getchar();
		}
		else {
			this->memory[static_cast<uint16_t>(RegistersController::IORegister::KBSR)] = 0;
		}
	}
	

	return this->memory[location];
}

void MemoryController::writeMemory(const uint16_t location, uint16_t value)
{
	if (location > MEM_MAX_SIZE - 1) {
		throw Error::CODES::OUTSIDE_OF_MEM_SPACE;
	}
	this->memory[location] = value;
}
