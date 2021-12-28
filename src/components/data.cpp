#include "headers/data.hpp"

Data::Data(string name, string type, string size, string createDate){
    this->name = name;
    this->type = type;
    this->size = size;
    this->createDate = createDate;
}


//Functions
void Data::printHead(){
    cout<< "\n-------------------------------------------------------------"<<endl;
    printf(" +     NAME     |  TYPE  |   SIZE   |        CREATE        +\n");
    cout<< "-------------------------------------------------------------"<<endl;
}
void Data::print(){
    printf(" +  %-10s  | %-6s | %-8s |  %-18s  +\n",name.c_str(), type.c_str(), size.c_str(), createDate.c_str());
}
void Data::printFooter(){
    cout<< "-------------------------------------------------------------\n"<<endl;
}