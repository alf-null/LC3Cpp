#include "ISA.h"

uint16_t ISA::signExtend(uint16_t number, unsigned int bitCount)
{
    if ((number >> (bitCount - 1)) & 1) {
        number |= (0xFFFF << bitCount);
    }
    return number;
}
