#ifndef _SHELL_HPP
#define _SHELL_HPP

#include "../kernel/kernel.hpp"
#include "../kernel/scheduler/scheduler.hpp"
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
        Scheduler* scheduler;
        Json helps;

    public:
        Shell(Kernel* kernel, Scheduler* scheduler);
        
        string getUserName();

        void openShell();
        void rebaseShell();
        void showHelp();
        void loadHelps();
        void htop();
};


#endif