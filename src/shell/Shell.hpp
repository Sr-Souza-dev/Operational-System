#ifndef _SHELL_HPP
#define _SHELL_HPP

#include <iostream>
using namespace std;

#include "../cpu/Cpu.hpp"
#include "../disc/Disc.hpp"
#include "../memory/Memory.hpp"

#define userNameLenght 20


class Shell
{
    private:
        string userName;

    public:
        Shell(string user);
        void openShell(Memory memo, Disc disc, Cpu cpu);
        void showHelp();
};


#endif