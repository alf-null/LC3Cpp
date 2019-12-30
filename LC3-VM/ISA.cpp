#include "ISA.h"

uint16_t ISA::signExtend(uint16_t number, unsigned int bitCount)
{
    if ((number >> (bitCount - 1)) & 1) {
        number |= (0xFFFF << bitCount);
    }
    return number;
}

void ISA::fOP_BR(MemoryController Memory, RegistersController Registers, uint16_t instr)
{
    auto pcOffset = ISA::signExtend((instr) & 0x1FF, 9);
    auto flag = (instr >> 9) & 0x7;

    if (flag & Registers.readRegister(RegistersController::Register::R_CONDF)) {
        Registers.writeRegister(RegistersController::Register::R_PC, 
            Registers.readRegister(RegistersController::Register::R_PC) + pcOffset);
    }
}

void ISA::fOP_ADD(MemoryController Memory, RegistersController Registers, uint16_t instr)
{
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
}

void ISA::fOP_LD(MemoryController Memory, RegistersController Registers, uint16_t instr)
{
    auto r0 = static_cast<RegistersController::Register>((instr >> 9) & 0x7);
    uint16_t offset = ISA::signExtend(instr >> 0x1FF, 9);
    Registers.writeRegister(r0, (Memory.readMemory(static_cast<uint16_t>(RegistersController::Register::R_PC))+ offset));
    Registers.updateFlags(r0);
}

void ISA::fOP_ST(MemoryController Memory, RegistersController Registers, uint16_t instr)
{
    auto r0 = static_cast<RegistersController::Register>((instr >> 9) & 0x7);
    uint16_t offset = ISA::signExtend(instr >> 0x1FF, 9);
    Memory.writeMemory(Registers.readRegister(RegistersController::Register::R_PC) + offset, Registers.readRegister(r0));
}

void ISA::fOP_JSR(MemoryController Memory, RegistersController Registers, uint16_t instr)
{
    auto flag = (instr >> 11) & 1;
    Registers.writeRegister(RegistersController::Register::R_7, Registers.readRegister(RegistersController::Register::R_PC));

    if (flag) {
        uint16_t offset = ISA::signExtend((instr & 0x7FF), 11);
        Registers.writeRegister(RegistersController::Register::R_PC, Registers.readRegister(RegistersController::Register::R_PC) + offset);
    }
    else {
        auto r1 = static_cast<RegistersController::Register>((instr >> 6) & 0x7);
        Registers.writeRegister(RegistersController::Register::R_PC, Registers.readRegister(r1));
    }
}

void ISA::fOP_AND(MemoryController Memory, RegistersController Registers, uint16_t instr)
{
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
}

void ISA::fOP_LDR(MemoryController Memory, RegistersController Registers, uint16_t instr)
{
    auto r0 = static_cast<RegistersController::Register>((instr >> 9) & 0x7);
    auto r1 = static_cast<RegistersController::Register>((instr >> 6) & 0x7);
    uint16_t offset = ISA::signExtend((instr & 0x3F), 6);

    Registers.writeRegister(r0, Memory.readMemory(Registers.readRegister(r1) + offset));
    Registers.updateFlags(r0);
}

void ISA::fOP_STR(MemoryController Memory, RegistersController Registers, uint16_t instr)
{
    auto r0 = static_cast<RegistersController::Register>((instr >> 9) & 0x7);
    auto r1 = static_cast<RegistersController::Register>((instr >> 6) & 0x7);
    uint16_t offset = ISA::signExtend((instr & 0x3F), 6);

    Memory.writeMemory(Registers.readRegister(r1) + offset, Registers.readRegister(r0));
}

void ISA::fOP_RTI(MemoryController Memory, RegistersController Registers, uint16_t instr)
{
}

void ISA::fOP_NOT(MemoryController Memory, RegistersController Registers, uint16_t instr)
{
    // DR
    auto r0 = static_cast<RegistersController::Register>((instr >> 9) & 0x7);
    // SR1
    auto r1 = static_cast<RegistersController::Register>((instr >> 6) & 0x7);
    Registers.writeRegister(r0, ~Registers.readRegister(r1));
    Registers.updateFlags(r0);
}

