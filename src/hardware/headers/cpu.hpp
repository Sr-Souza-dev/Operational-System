#ifndef _CPU_HPP
#define _CPU_HPP

#include "../../components/headers/process.hpp"
#include <iostream>
#include <list>
#include <thread>

using namespace std;

class Cpu
{
    public:
    list<Process> process;
    int coreQT;

    Cpu(int coreQT);
    void processRegister(Process process_ToRegister);
    void showInfo();
};

#endif