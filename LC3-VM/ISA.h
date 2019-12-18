#pragma once

enum class ISA : unsigned int {
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

enum class FLAGS : unsigned char {
	FL_POS = 1 << 0, /* Positive flag */
	FL_ZRO = 1 << 1, /* Zero flag */
	FL_NEG = 1 << 2 /* Negative flag */
};