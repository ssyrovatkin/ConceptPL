#include "Registers.h"

std::string registerToStr(uint8_t reg) {
    if (reg == Registers::SP) {
        return "sp";
    } else if (reg == Registers::FLG) {
        return "flg";
    } else if (reg == Registers::LR) {
        return "x30";
    } else if (reg == Registers::PC) {
        return "pc";
    } else {
        return "x" + std::to_string(int(reg));
    }
}