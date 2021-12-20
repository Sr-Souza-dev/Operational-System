#include "Cpu.hpp"
using namespace std;

void Cpu::showInfo(){
    cout<<"\n Verificando informações do CPU"<<endl;
    for(int i=0; i<4; i++)
    {
        cout<<"core  "<< i+1 <<"processo: "<< cores[i] <<endl;
    }
}