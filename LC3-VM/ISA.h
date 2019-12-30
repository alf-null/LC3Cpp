#pragma once

#include "Memory.h"
#include "Registers.h"

typedef unsigned short	uint16_t;

namespace ISA
{
	enum OPCODES : uint16_t {
		OP_BR = 0, // Branch
		OP_ADD,    // Add
		OP_LD,     // Load
		OP_ST,     // Store
		OP_JSR,    // Jump register
		OP_AND,    // Bitwise and
		OP_LDR,    // Load register
		OP_STR,    // Store register
		OP_RTI,    // Return from interrupt
		OP_NOT,    // Bitwise not
		OP_LDI,    // Load indirect
		OP_STI,    // Store indirect
		OP_JMP,    // Jump
		OP_RES,    // Reserved
		OP_LEA,    // Load effective address
		OP_TRAP,   // Trap
		OP_OPS_NUMBER
	};

	enum TRAP : uint16_t {
		TRAP_GETC = 0x20,  //  Read char from keyboard
		TRAP_OUT,   //  Output a char
		TRAP_PUTS,  //  Output a string
		TRAP_IN,    //  Get char from keyboard > output on terminal
		TRAP_PUTSP, //  Output a byte string
		TRAP_HALT   //  Halt
	};

	void fOP_BR(MemoryController Memory, RegistersController Registers, uint16_t instr);
	void fOP_ADD(MemoryController Memory, RegistersController Registers, uint16_t instr);
	void fOP_LD(MemoryController Memory, RegistersController Registers, uint16_t instr); 
	void fOP_ST(MemoryController Memory, RegistersController Registers, uint16_t instr);
	void fOP_JSR(MemoryController Memory, RegistersController Registers, uint16_t instr);
	void fOP_AND(MemoryController Memory, RegistersController Registers, uint16_t instr);
	void fOP_LDR(MemoryController Memory, RegistersController Registers, uint16_t instr);
	void fOP_STR(MemoryController Memory, RegistersController Registers, uint16_t instr);
	void fOP_RTI(MemoryController Memory, RegistersController Registers, uint16_t instr);
	void fOP_NOT(MemoryController Memory, RegistersController Registers, uint16_t instr);
	void fOP_LDI(MemoryController Memory, RegistersController Registers, uint16_t instr);
	void fOP_STI(MemoryController Memory, RegistersController Registers, uint16_t instr);
	void fOP_JMP(MemoryController Memory, RegistersController Registers, uint16_t instr);
	void fOP_RES(MemoryController Memory, RegistersController Registers, uint16_t instr);
	void fOP_LEA(MemoryController Memory, RegistersController Registers, uint16_t instr);
	void fOP_TRAP(MemoryController Memory, RegistersController Registers, uint16_t instr);
	
	uint16_t signExtend(uint16_t number, unsigned int bitCount);
};