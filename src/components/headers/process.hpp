#ifndef _PROCESS_HPP
#define _PROCESS_HPP
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class Process{
    
    public:
        int id;             // Identificador do processo
        int core;           // Core que está sendo utilizado para processar determinado processo
        int cycles;         // Quantidade de ciclos de cada processo para ser executado completamente
        int maxQuantum;     // Valor de quantum que cada processo precisa para finalizar um ciclo
        int timeStamp;      // Tempo de processamento
        int priority;       // Nivél de prioridade de cada processo (1 - 4)
        int state;          // 0 - Bloqueado; 1 - Execução; 2 - Pronto;
        int penalty;        // Tempo que o processo ficará no estado bloqueado
        int currentQuantum; // Valor de quantum atual do processo durante o ciclo
        int blockedTimes;   // Quantidade de vezes que o processo foi para fila de bloqueados
        int memoryRequest;
        int zombie;         // 
        bool associated;    // False - processos não associados a uma memoria/disco | true - processos associados a uma memoria/disco
        string initType;    // Tipo de recurso que o processo mais utiliza
        vector<int> historic;
        

    //Constructors
    Process(){}
    Process(int id, int cycles, int maxQuantum, int timeStamp, int priority, string initType, int core = 0, int memoryRequest = 0);

    //Functions
    void print(int opt = 0);        // Printa o conteúdo do processo
    void printHead(int opt = 0);    // Printa o escopo da tabela de processo
    void printFooter(int opt = 0);  // Printa o rodapé da tabela
};
#endif