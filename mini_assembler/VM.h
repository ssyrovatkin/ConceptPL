#ifndef UNTITLED3_VM_H
#define UNTITLED3_VM_H

#include <regex>
#include <fstream>
#include <iostream>
#include <cassert>

#include "CommandsRepr.h"

class VM {

public:
    VM(bool isDebug_);

    void init(const std::string &fileName);

    void run();

private:
    const bool isDebug;
    static const size_t ADDRESS_SIZE = sizeof(size_t);
    static const size_t MEM_SIZE = 8192;
    std::array<int64_t, MEM_SIZE * ADDRESS_SIZE> memory{};

    static const size_t NUM_REGISTERS = 64;
    std::array<int64_t, NUM_REGISTERS> registers{};

    size_t state(size_t address);

    static Commands decode(size_t value) {
        uint8_t command = *((uint8_t *) &value);
        return static_cast<Commands>(command);
    }

    // mov Rx, Vy: Rx <- Vy
    void mov(size_t value);

    // movr Rx, Ry: Rx <- Ry
    void movr(size_t value);

    // sub Rx, Ry, Rz: Rx <- Ry - Rz
    void sub(size_t value);

    // add Rx, Ry, Rz: Rx <- Ry + Rz
    void add(size_t value);

    // print Vx, Us: print memory[Vx:Vx+Us] values to console (casted to char)
    void print(size_t value);

    // print_s Rx, Ry: print memory[Rx:Rx+Ry] values to console
    void print_s(size_t value);

    // print_r Rx: print Rx value to console
    void print_r(size_t value);

    // print_c Rx: print Rx value to console as a char
    void print_c(size_t value);

    // inp Rx: read value from console to Rx
    void inp(size_t value);

    // b Vx: PC <- Vx
    void b(size_t value);

    // bl Vx: LR <- PC, PC <- Vx
    void bl(size_t value);

    // cmp Rx, Ry: write comparison result (Rx - Ry) to FLG
    void cmp(size_t value);

    // loadstr Rx, Ry, Ux, Uy: Rx <- Ux, Ry <- Uy
    void loadstr(size_t value);

    // bLE Vx: check FLG,  if <= 0 PC <- Vx
    void bLE(size_t value);

    // bEQ Vx: check FLG,  if == 0 PC <- Vx
    void bEQ(size_t value);

    // str Rx, [Ry]: store Rx in memory at address=Ry value
    void str(size_t value);

    // load Rx, [Ry]: load value from memory at address=Ry value and put into Rx
    void load(size_t value);

    // PC <- LR
    void ret();
};

#endif //UNTITLED3_VM_H
