#include "scheduler.hpp"

//-----------------------------CONSTRUCTORs------------------------------------
Scheduler::Scheduler(Kernel *kernel){
    this->kernel = kernel;
}

void Scheduler::load(){
   
    FileJson processFile = FileJson("config/process.json");
    Json process = processFile.getJsonFile();
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
    init();
}
//-----------------------------FUNCTIONs------------------------------------
void Scheduler::init(){
    while(!processReady.empty() || !processBlocked.empty()){
        policy("fifo");
        submission();
        luckType();
        usleep(1000000 * sleepTime);
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
    while (!processReady.empty())
    {  
       
        if(processReady.front().initType=="cpu-bound"){
            cpuBound(processReady.front());
            processReady.erase(processReady.begin());

        }else if(processReady.front().initType=="io-bound"){
            ioBound(processReady.front());
            processReady.erase(processReady.begin());

        }else if(processReady.front().initType=="memory-bound"){
            memoryBound(processReady.front());
            processReady.erase(processReady.begin());
        }
    }
    if(processReady.empty() && !processBlocked.empty()){
        increment();
        blockedUpdate();
    }
}

void Scheduler::cpuBound(Process process){
    kernel->cpu->put(process);
    decrementQuantum(process);
}

void Scheduler::memoryBound(Process process){
    if(process.associated == true){
        decrementQuantum(process);
    } else{
        blockedInsert(process);
    }
}

void Scheduler::ioBound(Process process){
    if(process.associated == true){
        decrementQuantum(process);
    } else{
        blockedInsert(process);
    }
}

void Scheduler::decrementQuantum(Process process){

    int quantum = luckNumber(process.maxQuantum);

    for(int i=0; i < quantum; i++){

        process.currentQuantum--;
        process.timeStamp++;

        increment();
        blockedUpdate();

        if(process.currentQuantum <= 0){
            if(process.initType=="memory-bound"){
                if(!kernel->memory->del(process)){
                    cout<< "[ERRO] - A remoção do processo ("<<process.id<<") na memória falhou"<<endl;
                }
            }else if(process.initType=="io-bound"){
                
                if(!kernel->disc->del(to_string(process.id))){
                    cout<< "[ERRO] - A remoção do processo ("<<process.id<<") no disco falhou"<<endl;
                }
            } 
            break;
        }
    }

    if(process.initType=="cpu-bound"){
        if(!kernel->cpu->del(process)){
            cout<< "[ERRO] - A remoção do processo ("<<process.id<<") na cpu falhou"<<endl;
        }
    }
    processes.push_back(process);     
}

Data Scheduler::createData(Process process){
    return Data(
        to_string(process.id), 
        "."+process.initType.substr(0,4), 
        to_string(process.maxQuantum*process.cycles)
    );
}

void Scheduler::blockedInsert(Process process){
    process.penalty = luckNumber(4);
    processBlocked.push_back(process);
}

void Scheduler::blockedUpdate(){
    for (long unsigned int i=0; i<processBlocked.size(); i++){
        processBlocked[i].penalty--;
        if(processBlocked[i].penalty <= 0){
            if(processBlocked[i].initType=="memory-bound"){
                processBlocked[i].associated = kernel->memory->put(processBlocked[i]);
                
            } else if(processReady[i].initType=="io-bound"){
                processBlocked[i].associated = kernel->disc->put(createData(processBlocked[i]));
            }
            processes.push_back(processBlocked[i]);
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
    int var;
    while (!processes.empty())
    {
        if(processes.front().currentQuantum <= 0){
            var = luckNumber(3);

            processes.front().cycles--;
            processes.front().associated = false;
            processes.front().currentQuantum = processes.front().maxQuantum;

            if(processes.front().cycles <= 0){
                processFinish.push_back(processes.front());
            }

            if(var == 1){
                processes.front().initType = "cpu-bound";
                processes.front().historic.push_back(1);

            }else if(var == 2){
                processes.front().initType = "io-bound";
                processes.front().historic.push_back(2);

            }else if(var == 3){
                processes.front().initType = "memory-bound";
                processes.front().historic.push_back(3);
            } else printf("[ERRO] - tipo não definido para o valor sorteado");
        }
        if(processes.front().cycles > 0){
            processReady.push_back(processes.front());
        }  
        processes.erase(processes.begin());
    }
}

void Scheduler::increment(){
    for(long unsigned int i=0; i<processReady.size(); i++){
        processReady[i].timeStamp++;
    }
    for(long unsigned int i=0; i<processBlocked.size(); i++){
        processBlocked[i].timeStamp++;
    }
    for(long unsigned int i=0; i<processes.size(); i++){
        processes[i].timeStamp++;
    }
}


//Imprime os processos bloqueados e prontos
void Scheduler::showProcess(){
    cout<<"\n\n";
    if(!processReady.empty()){
        cout<<"********************************** Lista de Processos - (Status: Pronto) *******************************"<<endl;
        Process().printHead();
        for (long unsigned int i = 0; i < processReady.size(); i++)
        {
            processReady[i].print();
        }
        Process().printFooter();
        if(!processBlocked.empty() || !processFinish.empty()){
            cout<<"////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;
        }
    }
    if(!processBlocked.empty()){
        cout<<"******************************** Lista de Processos - (Status: Bloqueado) ******************************"<<endl;
        Process().printHead();
        for (long unsigned int i = 0; i < processBlocked.size(); i++)
        {
            processBlocked[i].print();
        }
        Process().printFooter();
        if(!processFinish.empty()){
            cout<<"////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;
        }
    }
    if(!processFinish.empty()){
        cout<<"******************************* Lista de Processos - (Status: Finalizados) *****************************"<<endl;
        Process().printHead();
        for (long unsigned int i = 0; i < processFinish.size(); i++)
        {
            processFinish[i].print();
        }
        Process().printFooter();
    }
    if(processFinish.empty() && processBlocked.empty() && processReady.empty()){
        cout<<"   Não há processos em execução"<<endl;
    }
    cout<<"\n\n";
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
        aux["historico"] = processFinish[i].historic;

        principal.push_back(aux);
    }
    
      std::ofstream o("historic.json");
      o<<std::setw(4)<< principal <<endl;
}

        

    

