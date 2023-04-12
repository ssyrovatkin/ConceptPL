#include "CommandsRepr.h"


std::ostream &operator<<(std::ostream &os, Command command) {
    return os << commandToStr(command.command);
}

std::ostream &operator<<(std::ostream &os, CommandR command) {
    return os << commandToStr(command.command) << " " << registerToStr(command.regIdx);
}

std::ostream &operator<<(std::ostream &os, CommandRR command) {
    return os << commandToStr(command.command) << " " << registerToStr(command.reg1Idx) << ", " << registerToStr(command.reg2Idx);
}

std::ostream &operator<<(std::ostream &os, CommandRRR command) {
    return os << commandToStr(command.command) << " " << registerToStr(command.reg1Idx) << ", " << registerToStr(command.reg2Idx) << ", " << registerToStr(command.reg3Idx);
}

std::ostream &operator<<(std::ostream &os, CommandV command) {
    return os << commandToStr(command.command) << " " << int(command.value);
}

std::ostream &operator<<(std::ostream &os, CommandRV command) {
    return os << commandToStr(command.command) << " " << registerToStr(command.regIdx) << ", " << int(command.value);
}

std::ostream &operator<<(std::ostream &os, CommandVU command) {
    return os << commandToStr(command.command) << " " << int(command.vValue) << ", " << int(command.uValue);
}

std::ostream &operator<<(std::ostream &os, CommandRRUU command) {
    return os << commandToStr(command.command) << " " << registerToStr(command.reg1Idx) << ", " << registerToStr(command.reg2Idx) << ", " << int(command.u1Value) << ", " << int(command.u2Value);
}