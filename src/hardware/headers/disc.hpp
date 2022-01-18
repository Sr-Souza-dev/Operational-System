#ifndef _DISC_HPP
#define _DISC_HPP


#include "../../components/headers/data.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <thread>

using namespace std;

class Disc
{
    public:
    vector <Data> disc;
    int size;

    Disc(int size);
    void showInfo();   
    bool put(Data data);
    bool del(string dataName); 
};
#endif