#ifndef UNTITLED3_ASSEMBLER_H
#define UNTITLED3_ASSEMBLER_H
#include "CommandsRepr.h"

#include <regex>
#include <fstream>
#include <cassert>

class Assembler {
public:
    static void assemble(const std::string &inFileName, const std::string &outFileName);

private:
    static std::vector<std::string> readFileToLines(const std::string &fileName);

    static void writeFileBinary(const std::vector<size_t>& data, const std::string &fileName);

    static void deleteComments(std::vector<std::string> &lines);

    static std::vector<std::string> changeLabelsToOffsets(const std::vector<std::string> &lines);

    static void parseCommand(const std::string &command, std::vector<size_t> &result, int index);

    static uint8_t castRegister(std::string regName);

    static uint32_t castValue(const std::string &value);

    // mov Rx, Vy: Rx <- Vy
    static size_t mov(const std::smatch &sm);

    // movr Rx, Ry: Rx <- Ry
    static size_t movr(const std::smatch &sm);

    // sub Rx, Ry, Rz: Rx <- Ry - Rz
    static size_t sub(const std::smatch &sm);

    // add Rx, Ry, Rz: Rx <- Ry + Rz
    static size_t add(const std::smatch &sm);

    // print Vx, Us: print memory[Vx:Vx+Us] values to console (casted to char)
    static size_t print(const std::string &value, std::vector<size_t> &result);

    // loadstr Rx, Ry, Ux, Uy: Rx <- Ux, Ry <- Uy
    static size_t loadstr(const std::string &value, std::vector<size_t> &result);

    // print_s Rx, Ry: print memory[Rx:Rx+Ry] values to console
    static size_t print_s(const std::smatch &sm);

    // print_r Rx: print Rx value to console
    static size_t print_r(const std::smatch &sm);

    // print_c Rx: print Rx value to console as a char
    static size_t print_c(const std::smatch &sm);

    // inp Rx: read value from console to Rx
    static size_t inp(const std::smatch &sm);

    // bl Vx: LR <- PC, PC <- Vx
    static size_t bl(const std::smatch &sm);

    // cmp Rx, Ry: write comparison result (Rx - Ry) to FLG
    static size_t cmp(const std::smatch &sm);

    // b Vx: PC <- PC + Vx
    static size_t b(const std::smatch &sm);

    // bLE Vx: check FLG,  if <= 0 LR <- PC, PC <- Vx
    static size_t bLE(const std::smatch &sm);

    // bLE Vx: check FLG,  if == 0 LR <- PC, PC <- Vx
    static size_t bEQ(const std::smatch &sm);

    // str Rx, [Ry]: store Rx in memory at address=Ry value
    static size_t str(const std::smatch &sm);

    // load Rx, [Ry]: load value from memory at address=Ry value and put into Rx
    static size_t load(const std::smatch &sm);

    // PC <- LR
    static size_t ret();

    // exit
    static size_t exit();
};


#endif //UNTITLED3_ASSEMBLER_H
