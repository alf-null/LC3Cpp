#pragma once

#include <memory>
#include <cmath>
#include <cstdint>
#include <exception>
#include "Error.h"

class MemException: public std::exception
{
public:
	const Error::CODES OUTSIDE_OF_MEM_SPACE() const throw() {
		return Error::CODES::OUTSIDE_OF_MEM_SPACE;
	}
};


class MemoryController
{
private:
	MemException memExceptions;

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
	const uint16_t readMemory(const unsigned int location) const;
	void writeMemory(const unsigned	int location, uint16_t value);
};

