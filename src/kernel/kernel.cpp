#include "kernel.hpp"

Kernel::Kernel(){
    
    FileJson hardware = FileJson("config/hardware.json");
    Json hardwareConfig = hardware.getJsonFile();

    cpu  = new Cpu(hardwareConfig["cpu"]);
    disc = new Disc(hardwareConfig["disc"]);
    memory = new Memory(hardwareConfig["memory"]);
}