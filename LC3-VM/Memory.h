#pragma once

#include <memory>
#include <cmath>
#include <exception>
#include "Error.h"

typedef unsigned short	uint16_t;

class MemoryController
{
private:
	const unsigned int MEM_WORD_SIZE = 16;
	static const unsigned int MEM_MAX_SIZE = 65535; // Memory mapping from 0 - xFFFF
	uint16_t* memory;

public:
	MemoryController() {
		memory = new uint16_t[MEM_MAX_SIZE];
	}
	~MemoryController()
	{
		delete[] memory;
	}
	uint16_t* pMemory() const;
	const uint16_t readMemory(const uint16_t location) const;
	void writeMemory(const uint16_t location, uint16_t value);
};

