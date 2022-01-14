#include "components/headers/file.hpp"
#include "kernel/kernel.hpp"
#include "shell/shell.hpp"

int main(){

    //Define o kernel de acordo com as conf Iniciais 
    Kernel kernel = Kernel();

    Shell shell = Shell(&kernel);
    shell.openShell();
    
    return 0;
}