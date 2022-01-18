#include "headers/disc.hpp"

//Constructor
Disc::Disc(int size)
{
    this->size = size;
    
    Data data = Data("","","");
    for(int i=0; i < size; i++){
        this->disc.push_back(data);
    } 
}

//Functions
void Disc::showInfo()
{
    int used = 0;
    cout<<"\n Verificando informações do disco"<<endl;
    Data().printHead();
    for(long unsigned int i =0; i < disc.size(); i++){
        disc[i].print();
        if(disc[i].name != ""){
            used++;
        }
    }
    Data().printFooter();
    cout<<"Memória Total (disco):     "<<size<<endl;
    cout<<"Memória Utilizada (disco): "<<used<<endl;
    cout<<"Memória Diponível (disco): "<<size - used<<endl;
    cout<<endl;
}

bool Disc::put(Data data){
    for(long unsigned int i=0; i<disc.size() ;i++){
        if(disc[i].name == ""){
            disc[i] = data;
            return true;
        }
    }
    return false;
}
bool Disc::del(string dataName){
    for(long unsigned int i=0; i<disc.size() ;i++){
        if(disc[i].name == dataName){
            disc[i] = Data("","","");
            return true;
        }
    }
    return false;
}