#ifndef _PROCESS_HPP
#define _PROCESS_HPP
#include <iostream>
#include <string.h>

using namespace std;

class Process{
    
    public:
        int id;
        int core;
        int cycles;
        int maxQuantum;
        int timeStamp;      // tempo de processamento
        int priority;
        int state;          // 0 - Bloqueado; 1 - Execução; 2 - Pronto;
        bool blocked;
        int currentQuantum;
        string initType;

    //Constructors
    Process(){}
    Process(int id, int cycles, int maxQuantum, int timeStamp, int priority, string initType, int core = 0);

    //Functions
    void print(int opt = 0);
    void printHead(int opt = 0);
    void printFooter(int opt = 0);
};
#endif