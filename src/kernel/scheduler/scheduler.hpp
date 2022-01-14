#ifndef __SCHEDULER_HPP
#define __SCHEDULER_HPP

#include "../../components/headers/process.hpp"
#include "../../components/headers/file.hpp"
#include <string>
#include <queue>
#include <iostream>

using namespace std;

class Scheduler{
    public:
        queue<Process> processQueue;

        Scheduler();
        void showQueue();
};

#endif