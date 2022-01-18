#include "headers/data.hpp"

Data::Data(string name, string type, string size){
    this->name = name;
    this->type = type;
    this->size = size;
    
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    string realDate = to_string(tm.tm_mday) + "/" 
                + to_string(tm.tm_mon+1) + "/" 
                + to_string(tm.tm_year + 1900) + " - "
                + to_string(tm.tm_hour) + ":"
                + to_string(tm.tm_min);

    this->createDate = realDate;
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