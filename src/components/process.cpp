#include "headers/process.hpp"

//Constructor
Process::Process(int id, int cycles, int maxQuantum, int timeStamp, int priority, string initType, int core, int memoryRequest){
    this -> state = 0;
    this -> id = id;
    this -> cycles = cycles;
    this -> maxQuantum = maxQuantum;
    this -> currentQuantum = maxQuantum;
    this -> timeStamp = timeStamp;
    this -> priority = priority;
    this -> initType = initType;
    this -> core = core;
    this -> associated = false;
    this -> penalty = 0;
    this -> blockedTimes = 0;
    this -> memoryRequest = memoryRequest;
    this -> zombie = 4;
}

//Functions
void Process::printHead(int opt){
    if(opt == 0){
        cout<< "\n------------------------------------------------------------------------------------------------------------------------"<<endl;
        printf(" +  CORE  |    ID    |     CYCLES     |  MAX_QUANTUM  |   TIME_STAMP   |   PRIORITY   |    INIT_TYPE   |  TIMES BLOCKED +\n");
        cout<< "------------------------------------------------------------------------------------------------------------------------"<<endl;
    } else if(opt == 1){
        cout<< "\n--------------------------------------------------------------------------------------------------------"<<endl;
        printf(" + INDEX  |    ID    |     CYCLES     |  MAX_QUANTUM  |   TIME_STAMP   |   PRIORITY   |    INIT_TYPE   +\n");
        cout<< "--------------------------------------------------------------------------------------------------------"<<endl;
    }
}
void Process::print(int opt){
    if(opt == 0){
        printf(" +  %-3i   |  %-6i  |  %-12i  |  %-11i  |  %-12i  |  %-10i  |  %-12s  |  %-12i  +\n", core, id, cycles, maxQuantum, timeStamp, priority, initType.c_str(),blockedTimes);
    } else if(opt == 1){
        printf(" +  %-4i  |  %-6i  |  %-12i  |  %-11i  |  %-12i  |  %-10i  |  %-12s  +\n", core, id, cycles, maxQuantum, timeStamp, priority, initType.c_str());
    }

}
void Process::printFooter(int opt){
    if(opt == 0){
        cout<< "------------------------------------------------------------------------------------------------------------------------\n"<<endl;
    } else if(opt == 1){
        cout<< "---------------------------------------------------------------------------------------------------------\n"<<endl;
    }
}