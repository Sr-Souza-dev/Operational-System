#include "scheduler.hpp"

//-----------------------------CONSTRUCTORs------------------------------------
Scheduler::Scheduler(Kernel *kernel){
    this->kernel = kernel;



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
    while(!processReady.empty() || !processBlocked.empty()){
        policy("fifo");
        submission();
        luckType();
        usleep(1000000 * 0.5);
        showProcess();
    }
}


//Politicas de tratamento dos processos
void Scheduler::policy(string type){
    if(type == "fifo"){
        // A ideia de FIFO já é implementada como forma padrão do escalonador 
        
    }
}


//Processos de submissão 
void Scheduler::submission(){
    for (long unsigned int i=0; i<processReady.size(); i++)
    {
        if(processReady[i].initType=="cpu-bound"){
            cpuBound(i);
        }else if(processReady[i].initType=="io-bound"){
            i = i - ioBound(i);
        }else if(processReady[i].initType=="memory-bound"){
            i = i - memoryBound(i);
        }
    }
}

void Scheduler::cpuBound(int index){
    Process process_aux = processReady[index];
    kernel->cpu->processRegister(process_aux);
    decrementQuantum(index);
    //TODO IMPLEMENTAR A REMOÇÃO DE PROCESSOS DA CPU
}

int Scheduler::memoryBound(int index){
    if(processReady[index].associated == true){
        decrementQuantum(index);
        return 0;
    } else{
        blockedInsert(index);
        return 1;
    }
}

int Scheduler::ioBound(int index){
    if(processReady[index].associated == true){
        decrementQuantum(index);
        return 0;
    } else{
        blockedInsert(index);
        return 1;
    }
}

void Scheduler::decrementQuantum(int index){
    int quantum = luckNumber(processReady[index].maxQuantum);
    for(int i=0; i < quantum; i++){
        if(processReady[index].currentQuantum <= 0){
            if(processReady[index].initType=="memory-bound"){
                if(!kernel->memory->del(processReady[index])){
                    cout<< "[ERRO] - A remoção do processo ("<<processReady[index].id<<") na memória falhou"<<endl;
                }
            }else if(processReady[index].initType=="io-bound"){
                //TODO IMPLEMENTAR A REMOÇÃO DE ITENS DO DISCO
            }
            break;
        }
        processReady[index].currentQuantum--;
        blockedUpdate();
        usleep(1000000 * 0.5);
    }
}

void Scheduler::blockedInsert(int index){
    processReady[index].penalty = luckNumber(4);
    processBlocked.push_back(processReady[index]);
    processReady.erase(processReady.begin()+index);
}

void Scheduler::blockedUpdate(){
    for (long unsigned int i=0; i<processBlocked.size(); i++){
        processBlocked[i].penalty--;
        if(processBlocked[i].penalty <= 0){
            processReady.push_back(processBlocked[i]);
            if(processBlocked[i].initType=="memory-bound"){
                if(kernel->memory->put(processBlocked[i])){
                    processBlocked[i].associated = true;
                } else processBlocked[i].associated = false;
                
            } else if(processReady[i].initType=="io-bound"){
                //TODO IMPLEMENTAR A INSERÇÃO DE ITENS NO DISCO
            }
            processBlocked.erase(processBlocked.begin()+i);
            i--;
        }
    }
}

int Scheduler::luckNumber(int maxValue){
    //srand(42);
    return rand()%(maxValue) + 1;   
}

void Scheduler::luckType(){
    int var = rand()%(3) + 1;
    for (long unsigned int i=0; i<processReady.size(); i++)
    {
       if(processReady[i].currentQuantum <= 0){
            var = rand()%(3) + 1;
            if(var == 1){
                processReady[i].initType = "cpu-bound";
            }else if(var == 2){
                processReady[i].initType = "io-bound";
            }else if(var == 3){
                processReady[i].initType = "memory-bound";
            } else{
                processReady[i].initType = var%2 == 0 ? "cpu-bound" : "io-bound";
            }
            processReady[i].cycles--;
            processReady[i].currentQuantum = processReady[i].maxQuantum;
       }
    }
}

void Scheduler::increment(){
    for(long unsigned int i=0; i<processReady.size(); i++){
        processReady[i].timeStamp++;
    }
    for(long unsigned int i=0; i<processBlocked.size(); i++){
        processBlocked[i].timeStamp++;
    }
}



//Imprime os processos bloqueados e prontos
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

void Scheduler::makeHistoric()
{
    Json aux;
    Json principal;
    for(long unsigned int i = 0; i < processFinish.size(); i++){
        aux["processo"] = processFinish[i].id;
        aux["ciclos"] = processFinish[i].cycles;
        aux["timestamp"] = processFinish[i].timeStamp;
        aux["prioridade"] = processFinish[i].priority;

        principal.push_back(aux);
    }
    
      std::ofstream o("historic.json");
      o<<std::setw(4)<< principal <<endl;
}

        

    

