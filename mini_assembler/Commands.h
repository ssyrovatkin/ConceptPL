#ifndef UNTITLED3_COMMANDS_H
#define UNTITLED3_COMMANDS_H

#include <string>

// R... - register
// [R...] - register value=address in memory
// V... - int32 value
// U... - int16 value
enum Commands {
    mov,      // mov Rx, Vy: Rx <- Vy
    movr,     // movr Rx, Ry: Rx <- Ry
    sub,      // sub Rx, Ry, Rz: Rx <- Ry - Rz
    add,      // add Rx, Ry, Rz: Rx <- Ry + Rz

    print,    // print Vx, Us: print memory[Vx:Vx+Us] values to console
    print_s,  // print_s Rx, Ry: print memory[Rx:Rx+Ry] values to console
    print_r,  // print_r Rx: print Rx value to console
    print_c,  // print_c Rx: print Rx value to console as a char
    inp,      // inp Rx: read value from console to Rx

    EXIT,     // exit: end execution

    b,        // b Vx: PC <- Vx
    bl,       // bl Vx: LR <- PC, PC <- Vx
    cmp,      // cmp Rx, Ry: write comparison result (Rx - Ry) to FLG
    bLE,      // bLE Vx: check FLG,  if <= 0 PC <- Vx
    bEQ,      // bEQ Vx: check FLG if == 0 PC <- Vx

    str,      // str Rx, [Ry]: store Rx in memory at address=Ry value
    load,     // load Rx, [Ry]: load value from memory at address=Ry value and put into Rx

    ret,      // PC <- LR

    loadstr,  // loadstr Rx, Ry, Ux, Uy: Rx <- Ux, Ry <- Uy
};

std::string commandToStr(uint8_t command);

#endif //UNTITLED3_COMMANDS_H
