#include "Assembler.h"

void Assembler::assemble(const std::string &inFileName, const std::string &outFileName) {
    auto lines = readFileToLines(inFileName);

    deleteComments(lines);

    auto commands = changeLabelsToOffsets(lines);

    std::vector<size_t> result(commands.size());

    for (int i = 0; i < commands.size(); ++i) {
        parseCommand(commands[i], result, i);
    }

    writeFileBinary(result, outFileName);
}

std::vector<std::string> Assembler::readFileToLines(const std::string &fileName) {
    std::fstream inFile(fileName, std::ios::in);

    if (!inFile) {
        throw std::runtime_error("Cannot open file : " + fileName);
    }

    std::vector<std::string> lines{};
    std::string str;
    while (std::getline(inFile, str)) {
        if (!str.empty()) lines.push_back(str);
    }
    inFile.close();

    return lines;
}

void Assembler::writeFileBinary(const std::vector<size_t> &data, const std::string &fileName) {
    std::fstream outFile(fileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    outFile.seekg(0, std::ios::beg);

    for (auto elem: data) {
        outFile.write((char *) &elem, sizeof(size_t));
    }

    outFile.close();
}

void Assembler::deleteComments(std::vector<std::string> &lines) {
    for (auto &line: lines) {
        line = line.substr(0, line.find("//"));
    }
}

std::vector<std::string> Assembler::changeLabelsToOffsets(const std::vector<std::string> &lines) {
    // "   .<label>:  "
    const std::regex labelRegex(" *(\\..*)\\: *");

    std::vector<std::pair<std::string, size_t>> labelLines{};
    std::vector<std::string> commands{};

    // leave only lines with commands, for lines with labels remember idx of the following command
    for (const auto &line: lines) {
        std::smatch sm;
        if (!regex_search(line, sm, labelRegex)) {
            commands.push_back(line);
        } else {
            auto label = sm[1].str();
            labelLines.emplace_back(label, commands.size() - 1);
        }
    }

    // replace labels with offsets
    for (auto &command: commands) {
        // "print" command cannot contain label as an argument,
        // but can contain it inside expr to print, so we skip such commands
        const std::regex printRegex(" *print *\"(.*)\"");
        std::smatch sm;
        if (regex_search(command, sm, printRegex)) continue;

        for (const auto &pair: labelLines) {
            command = std::regex_replace(command, std::regex("\\" + pair.first), std::to_string(pair.second));
        }
    }
    return commands;
}

void Assembler::parseCommand(const std::string &command, std::vector<size_t> &result, int index) {
    const std::regex commandRegex(R"((?: *([^ ]*))(?: *([^, ]*) *)(?:, *([^, ]*) *)?(?:, *([^, ]*) *)?)");
    std::smatch sm;

    if (regex_search(command, sm, commandRegex)) {
        auto commandName = sm[1].str();

        size_t res;
        if (commandName == "mov") {
            res = mov(sm);
        } else if (commandName == "movr") {
            res = movr(sm);
        } else if (commandName == "sub") {
            res = sub(sm);
        } else if (commandName == "add") {
            res = add(sm);
        } else if (commandName == "print") {
            res = print(command, result);
        } else if (commandName == "loadstr") {
            res = loadstr(command, result);
        } else if (commandName == "print_r") {
            res = print_r(sm);
        } else if (commandName == "print_s") {
            res = print_s(sm);
        } else if (commandName == "print_c") {
            res = print_c(sm);
        }else if (commandName == "inp") {
            res = inp(sm);
        } else if (commandName == "EXIT") {
            res = exit();
        } else if (commandName == "bl") {
            res = bl(sm);
        } else if (commandName == "cmp") {
            res = cmp(sm);
        } else if (commandName == "b") {
            res = b(sm);
        } else if (commandName == "bLE") {
            res = bLE(sm);
        } else if (commandName == "bEQ") {
            res = bEQ(sm);
        } else if (commandName == "str") {
            res = str(sm);
        } else if (commandName == "load") {
            res = load(sm);
        } else if (commandName == "ret") {
            res = ret();
        } else {
            throw std::runtime_error("Unable to parse command " + command);
        }

        result[index] = res;
    } else {
        throw std::runtime_error("Unable to parse command " + command);
    }
}

uint8_t Assembler::castRegister(std::string regName) {
    if (regName.empty()) {
        throw std::runtime_error("Parse error");
    }

    if (regName == "pc")
        return PC;
    if (regName == "sp")
        return SP;
    if (regName == "flg")
        return FLG;
    if (regName == "lr")
        return LR;
    assert(regName[0] == 'x');

    return std::stoi(regName.substr(1));
}

uint32_t Assembler::castValue(const std::string &value) {
    if (value.empty()) {
        throw std::runtime_error("Parse error");
    }
    return std::stoi(value);
}

// mov Rx, Vy: Rx <- Vy
size_t Assembler::mov(const std::smatch &sm) {
    return castToSizeT(CommandRV{.command = Commands::mov,
            .regIdx = castRegister(sm[2].str()),
            .value = castValue(sm[3].str())});
}

// movr Rx, Ry: Rx <- Ry
size_t Assembler::movr(const std::smatch &sm) {
    return castToSizeT(CommandRR{.command = Commands::movr,
            .reg1Idx = castRegister(sm[2].str()),
            .reg2Idx = castRegister(sm[3].str())});
}


// sub Rx, Ry, Rz: Rx <- Ry - Rz
size_t Assembler::sub(const std::smatch &sm) {
    return castToSizeT(CommandRRR{.command = Commands::sub,
            .reg1Idx = castRegister(sm[2].str()),
            .reg2Idx = castRegister(sm[3].str()),
            .reg3Idx = castRegister(sm[4].str())});

}

// add Rx, Ry, Rz: Rx <- Ry + Rz
size_t Assembler::add(const std::smatch &sm) {
    return castToSizeT(CommandRRR{.command = Commands::add,
            .reg1Idx = castRegister(sm[2].str()),
            .reg2Idx = castRegister(sm[3].str()),
            .reg3Idx = castRegister(sm[4].str())});
}

// print Vx, Us: print memory[Vx:Vx+Us] values to console (casted to char)
size_t Assembler::print(const std::string &value, std::vector<size_t> &result) {
    const std::regex printRegex(" *print *\"(.*)\"");
    std::smatch sm;

    if (regex_search(value, sm, printRegex)) {
        auto printString = sm[1].str();
        auto start = uint32_t(result.size());
        auto size = uint16_t(printString.size());
        for (char i: printString) {
            result.push_back(i);
        }
        return castToSizeT(CommandVU{.command=Commands::print,
                .uValue=size,
                .vValue=start,
        });
    } else {
        throw std::runtime_error("Incorrect print statement: " + value);
    }
}

// loadstr Rx, Ry, Ux, Uy: Rx <- Ux, Ry <- Uy
size_t Assembler::loadstr(const std::string &value, std::vector<size_t> &result) {
    const std::regex loadstrRegex(" *loadstr(?: *([^, ]*) *)(?:, *([^, ]*) *), *\"(.*)\"");
    std::smatch sm;

    if (regex_search(value, sm, loadstrRegex)) {
        auto reg1Idx = castRegister(sm[1].str());
        auto reg2Idx = castRegister(sm[2].str());
        auto loadString = sm[3].str();
        auto start = uint16_t(result.size());
        auto size = uint16_t(loadString.size());
        for (char i: loadString) {
            result.push_back(i);
        }
        return castToSizeT(CommandRRUU{.command=Commands::loadstr,
                .reg1Idx = reg1Idx,
                .reg2Idx = reg2Idx,
                .u1Value = start,
                .u2Value = size,
        });
    } else {
        throw std::runtime_error("Incorrect loadstr statement: " + value);
    }
}

size_t Assembler::print_s(const std::smatch &sm) {
    return castToSizeT(CommandRR{.command = Commands::print_s,
            .reg1Idx = castRegister(sm[2].str()),
            .reg2Idx = castRegister(sm[3].str())
    });
}

// print_r Rx: print Rx value to console
size_t Assembler::print_r(const std::smatch &sm) {
    return castToSizeT(CommandR{.command = Commands::print_r,
            .regIdx = castRegister(sm[2].str())});
}

size_t Assembler::print_c(const std::smatch &sm) {
    return castToSizeT(CommandR{.command = Commands::print_c,
            .regIdx = castRegister(sm[2].str())});
}

// inp Rx: read value from console to Rx
size_t Assembler::inp(const std::smatch &sm) {
    return castToSizeT(CommandR{.command = Commands::inp,
            .regIdx = castRegister(sm[2].str())});
}

// bl Vx: LR <- PC, PC <- Vx
size_t Assembler::bl(const std::smatch &sm) {
    return castToSizeT(CommandV{.command = Commands::bl,
            .value = castValue(sm[2].str())});
}

// cmp Rx, Ry: write comparison result (Rx - Ry) to FLG
size_t Assembler::cmp(const std::smatch &sm) {
    return castToSizeT(CommandRR{.command = Commands::cmp,
            .reg1Idx = castRegister(sm[2].str()),
            .reg2Idx = castRegister(sm[3].str())});
}

// bLE Vx: check FLG,  if <= 0 LR <- PC, PC <- Vx
size_t Assembler::bLE(const std::smatch &sm) {
    return castToSizeT(CommandV{.command = Commands::bLE,
            .value = castValue(sm[2].str())});
}

// bLE Vx: check FLG,  if == 0 LR <- PC, PC <- Vx
size_t Assembler::bEQ(const std::smatch &sm) {
    return castToSizeT(CommandV{.command = Commands::bEQ,
            .value = castValue(sm[2].str())});
}


// b Vx: PC <- Vx
size_t Assembler::b(const std::smatch &sm) {
    return castToSizeT(CommandV{.command = Commands::b,
            .value = castValue(sm[2].str())});
}

// str Rx, [Ry]: store Rx in memory at address=Ry value
size_t Assembler::str(const std::smatch &sm) {
    return castToSizeT(CommandRR{.command = Commands::str,
            .reg1Idx = castRegister(sm[2].str()),
            .reg2Idx = castRegister(sm[3].str())});
}

// load Rx, [Ry]: load value from memory at address=Ry value and put into Rx
size_t Assembler::load(const std::smatch &sm) {
    return castToSizeT(CommandRR{.command = Commands::load,
            .reg1Idx = castRegister(sm[2].str()),
            .reg2Idx = castRegister(sm[3].str())});
}

// PC <- LR
size_t Assembler::ret() {
    return castToSizeT(Command{.command = Commands::ret});
}

// exit
size_t Assembler::exit() {
    return castToSizeT(Command{.command = Commands::EXIT});
}