#include "Core.hpp"

Core::Core(){
}

Core::Core(string process_name, string process_hour, string process_id):process_name(process_name),
process_hour(process_hour),process_id(process_id){}

void Core::setProcessName(string process_name){
    this -> process_name = process_name;
}

string Core::getProcessName()
{
    return process_name;
}

void Core::setProcessHour(string process_hour){
    this -> process_hour = process_hour;
}

string Core::getProcessHour()
{
    return process_hour;
}

void Core::setProcessId(string process_id){
    this -> process_id = process_id;
}

string Core::getProcessId()
{
    return process_id;
}

