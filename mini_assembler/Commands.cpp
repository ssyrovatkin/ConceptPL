#include "Commands.h"

std::string commandToStr(uint8_t command) {
    if (command == Commands::mov) {
        return "mov";
    } else if (command == Commands::movr) {
        return "movr";
    } else if (command == Commands::sub) {
        return "sub";
    } else if (command == Commands::add) {
        return "add";
    } else if (command == Commands::print) {
        return "print";
    } else if (command == Commands::print_s) {
        return "print_s";
    } else if (command == Commands::print_c) {
        return "print_c";
    } else if (command == Commands::loadstr) {
        return "loadstr";
    } else if (command == Commands::print_r) {
        return "print_r";
    } else if (command == Commands::str) {
        return "str";
    } else if (command == Commands::EXIT) {
        return "EXIT";
    } else if (command == Commands::bLE) {
        return "bLE";
    } else if (command == Commands::bEQ) {
        return "bEQ";
    } else if (command == Commands::b) {
            return "b";
    } else if (command == Commands::bl) {
        return "bl";
    } else if (command == Commands::cmp) {
        return "cmp";
    } else if (command == Commands::inp) {
        return "inp";
    } else if (command == Commands::load) {
        return "load";
    } else if (command == Commands::ret) {
        return "ret";
    }
    return "undefined command";
}

