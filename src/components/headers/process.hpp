#ifndef _PROCESS_HPP
#define _PROCESS_HPP
#include <iostream>
#include <string.h>

using namespace std;

class Process{
    
    public:
    string description;
    string name;
    string hour;
    string id;
    int core;

    //Constructors
    Process(string name, string hour, string id, string description, int core = 0);

    //Functions
    void print(int opt = 0);
    void printHead(int opt = 0);
    void printFooter(int opt = 0);
};
#endif