#ifndef _CORE_HPP
#define _CORE_HPP
#include <iostream>
using namespace std;

class Core{
    
    private:
    string process_name;
    string process_hour;
    string process_id;


    public:
    //Constructors

    Core();
    Core(string process_name, string process_hour, string process_id);
    //Setters e Getters
    void setProcessName(string process_name);
    string getProcessName();

    void setProcessHour(string process_hour);
    string getProcessHour();

    void setProcessId(string process_id);
    string getProcessId();


    
};
#endif