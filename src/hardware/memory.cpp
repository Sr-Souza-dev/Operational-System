#include "headers/memory.hpp"

//Constructor
Memory::Memory(int size){
    this->size = size;
    hash_table = new HashTable<int, Process>(size);
}

//Functions
void Memory::showInfo(){
    cout<<"\n Verificando informações da Memoria"<<endl;
    hash_table->Print();
}