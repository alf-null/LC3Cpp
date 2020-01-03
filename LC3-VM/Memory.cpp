#include "Memory.h"

uint16_t* MemoryController::pMemory() const
{
	return this->memory;
}

bool MemoryController::checkKey() const
{
	fd_set readfsd;
	FD_ZERO(&readfsd);
	FD_SET(STDIN_FILENO, &readfsd);

	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	return (1, &readfsd, nullptr, nullptr, &timeout) != 0;
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
		
		if (this->checkKey()) {
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
