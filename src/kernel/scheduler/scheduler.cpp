#include "scheduler.hpp"

Scheduler::Scheduler(){
    
    FileJson processFile = FileJson("config/process.json");
    Json process = processFile.getJsonFile();
    //int id, int cycles, int maxQuantum, int timeStamp, int priority, string initType,
    for(long unsigned int i=0; i<process.size(); i++){
        processQueue.push(
            Process(
                (int)process[i]["processo"], 
                (int)process[i]["ciclos"],
                (int)process[i]["max_quantum"],
                (int)process[i]["time_stamp"],
                (int)process[i]["prioridade"],
                (std::string)process[i]["init_type"])
            );
    }
}