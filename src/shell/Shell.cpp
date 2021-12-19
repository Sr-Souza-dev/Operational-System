#include "Shell.hpp"
using namespace std;


//-------------------- Constructor and Destructor ----------------
Shell::Shell(string user)
{
    this->userName = user;
    
}

//-------------------------- Functions ---------------------------
//Abre o shell para receber comandos
void Shell::openShell(Memory memo, Disc disc, Cpu cpu){

    showHelp();
    string cmd;
    do{
        cout<<this->userName<<"(shell):~ ";
        getline(cin,cmd);

        if(     cmd == "cpuInf" ){cpu.showInfo();}
        else if(cmd == "memoInf"){memo.showInfo();}
        else if(cmd == "discInf"){disc.showInfo();}
        else if(cmd == "help"   ){showHelp();}
        else if(cmd == "exit"   ){}
        else{
            cout<<"  Comando não inválido (<help> para mais informações!)"<<endl;
        }

    } while (cmd != "exit");
}

//Exibe um menu de informações com todos comandos possíveis
void Shell::showHelp(){
    cout<<"\n........ Você está na shell com poderes do usuário: "<<this->userName<<" ........."<<endl;
    cout<<"-------------- Segue abaixo os comandos disponíveis ------------------\n"<<endl;
    cout<<" <cpuInf>     para verificar informações do processador"<<endl;
    cout<<" <memoInf>    para verificar informações da memória"<<endl;
    cout<<" <discInf>    para verificar informações de armazenamento"<<endl;
    cout<<" <help>       para exibir este menu de opções"<<endl;
    cout<<" <exit>       para finalizar o shell"<<endl;
    cout<<"----------------------------------------------------------------------\n"<<endl;
}