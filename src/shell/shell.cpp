#include "shell.hpp"


//-------------------- Constructor and Destructor ----------------
Shell::Shell(Kernel *kernel, Scheduler* scheduler)
{
    this->userName  = getUserName();
    this->kernel    = kernel;
    this->scheduler = scheduler;
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

int Shell::kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

// Recupera lista de comando help
void Shell::loadHelps(){
    FileJson help = FileJson("config/helps.json");
    this -> helps = help.getJsonFile();
}

void initSchedule(Scheduler *scheduler){
    scheduler->load();
}

//Abre o shell para receber comandos
void Shell::openShell(){
    
    bool loadProcessExecuted = false;

    showHelp();
    string cmd;
    do{
        cout<<this->userName<<":~/"<<directory<<": ";
        getline(cin,cmd);

        if(     cmd == ((string)helps["help"][0]["command"]))   {pressAnyKey(0);}
        else if(cmd == ((string)helps["help"][1]["command"]))   {pressAnyKey(1);}
        else if(cmd == ((string)helps["help"][2]["command"]))   {pressAnyKey(2);}
        else if(cmd == ((string)helps["help"][3]["command"]))   {pressAnyKey(3);} //htop
        else if(cmd == ((string)helps["help"][4]["command"]))   {            
            if(!loadProcessExecuted){
                loadProcessExecuted = true;
                thread t_init(initSchedule, scheduler);
                t_init.detach();
            } else{
                cerr << "[ERRO] - Os processos já foram carregados!" << endl;
            }
        }
        else if(cmd == ((string)helps["help"][5]["command"]))   {showHelp();}
        else if(cmd == ((string)helps["help"][6]["command"]))   {}
        else{
            cout<<"  Comando inválido (<help> para mais informações!)"<<endl;
        }

    } while (cmd != "exit");
}

void Shell::pressAnyKey(int aux){
    while(!kbhit()){
        usleep(1000000 * sleepTime * 0.1);
        system("clt||clear");
        cout<<"  ************ Pressione Qualquer Tecla para sair do modo de visualização! ************ "<<endl;
        switch(aux){
            case 0:
                kernel->cpu->showInfo();
            break;
            case 1:
                kernel->memory->showInfo();
            break;
            case 2:
                kernel->disc->showInfo();
            break;
            case 3:
                scheduler->showProcess();  
            break;
        }
        cout<<"\n  ************ Pressione Qualquer Tecla para sair do modo de visualização! ************ "<<endl;
    }
    getchar();
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
    