#ifndef _SHELL_HPP
#define _SHELL_HPP

#include "../kernel/kernel.hpp"
#include "../kernel/scheduler/scheduler.hpp"
#include "../components/headers/file.hpp"
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <thread>
using namespace std;
#define userNameLenght 20


class Shell
{
    public:
        string userName;
        string directory;
        Kernel* kernel;
        Scheduler* scheduler;
        Json helps;
        Shell(Kernel* kernel, Scheduler* scheduler);
        
        string getUserName();

        void openShell();
        void showHelp();
        void loadHelps();
        void htop();
        int kbhit(void);
        void pressAnyKey(int aux);
};


#endif