#ifndef __SCHEDULER_HPP
#define __SCHEDULER_HPP
#include "../../hardware/headers/cpu.hpp"
#include "../../components/headers/process.hpp"
#include "../../components/headers/file.hpp"
#include "../kernel.hpp"
#include <string>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

using json = nlohmann::json;
using namespace std;

class Scheduler{
    public:
        //Variables
        vector<Process> processReady;           // Vetor de processos prontos para serem executados
        vector<Process> processBlocked;         // Vetor de processos que estão aguardando recursos
        vector<Process> processFinish;          // Vetor de processos finalizados 
        Kernel *kernel;                         // Hardware virtual simulado

        //Constructor
        Scheduler(Kernel *kernel);

        //Functions
        void init();                            // Inicializa os processos 
        void policy(string type);               // Aplica uma politica de ordenação do vetor processReady

        void submission();                      // Encaminha os processos para as devidas estruturas físicas
        void cpuBound(int index);               // Trata processos que gastam muito hardware de processador
        int ioBound(int index);                 // Trata processos que gastam muito hardware de disco
        int memoryBound(int index);             // Trata processos que gastam muito hardware de memoria primaria
        void increment();                       // Incremento nos timeStamp
        int luckNumber(int maxValue);           // Sorteia um valor de 1 - maxValue
        void luckType();                        // Sortei os novos custos para cada processo
        void decrementQuantum(int index);       // Reduz o quantum implementando todos decrescimos de tempo
        void blockedUpdate();                   // Atualiza o vetor de processos bloqueados
        void blockedInsert(int index);          // Insere um processo no vetor de bloqueados

        void showProcess();                     // Visualiza Informações das listas de processos Bloqueados e Prontos
        void makeHistoric();                    // Emite um histórico dos processos ao longo da execução
        
        
};

#endif