#include "scheduler.hpp"

//-----------------------------CONSTRUCTORs------------------------------------
Scheduler::Scheduler(){
    
    FileJson processFile = FileJson("config/process.json");
    Json process = processFile.getJsonFile();
    //int id, int cycles, int maxQuantum, int timeStamp, int priority, string initType,
    for(long unsigned int i=0; i<process.size(); i++){
        try{
            processReady.push_back(
                Process(
                (int)process[i]["processo"], 
                (int)process[i]["ciclos"],
                (int)process[i]["max_quantum"],
                (int)process[i]["timestamp"],
                (int)process[i]["prioridade"],
                (std::string)process[i]["init_type"])
            );
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }        
    }
}

//-----------------------------FUNCTIONs------------------------------------
void Scheduler::init(){
    while(!processReady.empty() && !processBlocked.empty()){
        policy();
        submission();
    }
}
void Scheduler::policy(){}
void Scheduler::submission(){}
void Scheduler::showProcess(){
    if(!processReady.empty()){
        cout<<"********************************** Lista de Processos - (Status: Pronto) *******************************"<<endl;
        Process().printHead();
        for (long unsigned int i = 0; i < processReady.size(); i++)
        {
            processReady[i].print();
        }
        Process().printFooter();
    }
    if(!processBlocked.empty()){
        cout<<"******************************** Lista de Processos - (Status: Bloqueado) ******************************"<<endl;
        Process().printHead();
        for (long unsigned int i = 0; i < processBlocked.size(); i++)
        {
            processBlocked[i].print();
        }
        Process().printFooter();
    }
}