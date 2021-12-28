#include "headers/process.hpp"

//Constructor
Process::Process(string name, string hour, string id, string description, int core){
    this -> description = description;
    this -> name = name;
    this -> hour = hour;
    this -> id   = id;
    this -> core = core;
}

//Functions
void Process::printHead(int opt){
    if(opt == 0){
        cout<< "\n---------------------------------------------------------------"<<endl;
        printf(" + CORE |    ID    |     NAME     |  HOUR  |   DESCRIPTION   +\n");
        cout<< "---------------------------------------------------------------"<<endl;
    } else if(opt == 1){
        cout<< "\n----------------------------------------------------------"<<endl;
        printf(" +    ID    |     NAME     |  HOUR  |   DESCRIPTION   +\n");
        cout<< "----------------------------------------------------------"<<endl;
    }
    
}
void Process::print(int opt){
    if(opt == 0){
        printf(" +  %i   |  %-6s  |  %-10s  | %-6s | %-15s +\n",core, id.c_str(), name.c_str(), hour.c_str(), description.c_str());
    } else if(opt == 1){
        printf(" +  %-6s  |  %-10s  | %-6s | %-15s +\n", id.c_str(), name.c_str(), hour.c_str(), description.c_str());
    }

}
void Process::printFooter(int opt){
    if(opt == 0){
        cout<< "---------------------------------------------------------------\n"<<endl;
    } else if(opt == 1){
        cout<< "----------------------------------------------------------\n"<<endl;
    }
}