#include "scheduler.hpp"

Scheduler::Scheduler(){
    
    FileJson processFile = FileJson("config/process.json");
    Json process = processFile.getJsonFile();
    //int id, int cycles, int maxQuantum, int timeStamp, int priority, string initType,

    try
    {
        for(long unsigned int i=0; i<process.size(); i++){
        Process processAux = Process(
                (int)process[i]["processo"], 
                (int)process[i]["ciclos"],
                (int)process[i]["max_quantum"],
                (int)process[i]["timestamp"],
                (int)process[i]["prioridade"],
                (std::string)process[i]["init_type"]);

        processQueue.push(processAux);
    }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
}

void Scheduler::showQueue(){
    
    queue<Process> aux = processQueue;
    while (!aux.empty())
    {
        aux.front().print();
        aux.pop();

    }
}