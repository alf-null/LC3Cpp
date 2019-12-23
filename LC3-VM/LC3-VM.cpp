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
			case ISA::OP_BR: {
				// https://justinmeiners.github.io/lc3-vm/supplies/lc3-isa.pdf 528
				auto pcOffset = ISA::signExtend((instr) & 0x1FF, 9);
				auto flag = (instr >> 9) & 0x7;

				if (flag & Registers.readRegister(RegistersController::Register::R_CONDF)) {
					Registers.writeRegister(RegistersController::Register::R_PC, 
						Registers.readRegister(RegistersController::Register::R_PC) + pcOffset);
				}

				break;
			}
			case ISA::OP_ADD: {
				// https://justinmeiners.github.io/lc3-vm/supplies/lc3-isa.pdf 526 
				// DR
				auto r0 = static_cast<RegistersController::Register>((instr >> 9) & 0x7);
				// SR1
				auto r1 = static_cast<RegistersController::Register>((instr >> 6) & 0x7);
				// Has inmediate mode?
				auto immFlag = (instr >> 5) & 0x1;
				if (immFlag) {
					auto imm5 = ISA::signExtend(instr & 0x1F, 5);
					Registers.writeRegister(r0, Registers.readRegister(r1) + imm5);
				}
				else {
					auto r2 = static_cast<RegistersController::Register>(instr & 0x7);
					Registers.writeRegister(r0, Registers.readRegister(r1) + Registers.readRegister(r2));
				}

				Registers.updateFlags(r0);
				break;
			}
			case ISA::OP_LD:
				break;
			case ISA::OP_ST:
				break;
			case ISA::OP_JSR:
				break;
			case ISA::OP_AND: {
				// https://justinmeiners.github.io/lc3-vm/supplies/lc3-isa.pdf 527 
				// DR
				auto r0 = static_cast<RegistersController::Register>((instr >> 9) & 0x7);
				// SR1
				auto r1 = static_cast<RegistersController::Register>((instr >> 6) & 0x7);
				auto immFlag = (instr >> 5) & 0x1;
				if (immFlag) {
					auto imm5 = ISA::signExtend(instr & 0x1F, 5);
					Registers.writeRegister(r0, Registers.readRegister(r1) & imm5);
				}
				else {
					// SR2
					auto r2 = static_cast<RegistersController::Register>(instr & 0x7);
					Registers.writeRegister(r0, Registers.readRegister(r1) & Registers.readRegister(r2));
				}

				Registers.updateFlags(r0);
				break;
			}
			case ISA::OP_LDR:
				break;
			case ISA::OP_STR:
				break;
			case ISA::OP_RTI: // Unnused (for now)
				throw Error::CODES::INVALID_OP;
				break;
			case ISA::OP_NOT: {
				// https://justinmeiners.github.io/lc3-vm/supplies/lc3-isa.pdf 535
				// DR
				auto r0 = static_cast<RegistersController::Register>((instr >> 9) & 0x7);
				// SR1
				auto r1 = static_cast<RegistersController::Register>((instr >> 6) & 0x7);
				Registers.writeRegister(r0, ~Registers.readRegister(r1));
				Registers.updateFlags(r0);
				break;
			}
			case ISA::OP_LDI: {
				// https://justinmeiners.github.io/lc3-vm/supplies/lc3-isa.pdf 532 
				// DR
				auto r0 = static_cast<RegistersController::Register>((instr >> 9) & 0x7);
				// PCoffset9
				uint16_t pcOffset = ISA::signExtend(instr & 0x1FF, 9);

				Registers.writeRegister(r0, 
					Memory.readMemory( 
						Memory.readMemory( Registers.readRegister(RegistersController::Register::R_PC) + pcOffset ) 
					) 
				);

				Registers.updateFlags(r0);
				break;
			}
			
			case ISA::OP_STI:
				break;
			case ISA::OP_JMP:
				break;
			case ISA::OP_RES: // Unnused (for now)
				throw Error::CODES::INVALID_OP;
				break;
			case ISA::OP_LEA:
				break;
			case ISA::OP_TRAP:
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