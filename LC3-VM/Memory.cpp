#include "Memory.h"

const uint16_t MemoryController::readMemory(const unsigned int location) const
{
	if (location > MEM_MAX_SIZE -1) {
		throw memExceptions;
	}
	return this->memory[location];
}

void MemoryController::writeMemory(const unsigned int location, uint16_t value)
{
	if (location > MEM_MAX_SIZE - 1) {
		throw memExceptions;
	}
	this->memory[location] = value;
}
