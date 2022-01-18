#ifndef _SHELL_HPP
#define _SHELL_HPP

#include "../kernel/kernel.hpp"
#include "../components/headers/file.hpp"
#include <iostream>
#include <unistd.h>
#include <thread>
using namespace std;
#define userNameLenght 20


class Shell
{
    private:
        string userName;
        string directory;
        Kernel* kernel;
        Json helps;

    public:
        Shell(Kernel* kernel);
        
        string getUserName();

        void openShell();
        void showHelp();
        void loadHelps();
};


#endif