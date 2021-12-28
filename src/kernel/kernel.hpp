#ifndef _KERNEL_HPP
#define _KERNEL_HPP

#include "../hardware/headers/cpu.hpp"
#include "../hardware/headers/disc.hpp"
#include "../hardware/headers/memory.hpp"

#include <iostream>
using namespace std;

class Kernel{
    public:
    Cpu *cpu;
    Disc *disc;
    Memory *memory;

    Kernel(int coreQT, int discSize, int memorySize);

};

#endif