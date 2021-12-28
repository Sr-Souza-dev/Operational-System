#include "kernel.hpp"

Kernel::Kernel(int coreQT, int discSize, int memorySize){
    cpu  = new Cpu(coreQT);
    disc = new Disc(discSize);
    memory = new Memory(memorySize);
}