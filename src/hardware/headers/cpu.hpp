#ifndef _CPU_HPP
#define _CPU_HPP

#include "../../components/headers/process.hpp"
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

class Cpu
{
    public:
    vector <Process> process;
    int coreQT;

    Cpu(int coreQT);
    void showInfo();
    bool put(Process proc);
    bool del(Process proc);
};

#endif