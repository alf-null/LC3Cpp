// LC3-VM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Memory.h"
#include "ISA.h"
#include "Registers.h"	

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
		uint16_t instr = Memory.readMemory(Registers.readRegister(RegistersController::Register::R_PC));
		Registers.writeRegister(RegistersController::Register::R_PC, 
								Registers.readRegister(RegistersController::Register::R_PC)+1 );

		uint16_t op = instr >> 12;
		switch (op)
		{
		case ISA::OP_BR:
			break;
		case ISA::OP_ADD:
			break;
		case ISA::OP_LD:
			break;
		case ISA::OP_ST:
			break;
		case ISA::OP_JSR:
			break;
		case ISA::OP_AND:
			break;
		case ISA::OP_LDR:
			break;
		case ISA::OP_STR:
			break;
		case ISA::OP_RTI:
			break;
		case ISA::OP_NOT:
			break;
		case ISA::OP_LDI:
			break;
		case ISA::OP_STI:
			break;
		case ISA::OP_JMP:
			break;
		case ISA::OP_RES:
			break;
		case ISA::OP_LEA:
			break;
		case ISA::OP_TRAP:
			break;
		default:
			break;
		}
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
