#ifndef _MEMORY_HPP
#define _MEMORY_HPP

#include <iostream>
#include "../../components/headers/process.hpp"
#include "../../../lib/hash.hpp"

using namespace std;



class Memory
{
    public:
        HashTable<int, Process> *hash_table;
        int size;

        Memory(int size);
        void showInfo();
};

#endif