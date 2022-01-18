#include "kernel/scheduler/scheduler.hpp"
#include "components/headers/file.hpp"
#include "kernel/kernel.hpp"
#include "shell/shell.hpp"


void initScheduler(Scheduler *scheduler){
    scheduler->init();
}

int main(){
    //Define o kernel de acordo com as conf Iniciais 
    Kernel kernel = Kernel();

    //Define e inicializa o escalonador
    Scheduler scheduler = Scheduler(&kernel);

    //Define e inicializa as diretrizes do shell
    Shell shell = Shell(&kernel, &scheduler);
    
    shell.openShell();

    scheduler.makeHistoric();

    
    return 0;
}