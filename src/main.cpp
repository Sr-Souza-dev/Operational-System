#include "components/headers/file.hpp"
#include "kernel/kernel.hpp"
#include "shell/shell.hpp"

int main(){

    //Define o diretório do arquivo e faz a leitura do json (config Iniciais)
    FileJson hardware = FileJson("config/hardware.json");
    Json hardwareConfig = hardware.getJsonFile();

    //Define o kernel de acordo com as conf Iniciais 
    Kernel kernel = Kernel(hardwareConfig["cpu"], hardwareConfig["disc"], hardwareConfig["memory"]);

    Shell shell = Shell(&kernel);
    shell.openShell();
    
    return 0;
}