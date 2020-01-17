#pragma once

#include <cmath>
#include <ctime>
#include <memory>
#include <exception>

#include <WinSock2.h>

#include "Error.h"
#include "Registers.h"

#pragma comment(lib, "Ws2_32.lib")

typedef unsigned short	uint16_t;

constexpr unsigned int STDIN_FILENO = 0;

class MemoryController
{
private:
	const unsigned int MEM_WORD_SIZE = 16;
	static const unsigned int MEM_MAX_SIZE = 65535; // Memory mapping from 0 - xFFFF
	uint16_t* memory = (uint16_t*)HeapAlloc(
		GetProcessHeap(),
		HEAP_ZERO_MEMORY,
		sizeof(uint16_t) * MEM_MAX_SIZE
	);

public:
	uint16_t* pMemory() const;
	bool checkKey() const;
	void cleanMemory();
	const uint16_t readMemory(const uint16_t location) const;
	void writeMemory(const uint16_t location, uint16_t value);
};

