#ifndef _MEMORY_HPP
#define _MEMORY_HPP

#include <iostream>
#include "../../components/headers/process.hpp"
#include <vector>
#include <thread>
#include <unistd.h>

using namespace std;



class Memory
{
    public:
        vector<Process> memory;
        vector<int> memoryStatus;       // 0 Memória livre, -1 Memoria utilizada, [1, size] Segmentos de memoria livre
        vector<int>     memoryFree;     // Segmento de memória livre
        int size;

        Memory(int size);
        void showInfo();
        bool put(Process process);
        bool del(Process process);
        bool isAvaible(int* index, int memoryRequest);
        void reorganize();
        void updateStatus();
};

#endif