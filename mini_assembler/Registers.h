#ifndef UNTITLED3_REGISTERS_H
#define UNTITLED3_REGISTERS_H

#include <string>

enum Registers {
    PC = 33,   // program counter
    SP = 34,   // stack pointer
    FLG = 35,  // flags register
    LR = 30    // link register (x30)
};

std::string registerToStr(uint8_t reg);

#endif //UNTITLED3_REGISTERS_H