void ISA::fOP_LDI(MemoryController Memory, RegistersController Registers, uint16_t instr)
{
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
}

void ISA::fOP_STI(MemoryController Memory, RegistersController Registers, uint16_t instr)
{
    auto r0 = static_cast<RegistersController::Register>((instr >> 9) & 0x7);
    uint16_t offset = ISA::signExtend(instr & 0x1FF, 9);
    Memory.writeMemory(
        Memory.readMemory(
            Registers.readRegister(RegistersController::Register::R_PC) + offset
        ), Registers.readRegister(r0)
    );
}

void ISA::fOP_JMP(MemoryController Memory, RegistersController Registers, uint16_t instr)
{
    // R1
    auto r1 = static_cast<RegistersController::Register>((instr >> 6) & 0x7);
    Registers.writeRegister(RegistersController::Register::R_PC, Registers.readRegister(r1));
}

void ISA::fOP_RES(MemoryController Memory, RegistersController Registers, uint16_t instr)
{
}

void ISA::fOP_LEA(MemoryController Memory, RegistersController Registers, uint16_t instr)
{
    auto r0 = static_cast<RegistersController::Register>((instr >> 9) & 0x7);
    uint16_t offset = ISA::signExtend(instr & 0x1FF, 9);
    Registers.writeRegister(r0, Registers.readRegister(RegistersController::Register::R_PC) + offset);
    Registers.updateFlags(r0);
}

void ISA::fGETC(MemoryController Memory, RegistersController Registers)
{
	Registers.writeRegister(RegistersController::Register::R_0, static_cast<uint16_t>(getchar()));
}

void ISA::fOUT(MemoryController Memory, RegistersController Registers)
{
	putc(static_cast<char>(Registers.readRegister(RegistersController::Register::R_0)), stdout);
	fflush(stdout);
}

void ISA::fPUTS(MemoryController Memory, RegistersController Registers)
{
	uint16_t* c = Memory.pMemory() + Registers.readRegister(RegistersController::Register::R_0);
	while (*c) {
		putc(static_cast<char>(*c), stdout);
		c++;
	}
	fflush(stdout);
}

void ISA::fIN(MemoryController Memory, RegistersController Registers)
{
	char c = getchar();
	putc(c, stdout);
	
	Registers.writeRegister(RegistersController::Register::R_0, static_cast<uint16_t>(c));
}

void ISA::fPUTSP(MemoryController Memory, RegistersController Registers)
{
	uint16_t* character = Memory.pMemory() + Registers.readRegister(RegistersController::Register::R_0);
	while(*character) {
		putc((*character) & 0xFF, stdout);
		char c2 = (*character) >> 8;
		if (c2) {
			putc(c2, stdout);
		}
	}

	fflush(stdout);
}

void ISA::fHALT(MemoryController Memory, RegistersController Registers, bool* running)
{
	puts("HALTING");
	fflush(stdout);
	*running = false;
}


void ISA::fOP_TRAP(MemoryController Memory, RegistersController Registers, uint16_t instr, bool* running)
{
	// The trap vector table has 256 memory locations from 0x0000 to 0x00FF
	switch (instr & 0xFF) {
	case ISA::TRAP::GETC: {
		ISA::fGETC(Memory, Registers);
		break;
	}

	case ISA::TRAP::OUT: {
		ISA::fOUT(Memory, Registers);
		break;
	}

	case ISA::TRAP::PUTS: {
		ISA::fPUTS(Memory, Registers);
		break;
	}

	case ISA::TRAP::IN: {
		ISA::fIN(Memory, Registers);
		break;
	}

	case ISA::TRAP::PUTSP: {
		ISA::fPUTSP(Memory, Registers);
		break;
	}

	case ISA::TRAP::HALT: {
		ISA::fHALT(Memory, Registers, running);
		break;
	}
	}
}

