#ifndef _CPU_HPP
#define _CPU_HPP

#include "../../components/headers/process.hpp"
#include <iostream>
#include <list>

using namespace std;

class Cpu
{
    public:
    list<Process> process;
    int coreQT;

    Cpu(int coreQT);
    void showInfo();
};

#endif