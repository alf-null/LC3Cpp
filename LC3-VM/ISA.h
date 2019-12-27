#pragma once

#include "Memory.h"
#include "Registers.h"

typedef unsigned short	uint16_t;

namespace ISA
{
	enum OPCODES : uint16_t {
		OP_BR = 0, /* branch */
		OP_ADD,    /* add  */
		OP_LD,     /* load */
		OP_ST,     /* store */
		OP_JSR,    /* jump register */
		OP_AND,    /* bitwise and */
		OP_LDR,    /* load register */
		OP_STR,    /* store register */
		OP_RTI,    /* unused */
		OP_NOT,    /* bitwise not */
		OP_LDI,    /* load indirect */
		OP_STI,    /* store indirect */
		OP_JMP,    /* jump */
		OP_RES,    /* reserved (unused) */
		OP_LEA,    /* load effective address */
		OP_TRAP,    /* execute trap */
		OP_OPS_NUMBER
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