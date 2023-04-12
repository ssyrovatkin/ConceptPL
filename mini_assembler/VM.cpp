#include "VM.h"

VM::VM(bool isDebug_): isDebug(isDebug_) {
}

void VM::init(const std::string &fileName) {
    // write program text to memory
    std::fstream file(fileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file : " + fileName);
    }

    file.seekg(0, std::ios::end);
    auto fileSize = file.tellg();

    file.seekp(0, std::ios_base::beg);
    file.read((char *) memory.data(), fileSize);
    file.close();

    // init sp, pc
    registers[PC] = 0;
    registers[SP] = MEM_SIZE;
}

void VM::run() {
    while (true) {
        size_t nextStateAddress = registers[PC];
        size_t nextState = state(nextStateAddress);
        Commands command = decode(nextState);

        switch (command) {
            case Commands::mov:
                mov(nextState);
                break;
            case Commands::movr:
                movr(nextState);
                break;
            case Commands::print:
                print(nextState);
                break;
            case Commands::print_s:
                print_s(nextState);
                break;
            case Commands::print_r:
                print_r(nextState);
                break;
            case Commands::print_c:
                print_c(nextState);
                break;
            case Commands::inp:
                inp(nextState);
                break;
            case Commands::EXIT:
                if (isDebug) std::cout << "exit" << std::endl;
                return;
            case Commands::bl:
                bl(nextState);
                break;
            case Commands::cmp:
                cmp(nextState);
                break;
            case Commands::loadstr:
                loadstr(nextState);
                break;
            case Commands::b:
                b(nextState);
                break;
            case Commands::bLE:
                bLE(nextState);
                break;
            case Commands::bEQ:
                bEQ(nextState);
                break;
            case Commands::sub:
                sub(nextState);
                break;
            case Commands::str:
                str(nextState);
                break;
            case Commands::load:
                load(nextState);
                break;
            case Commands::add:
                add(nextState);
                break;
            case Commands::ret:
                ret();
                if (isDebug) std::cout << "ret" << std::endl;
                break;
        }

        registers[PC] += 1;
    }
}


size_t VM::state(size_t address) {
    assert(address < MEM_SIZE);
    return memory[address];
}

// mov Rx, Vy: Rx <- Vy
void VM::mov(size_t value) {
    auto input = castFromSizeT<CommandRV>(value);
    if (isDebug) std::cout << input << std::endl;
    registers[input.regIdx] = input.value;
}

// movr Rx, Ry: Rx <- Ry
void VM::movr(size_t value) {
    auto input = castFromSizeT<CommandRR>(value);
    if (isDebug) std::cout << input << std::endl;
    registers[input.reg1Idx] = registers[input.reg2Idx];
}

// sub Rx, Ry, Rz: Rx <- Ry - Rz
void VM::sub(size_t value) {
    auto input = castFromSizeT<CommandRRR>(value);
    if (isDebug) std::cout << input << std::endl;
    registers[input.reg1Idx] = registers[input.reg2Idx] - registers[input.reg3Idx];
}

// add Rx, Ry, Rz: Rx <- Ry + Rz
void VM::add(size_t value) {
    auto input = castFromSizeT<CommandRRR>(value);
    if (isDebug) std::cout << input << std::endl;
    registers[input.reg1Idx] = registers[input.reg2Idx] + registers[input.reg3Idx];
}

// print Vx, Us: print memory[Vx:Vx+Us] values to console (casted to char)
void VM::print(size_t value) {
    auto input = castFromSizeT<CommandVU>(value);
    if (isDebug) std::cout << input << std::endl;
    auto startAddr = input.vValue;
    auto size = input.uValue;

    std::vector<char> printStr;
    for (auto i = startAddr; i < startAddr + size; ++i) {
        printStr.push_back(char(memory[i]));
    }
    std::string str(printStr.begin(), printStr.end());
    std::cout << str;
}

// print Rx, Ry: print memory[Rx:Rx+Ry] values to console
void VM::print_s(size_t value) {
    auto input = castFromSizeT<CommandRR>(value);
    if (isDebug) std::cout << input << std::endl;
    auto startAddr = registers[input.reg1Idx];
    auto size = registers[input.reg2Idx];

    std::vector<char> printStr;
    for (auto i = startAddr; i < startAddr + size; ++i) {
        printStr.push_back(char(memory[i]));
    }
    std::string str(printStr.begin(), printStr.end());
    std::cout << str;
}


// print_r Rx: print Rx value to console
void VM::print_r(size_t value) {
    auto input = castFromSizeT<CommandR>(value);
    if (isDebug) std::cout << input << std::endl;
    std::cout << registers[input.regIdx];
}

// print_c Rx: print Rx value to console as a char
void VM::print_c(size_t value) {
    auto input = castFromSizeT<CommandR>(value);
    if (isDebug) std::cout << input << std::endl;
    std::cout << char(registers[input.regIdx]);
}

// inp Rx: read value from console to Rx
void VM::inp(size_t value) {
    auto input = castFromSizeT<CommandR>(value);
    if (isDebug) std::cout << input << std::endl;
    uint32_t consoleInput;
    std::cin >> consoleInput;
    registers[input.regIdx] = consoleInput;
}

// bl Vx: LR <- PC, PC <- Vx
void VM::bl(size_t value) {
    auto input = castFromSizeT<CommandV>(value);
    if (isDebug) std::cout << input << std::endl;
    registers[LR] = registers[PC];
    registers[PC] = input.value;
}

// cmp Rx, Ry: write comparison result (Rx - Ry) to FLG
void VM::cmp(size_t value) {
    auto input = castFromSizeT<CommandRR>(value);
    if (isDebug) std::cout << input << std::endl;
    registers[FLG] = registers[input.reg1Idx] - registers[input.reg2Idx];
}

// loadstr Rx, Ry, Ux, Uy: Rx <- Ux, Ry <- Uy
void VM::loadstr(size_t value) {
    auto input = castFromSizeT<CommandRRUU>(value);
    if (isDebug) std::cout << input << std::endl;
    registers[input.reg1Idx] = input.u1Value;
    registers[input.reg2Idx] = input.u2Value;
}

// b Vx: PC <- Vx
void VM::b(size_t value) {
    auto input = castFromSizeT<CommandV>(value);
    if (isDebug) std::cout << input << std::endl;
    registers[PC] = input.value;
}

// bLE Vx: check FLG,  if <= 0 PC <- Vx
void VM::bLE(size_t value) {
    auto input = castFromSizeT<CommandV>(value);
    if (isDebug) std::cout << input << std::endl;
    if (registers[FLG] <= 0) {
        registers[PC] = input.value;
    }
}

// bEQ Vx: check FLG,  if == 0 PC <- Vx
void VM::bEQ(size_t value) {
    auto input = castFromSizeT<CommandV>(value);
    if (isDebug) std::cout << input << std::endl;
    if (registers[FLG] == 0) {
        registers[PC] = input.value;
    }
}


// str Rx, [Ry]: store Rx in memory at address=Ry value
void VM::str(size_t value) {
    auto input = castFromSizeT<CommandRR>(value);
    if (isDebug) std::cout << input << std::endl;
    memory[registers[input.reg2Idx]] = registers[input.reg1Idx];
}

// load Rx, [Ry]: load value from memory at address=Ry value and put into Rx
void VM::load(size_t value) {
    auto input = castFromSizeT<CommandRR>(value);
    if (isDebug) std::cout << input << std::endl;
    registers[input.reg1Idx] = memory[registers[input.reg2Idx]];
}

// PC <- LR
void VM::ret() {
    registers[PC] = registers[LR];
}
