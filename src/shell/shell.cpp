#include "shell.hpp"


//-------------------- Constructor and Destructor ----------------
Shell::Shell(Kernel *kernel)
{
    this->userName = getUserName();
    this->kernel   = kernel;
    
}

string Shell::getUserName(){
    char uName[userNameLenght];
    int result = getlogin_r(uName, userNameLenght);
        
    if(result != 0){
        return "user";
    } else{
        return uName;
    }
}


//-------------------------- Functions ---------------------------
//Abre o shell para receber comandos
void Shell::openShell(){

    showHelp();
    string cmd;
    do{
        cout<<this->userName<<"(shell):~ ";
        getline(cin,cmd);

        if(     cmd == "cpuInf" ){kernel->cpu->showInfo();}
        else if(cmd == "memoryInf"){kernel->memory->showInfo();}
        else if(cmd == "discInf"){kernel->disc->showInfo();}
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