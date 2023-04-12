#ifndef UNTITLED3_COMMANDSREPR_H
#define UNTITLED3_COMMANDSREPR_H

#include "Registers.h"
#include "Commands.h"
#include <cstdint>
#include <ostream>

template<typename T>
size_t castToSizeT(const T &structObj) {
    size_t result = *((size_t * ) & structObj);
    return result;
}

template<typename T>
T castFromSizeT(const size_t &value) {
    T result = *((T *) &value);
    return result;
}

// struct for commands like [CMD]
struct Command {
    uint8_t command; // Commands

};

// struct for commands like [CMD] Rx
struct CommandR {
    uint8_t command; // Commands
    uint8_t regIdx;
};

// struct for commands like [CMD] Rx, Ry
struct CommandRR {
    uint8_t command; // Commands
    uint8_t reg1Idx;
    uint8_t reg2Idx;
};

// struct for commands like [CMD] Rx, Ry, Rz
struct CommandRRR {
    uint8_t command; // Commands
    uint8_t reg1Idx;
    uint8_t reg2Idx;
    uint8_t reg3Idx;
};

// struct for commands like [CMD] Vx
struct CommandV {
    uint8_t command; // Commands
    uint32_t value;
};

// struct for commands like [CMD] Rx, Vy
struct CommandRV {
    uint8_t command; // Commands
    uint8_t regIdx;
    uint32_t value;
};

// struct for commands like [CMD] Vx, Uy
struct CommandVU {
    uint8_t command; // Commands
    uint16_t uValue;
    uint32_t vValue;
};

// struct for commands like [CMD] Rx, Ry, Ux, Uy
struct CommandRRUU {
    uint8_t command; // Commands
    uint8_t reg1Idx;
    uint8_t reg2Idx;
    uint16_t u1Value;
    uint16_t u2Value;
};

std::ostream &operator<<(std::ostream &os, Command command);
std::ostream &operator<<(std::ostream &os, CommandR command);
std::ostream &operator<<(std::ostream &os, CommandRR command);
std::ostream &operator<<(std::ostream &os, CommandRRR command);
std::ostream &operator<<(std::ostream &os, CommandV command);
std::ostream &operator<<(std::ostream &os, CommandRV command);
std::ostream &operator<<(std::ostream &os, CommandVU command);
std::ostream &operator<<(std::ostream &os, CommandRRUU command);

#endif //UNTITLED3_COMMANDSREPR_H
