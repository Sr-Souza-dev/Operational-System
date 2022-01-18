#ifndef _DATA_HPP
#define _DATA_HPP

#include <iostream>
#include <string>
#include <time.h>

using namespace std;


class Data
{
    public:
        string name;
        string type;
        string size;
        string createDate; 

        Data(string name, string type, string size);
        Data(){};
        void print();
        void printHead();
        void printFooter();
};

#endif