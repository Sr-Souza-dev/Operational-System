#include "headers/cpu.hpp"

//Constructor
Cpu::Cpu(int coreQT){
    this -> coreQT = coreQT;
    Process proc = Process("noneNa","00:00","noneId","noneDes");

    this -> process.resize(coreQT, proc);
}

//Functions
void Cpu::showInfo(){

    int used = 0;
    process.front().printHead();
    for(Process proc:process){
        proc.print();
        if(proc.core != 0){
            used++;
        }
    }
    process.front().printFooter();

    cout<<"Total Core:      "<<coreQT<<endl;
    cout<<"Core Utilizados: "<<used<<endl;
    cout<<"Core Diponíveis: "<<coreQT - used<<endl;
    cout<<endl;
}