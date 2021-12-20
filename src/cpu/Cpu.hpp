#ifndef _CPU_HPP
#define _CPU_HPP

#include <iostream>
using namespace std;


class Cpu
{
    private:
    string cores[4];
    

    public:
        Cpu() = default;
        void showInfo();
};

#endif