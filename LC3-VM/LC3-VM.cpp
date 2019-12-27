// LC3-VM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>

#include "Memory.h"
#include "Registers.h"
#include "ISA.h"

constexpr uint16_t PC_START = 0x3000;

int main()
{
	MemoryController Memory;
	RegistersController Registers;

	// R_PC Initialization
	Registers.writeRegister(RegistersController::Register::R_PC, PC_START);
	
	// Instruction processing
	bool running = true;
	while (running)
	{
		try {
			uint16_t instr = Memory.readMemory(Registers.readRegister(RegistersController::Register::R_PC));
			Registers.writeRegister(RegistersController::Register::R_PC,
				Registers.readRegister(RegistersController::Register::R_PC) + 1);

			uint16_t op = instr >> 12;
			switch (op)
			{
			case ISA::OPCODES::OP_BR: {
				// https://justinmeiners.github.io/lc3-vm/supplies/lc3-isa.pdf 528
				ISA::fOP_BR(Memory, Registers, instr);
				break;
			}
			case ISA::OPCODES::OP_ADD: {
				// https://justinmeiners.github.io/lc3-vm/supplies/lc3-isa.pdf 526 
				ISA::fOP_ADD(Memory, Registers, instr);
				break;
			}
			case ISA::OPCODES::OP_LD:
				break;
			case ISA::OPCODES::OP_ST:
				break;
			case ISA::OPCODES::OP_JSR: {
				ISA::fOP_JSR(Memory, Registers, instr);
				break;
			}
			case ISA::OPCODES::OP_AND: {
				// https://justinmeiners.github.io/lc3-vm/supplies/lc3-isa.pdf 527 
				ISA::fOP_AND(Memory, Registers, instr);
				break;
			}
			case ISA::OPCODES::OP_LDR:
				break;
			case ISA::OPCODES::OP_STR:
				break;
			case ISA::OPCODES::OP_RTI: // Unnused (for now)
				throw Error::CODES::INVALID_OP;
				break;
			case ISA::OP_NOT: {
				// https://justinmeiners.github.io/lc3-vm/supplies/lc3-isa.pdf 535
				ISA::fOP_NOT(Memory, Registers, instr);
				break;
			}
			case ISA::OPCODES::OP_LDI: {
				// https://justinmeiners.github.io/lc3-vm/supplies/lc3-isa.pdf 532 
				ISA::fOP_LDI(Memory, Registers, instr);
				break;
			}
			
			case ISA::OPCODES::OP_STI:
				break;
			case ISA::OPCODES::OP_JMP: {
				ISA::fOP_JMP(Memory, Registers, instr);
				break;
			}
			case ISA::OPCODES::OP_RES: // Unnused (for now)
				throw Error::CODES::INVALID_OP;
				break;
			case ISA::OPCODES::OP_LEA:
				break;
			case ISA::OPCODES::OP_TRAP:
				break;
			default:
				throw Error::CODES::INVALID_OP;
				break;
			}
		}

		catch (Error::CODES & e) {
			switch (e)
			{
			case Error::CODES::INVALID_REG:
				std::cout << "Invalid access to a register" << std::endl;
				break;

			case Error::CODES::OUTSIDE_OF_MEM_SPACE:
				std::cout << "Invalid memory access" << std::endl;
				break;
			
			case Error::CODES::INVALID_OP:
				std::cout << "Invalid instruction" << std::endl;
				break;

			default:
				std::cout << "Unhandled error detected" << std::endl;
				break;
			}
			std::abort();
		}
	}
}