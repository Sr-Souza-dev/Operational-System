#ifndef _DATA_HPP
#define _DATA_HPP

#include <iostream>
#include <string>

using namespace std;


class Data
{
    public:
        string name;
        string type;
        string size;
        string createDate; 

        Data(string name, string type, string size, string createDate);
        void print();
        void printHead();
        void printFooter();
};

#endif