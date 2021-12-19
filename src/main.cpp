#include <unistd.h>

using namespace std;
#include "shell/Shell.hpp"


//Recupera o nome do usuário logado na máquina
string getUserName(){
    char uName[userNameLenght];
    int result = getlogin_r(uName, userNameLenght);
        
    if(result != 0){
        return "user";
    } else{
        return uName;
    }
}


int main()
{
    //Definindo Instâncias do sistema
    string  userName    = getUserName();
    
    Shell   shell       = Shell(userName);
    Memory  memo        = Memory();
    Disc    disc        = Disc();
    Cpu     cpu         = Cpu();


    //Abrindo o shell
    shell.openShell(memo, disc, cpu);

    return 0;
}
