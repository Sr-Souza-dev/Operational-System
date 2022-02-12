#include "headers/memory.hpp"

//Constructor
Memory::Memory(int size){
    this->size = size;
    Process proc = Process(0, 0, 0, 0, 0, "");

    for(int i=0; i<size; i++){
        memory.push_back(proc);
        memoryStatus.push_back(0);
    }
    memoryStatus[0] = size;
    memoryFree.push_back(size);
}

//Functions
bool Memory::put(Process process){
    int index;
    if(isAvaible(&index, process.memoryRequest)){
        for(int i = index; i < index+process.memoryRequest; i++){
            memory[i] = process;
        }

        updateStatus();
        return true;
    }
    return false;
}

bool Memory::del(Process process){
    Process processDefault = Process(0, 0, 0, 0, 0, "");
    int cont = 0;

    for(long unsigned int i=0; i<memory.size() ;i++){
        if(memory[i].id == process.id){
            memory[i] = processDefault;
            cont++;
        }
        if(cont == process.memoryRequest){
            updateStatus();
            return true;
        }    
    }
    return false;
}

void Memory::updateStatus(){
    int indexAux = -1;
    int contAux = 0;

    memoryFree.clear();

    for(int i=0; i<size; i++){
        if(memory[i].id == 0){

            memoryStatus[i] = 0;
            contAux++;

            if(contAux == 1){
                indexAux = i;
            }
            
            if(indexAux != -1 && i == size-1){
                memoryStatus[indexAux] = contAux;
                memoryFree.push_back(contAux);
                indexAux = -1;
                contAux = 0; 
            }

        } else{
            memoryStatus[i] = -1;
            if(indexAux != -1 && memory[i-1].id == 0){
                memoryStatus[indexAux] = contAux;
                memoryFree.push_back(contAux);
                indexAux = -1;
                contAux = 0; 
            } 
        }
    }
}


bool Memory::isAvaible(int* index, int memoryRequest){
    int sum = 0;
    for(int value : memoryFree){
        if(memoryRequest <= value){
            for(int i=0; i < size; i++){
                if(memoryStatus[i] == value){
                    *index = i;
                    return true;
                }
            }
        }
        sum += value;
    }
    if(memoryRequest <= sum){
        reorganize();
        *index = 0;
        return true;
    }
    return false;
}

void Memory::reorganize(){
    Process processDefault = Process(0, 0, 0, 0, 0, "");
    Process processAux;
    
    int cont = 0;
    for(int i=size-1; i>=0; i--){
        if(memory[i].id == 0){
            cont++;
        } else if(cont != 0){
            memory[i + cont] = memory[i];
            memory[i] = processDefault;

            memoryStatus[i+cont] = -1;
            memoryStatus[i] = 0;
            memoryStatus[i+1] = 0;

        }
    }

    int sum = 0;
    for(int value : memoryFree){
        sum += value;
    }
    memoryFree.clear();
    memoryFree.push_back(sum);
    memoryStatus[0] = sum;
}

void Memory::showInfo(){
    std::cout<<"\n Verificando informações da Memoria"<<endl;
    Process().printHead(1);
    int used = 0;
    int time = 0;
    for(long unsigned int i =0; i < memory.size(); i++){
        memory[i].print(1);
        if(memory[i].id != 0){
            used++;
            time = memory[i].timeStamp;
        }
    }
    Process().printFooter(1);

    std::cout<<"Time:                    "<<time<<endl;
    std::cout<<"Total de Memória RAM:    "<<memory.size()<<endl;
    std::cout<<"Memória RAM Utilizada:   "<<used<<endl;
    std::cout<<"Memória RAM Disponível:  "<<memory.size() - used<<endl;

    std::cout<<"Status: ";
    for(int value : memoryStatus){
        std::cout<<"*["<<value<<"]";
    }
    std::cout<<endl;

    std::cout<<"Free: ";
    for(int value : memoryFree){
        std::cout<<"*["<<value<<"]";
    }
    std::cout<<endl;
}
