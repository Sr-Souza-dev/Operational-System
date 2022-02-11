#ifndef __SCHEDULER_HPP
#define __SCHEDULER_HPP
#include "../../hardware/headers/cpu.hpp"
#include "../../components/headers/process.hpp"
#include "../../components/headers/file.hpp"
#include "../kernel.hpp"
#include <unistd.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

#define sleepTime 1

using json = nlohmann::json;
using namespace std;

class Scheduler{
    public:
        //Variables
        vector<Process> processes;              // Lista de processos que já executaram sua parcela no ciclo
        vector<Process> processReady;           // Vetor de processos prontos para serem executados
        vector<Process> processBlocked;         // Vetor de processos que estão aguardando recursos
        vector<Process> processFinish;          // Vetor de processos finalizados 
        vector<Process> processesAux; 
        vector<Process> processZombie;          // Processos que não conseguiram executar em 4 ciclos
        vector<int> tickets;
        Kernel *kernel;                         // Hardware virtual simulado

        //Constructor
        Scheduler(Kernel *kernel);

        //Functions
        void init();                            // Inicializa os processos 
        void policy(string type);               // Aplica uma politica de ordenação do vetor processReady

        void submission();                      // Encaminha os processos para as devidas estruturas físicas
        void cpuBound(Process process);         // Trata processos que gastam muito hardware de processador
        void ioBound(Process process);          // Trata processos que gastam muito hardware de disco
        void memoryBound(Process process);      // Trata processos que gastam muito hardware de memoria primaria
        void increment();                       // Incremento nos timeStamp
        int luckNumber(int maxValue);           // Sorteia um valor de 1 - maxValue
        void luckType();                        // Sortei os novos custos para cada processo
        void decrementQuantum(Process process); // Reduz o quantum implementando todos decrescimos de tempo
        void blockedUpdate();                   // Atualiza o vetor de processos bloqueados
        void blockedInsert(Process process);    // Insere um processo no vetor de bloqueados
        Data createData(Process process);       // Cria um tipo Data a partir de um processo
        void LRU();
        void multipleQueues();
        void removeProcessTicket(int id);
        
        void showProcess();                     // Visualiza Informações das listas de processos Bloqueados e Prontos
        void makeHistoric();                    // Emite um histórico dos processos ao longo da execução
        void load();                            // Recebe os processos do arquivo json e carrega os mesmos para lista de pronto
        
};

#endif