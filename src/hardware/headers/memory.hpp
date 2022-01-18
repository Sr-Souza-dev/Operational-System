#ifndef _MEMORY_HPP
#define _MEMORY_HPP

#include <iostream>
#include "../../components/headers/process.hpp"
#include <vector>
#include <thread>

using namespace std;



class Memory
{
    public:
        vector<Process> memory;
        int size;

        Memory(int size);
        void showInfo();
        bool put(Process process);
        bool del(Process process);
};

#endif