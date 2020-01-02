#pragma once

#include <memory>
#include <cmath>
#include <exception>

#include "Error.h"
#include "Registers.h"

typedef unsigned short	uint16_t;

class MemoryController
{
private:
	const unsigned int MEM_WORD_SIZE = 16;
	static const unsigned int MEM_MAX_SIZE = 65535; // Memory mapping from 0 - xFFFF
	uint16_t* memory = new uint16_t[MEM_MAX_SIZE];

public:
	uint16_t* pMemory() const;
	void cleanMemory();
	const uint16_t readMemory(const uint16_t location) const;
	void writeMemory(const uint16_t location, uint16_t value);
};

