#include <iostream>

#include "Assembler.h"
#include "VM.h"


int main() {
    system("chcp 65001");

    //Assembler::assemble("hello-world", "hello-world.bin");
    //Assembler::assemble("fibonacci", "fibonacci.bin");
    //Assembler::assemble("fibonacci-recursive", "fibonacci-recursive.bin");
    Assembler::assemble("printf", "printf.bin");

    auto vm = VM(false);

    //vm.init("hello-world.bin");
    //vm.init("fibonacci.bin");
    //vm.init("fibonacci-recursive.bin");
    vm.init("printf.bin");

    vm.run();

    return 0;
}
