#ifndef _SHELL_HPP
#define _SHELL_HPP

#include "../kernel/kernel.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;
#define userNameLenght 20


class Shell
{
    private:
        string userName;
        Kernel* kernel;

    public:
        Shell(Kernel* kernel);
        
        string getUserName();

        void openShell();
        void showHelp();
};


#endif