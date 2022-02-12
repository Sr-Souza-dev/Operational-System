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
                (std::string)process[i]["init_type"],
                0,
                luckNumber(13) + 7)
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
    while(!processReady.empty() || !processBlocked.empty() || !processesAux.empty()){
        policy("fifo");
        submission();
        luckType();
        //usleep(1000000 * sleepTime * 0.5);
    }
}


//Politicas de tratamento dos processos
void Scheduler::policy(string type){
    if(type == "fifo"){
        // A ideia de FIFO já é implementada como forma padrão do escalonador 
    } else if(type == "lru"){
        LRU();
    } else if(type == "multipleQueues"){
        multipleQueues();
    }
}

bool sortFunctionGrowing(Process i, Process j){return(i.cycles < j.cycles);}
void Scheduler::LRU(){
    sort(processReady.begin(), processReady.end(), sortFunctionGrowing);
}

//bool sortFunctionDescending(Process i, Process j){return(i.timeStamp < j.timeStamp);}
void Scheduler::multipleQueues(){
    int maxPriority = 0;
   
    if(processReady.empty()){       
        maxPriority = processesAux.front().priority;
        for(Process aux:processesAux){
            if(maxPriority < aux.priority){
                maxPriority = aux.priority;
            }
        }
    } else{
        while(!processReady.empty()){
            if(maxPriority < processReady.front().priority){
                maxPriority = processReady.front().priority;
            }
            processesAux.push_back(processReady.front());
            processReady.erase(processReady.begin());
        }
    }

    if(maxPriority > 0){
        long unsigned int cont = 0;
        while(cont < processesAux.size()){
            if(processesAux[cont].priority >= maxPriority){
                removeProcessTicket(processesAux[cont].id);
                processReady.push_back(processesAux[cont]);
                processesAux.erase(processesAux.begin() + cont);
            } else{
                tickets.push_back(processesAux[cont].id);
                cont++;
            }
        }
    } else{
        int luck = 0;
        long unsigned int j = 0;

        for(int i = 0; i< kernel->cpu->coreQT; i++){
            if(this->tickets.size() != 0){
                luck =  luckNumber(this->tickets.size()) - 1;
            }
            
            j = 0;
            while(j < processesAux.size()){
                if(processesAux[j].id == this->tickets[luck]){
                    removeProcessTicket(processesAux[j].id);
                    processReady.push_back(processesAux[j]);
                    processesAux.erase(processesAux.begin() + j);
                } else{
                    this->tickets.push_back(processesAux[j].id);
                    j++;
                }
            }
        }
    }
}

void Scheduler::removeProcessTicket(int id){
    long unsigned int cont = 0;
    while(cont < tickets.size()){
        if(tickets[cont] == id){
            tickets.erase(tickets.begin()+cont);
        } else{
            cont++;
        }
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
            if(processReady.front().zombie <= 0){
                processZombie.push_back(processReady.front());
            } else{
                memoryBound(processReady.front());
            }  
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

        usleep(1000000 * sleepTime * 0.5); 

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
    process.blockedTimes += process.penalty;
    processBlocked.push_back(process);
}

void Scheduler::blockedUpdate(){
    bool aux = false;
    for (long unsigned int i=0; i<processBlocked.size(); i++){
        processBlocked[i].penalty--;
        if(processBlocked[i].penalty <= 0){
            if(processBlocked[i].initType=="memory-bound"){
                aux = kernel->memory->put(processBlocked[i]);
                processBlocked[i].associated = aux;
                if(!aux){
                   processBlocked[i].zombie--; 
                }
                                
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
            
            if(processes.front().priority > 0){processes.front().priority--;}
            
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
                processes.front().memoryRequest = luckNumber(13) + 7;
                processes.front().historic.push_back(3);
                processes.front().zombie = 4;
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
     for(long unsigned int i=0; i<processesAux.size(); i++){
        processesAux[i].timeStamp++;
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
        if(!processBlocked.empty() || !processFinish.empty() || !processZombie.empty()){
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
        if(!processFinish.empty() || !processZombie.empty()){
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
        if(!processZombie.empty()){
            cout<<"////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;
        }
    }
     if(!processZombie.empty()){
        cout<<"******************************* Lista de Processos - (Status: Zombie) *****************************"<<endl;
        Process().printHead();
        for (long unsigned int i = 0; i < processZombie.size(); i++)
        {
            processZombie[i].print();
        }
        Process().printFooter();
        if(!processZombie.empty()){
            cout<<"////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;
        }
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
    
    std::ofstream o("config/historic.json");
    o<<std::setw(4)<< principal <<endl;
}