#ifndef _DISC_HPP
#define _DISC_HPP


#include "../../components/headers/data.hpp"
#include <iostream>
#include <string>
#include <stack>
#include <thread>

using namespace std;

class Disc
{
    public:
    stack <Data> disc;
    int size;

    Disc(int size);
    void showInfo();    
};
#endif