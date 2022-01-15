#ifndef __SCHEDULER_HPP
#define __SCHEDULER_HPP

#include "../../components/headers/process.hpp"
#include "../../components/headers/file.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Scheduler{
    public:
        //Variables
        vector<Process> processReady;           //Vetor de processos prontos para serem executados
        vector<Process> processBlocked;         //Vetor de processos que estão aguardando recursos
        vector<int>     auxProcessBlock;        //Define o quantum faltante para que o processo saia do vetor de bloqueados

        //Constructor
        Scheduler();

        //Functions
        void init();                            //Inicializa os processos 
        void policy();                          //Aplica uma politica de ordenação do vetor processReady
        void submission();                      //Ecaminha os processos para as devidas estruturas físicas
        void showProcess();                     //Visualiza Informações das listas de processos Bloqueados e Prontos
        
        
};

#endif