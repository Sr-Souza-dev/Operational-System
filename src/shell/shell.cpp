#include "shell.hpp"


//-------------------- Constructor and Destructor ----------------
Shell::Shell(Kernel *kernel)
{
    this->userName  = getUserName();
    this->kernel    = kernel;
    this->directory = "Home";

    loadHelps();
}

//-------------------------- Functions ---------------------------
//Recupera o nome do usuario 
string Shell::getUserName(){
    char uName[userNameLenght];
    int result = getlogin_r(uName, userNameLenght);
        
    if(result != 0){
        return "user";
    } else{
        return uName;
    }
}

// Recupera lista de comando help
void Shell::loadHelps(){
    FileJson help = FileJson("config/helps.json");
    this -> helps = help.getJsonFile();
}


//Abre o shell para receber comandos
void Shell::openShell(){
    
    showHelp();
    string cmd;
    do{
        cout<<this->userName<<":~/"<<directory<<": ";
        getline(cin,cmd);

        if(     cmd == ((string)helps["help"][0]["command"]))   {kernel->cpu->showInfo();}
        else if(cmd == ((string)helps["help"][1]["command"]))   {kernel->memory->showInfo();}
        else if(cmd == ((string)helps["help"][2]["command"]))   {kernel->disc->showInfo();}
        else if(cmd == ((string)helps["help"][3]["command"]))   {showHelp();}
        else if(cmd == ((string)helps["help"][4]["command"]))   {}
        else{
            cout<<"  Comando inválido (<help> para mais informações!)"<<endl;
        }

    } while (cmd != "exit");
}

//Exibe um menu de informações com todos comandos possíveis
void Shell::showHelp(){
    cout<<"\n-------------------------- Comandos disponíveis ("<<directory<<") ------------------------------"<<endl;
    if(!helps.empty()){
        for(long unsigned int i = 0; i< helps["help"].size(); i++){
            printf("  - %-15s    =>   | %s |\n", ((string)helps["help"][i]["command"]).c_str(), ((string)helps["help"][i]["description"]).c_str());
        }
    } else{
        cout<< "[ERRO] - Falha ao carregar comandos"<<endl;
        loadHelps();
    }
    cout<<endl;    
}