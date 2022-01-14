#include "headers/cpu.hpp"

//Constructor
Cpu::Cpu(int coreQT){
    this -> coreQT = coreQT;
    Process proc = Process(0, 0, 0, 0, 0, "");

    for(int i=0; i<coreQT; i++){
        proc.core = i+1;
        this->process.push_back(proc);
    }
}

//Functions
void Cpu::showInfo(){

    int used = 0;
    process.front().printHead();
    for(Process proc:process){
        proc.print();
        if(proc.id != 0){
            used++;
        }
    }
    process.front().printFooter();

    cout<<"Total Core:      "<<coreQT<<endl;
    cout<<"Core Utilizados: "<<used<<endl;
    cout<<"Core Diponíveis: "<<coreQT - used<<endl;
    cout<<endl;
}