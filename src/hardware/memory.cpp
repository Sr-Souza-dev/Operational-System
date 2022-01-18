#include "headers/memory.hpp"

//Constructor
Memory::Memory(int size){
    this->size = size;
    Process proc = Process(0, 0, 0, 0, 0, "");

    for(int i=0; i<size; i++){
        memory.push_back(proc);
    }
}

//Functions
void Memory::showInfo(){
    cout<<"\n Verificando informações da Memoria"<<endl;
    Process().printHead(1);
    int used = 0;
    for(long unsigned int i =0; i < memory.size(); i++){
        memory[i].print();
        if(memory[i].id != 0){
            used++;
        }
    }
    Process().printFooter();

    cout<<"Total de Memória RAM:    "<<memory.size()<<endl;
    cout<<"Memória RAM Utilizada:   "<<used<<endl;
    cout<<"Memória RAM Disponível:  "<<memory.size() - used<<endl;
}

bool Memory::put(Process process){
    for(long unsigned int i=0; i<memory.size() ;i++){
        if(memory[i].id == 0){
            process.core = i;
            memory[i] = process;
            return true;
        }
    }
    return false;
}
bool Memory::del(Process process){
    for(long unsigned int i=0; i<memory.size() ;i++){
        if(memory[i].id == process.id){
            memory[i] = Process(0, 0, 0, 0, 0, "");
            return true;
        }
    }
    return false;
}

