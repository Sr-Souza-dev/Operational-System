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
        int qtdFree = memoryStatus[index];
        for(int i = index; i < index+process.memoryRequest; i++){
            memory[i] = process;
            memoryStatus[i] = -1;
        }

        if(memory[index+process.memoryRequest].id == 0 && index+process.memoryRequest < size){
            memoryStatus[index+process.memoryRequest] = qtdFree - process.memoryRequest;
        }
        for(long unsigned int i = 0; i<memoryFree.size(); i++){
            if(memoryFree[i] == qtdFree){
                if(qtdFree - process.memoryRequest > 0){
                    memoryFree[i] = qtdFree - process.memoryRequest;
                }else{
                    memoryFree.erase(memoryFree.begin() + i);
                }
                break;
            }
        }

        return true;
    }
    return false;
}
bool Memory::del(Process process){

    Process processDefault = Process(0, 0, 0, 0, 0, "");
    bool okay = false;
    int cont = 0;

    for(long unsigned int i=0; i<memory.size() ;i++){
        if(memory[i].id == process.id){

            memory[i] = processDefault;
            memoryStatus[i] = 0;
            cont++;
        }
        if(cont == process.memoryRequest){
            okay = true;
            cont = i+1;
            break;
        }    
    }

    if(okay){
        if(cont < size && memory[cont].id == 0){
            for(long unsigned int j=0; j<memoryFree.size() ;j++){
                if(memoryFree[j] == memoryStatus[cont]){
                    memoryFree[j] += process.memoryRequest;
                    break;
                }
            }
            memoryStatus[cont - process.memoryRequest] = process.memoryRequest + memoryStatus[cont];
            memoryStatus[cont] = 0;
        } else{
            memoryStatus[cont - process.memoryRequest] = process.memoryRequest;

            memoryFree.clear();
            for(int value : memoryStatus){
                if(value > 0){
                    memoryFree.push_back(value);
                }
            }
        }
        if(cont - process.memoryRequest > 0){
            if(memory[cont - process.memoryRequest -1].id == 0){
                for(int j = cont - process.memoryRequest -1; j>=0; j--){
                    if(memory[j].id != 0){
                        memoryStatus[j+1] += memoryStatus[cont - process.memoryRequest];
                        memoryStatus[cont - process.memoryRequest] = 0;
                        


                        memoryFree.clear();
                        for(int value : memoryStatus){
                            if(value > 0){
                                memoryFree.push_back(value);
                            }
                        }
                        break;
                    }
                }
            }
        }
        return true; 
    }

    return false;
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
    cout<<"\n Verificando informações da Memoria"<<endl;
    Process().printHead(1);
    int used = 0;
    for(long unsigned int i =0; i < memory.size(); i++){
        memory[i].print(1);
        if(memory[i].id != 0){
            used++;
        }
    }
    Process().printFooter(1);

    cout<<"Total de Memória RAM:    "<<memory.size()<<endl;
    cout<<"Memória RAM Utilizada:   "<<used<<endl;
    cout<<"Memória RAM Disponível:  "<<memory.size() - used<<endl;

    cout<<"Status: ";
    for(int value : memoryStatus){
        cout<<"*["<<value<<"]";
    }
    cout<<endl;

    cout<<"Free: ";
    for(int value : memoryFree){
        cout<<"*["<<value<<"]";
    }
    cout<<endl;
}
