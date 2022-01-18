#include "kernel/scheduler/scheduler.hpp"
#include "components/headers/file.hpp"
#include "kernel/kernel.hpp"
#include "shell/shell.hpp"
#include <thread>


void initScheduler(Scheduler *scheduler){
    scheduler->init();
}
void openShell(Shell *shell){
    shell->openShell();
}
int main(){
    //Define o kernel de acordo com as conf Iniciais 
    Kernel kernel = Kernel();

    //Define e inicializa o escalonador
    Scheduler scheduler = Scheduler(&kernel);

    //Define e inicializa as diretrizes do shell
    Shell shell = Shell(&kernel);
    
    //threads
    thread t_init(initScheduler, &scheduler);
    thread t_shell(openShell,&shell);


    t_init.join();
    //scheduler.init();

    //scheduler.showProcess();
    

    t_shell.join();
    //shell.openShell();

    scheduler.makeHistoric();

    
    return 0;
}