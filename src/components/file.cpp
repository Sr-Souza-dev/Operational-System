#include "headers/file.hpp"

// CONSTRUCTOR
FileJson::FileJson(string directory){
    this->dyrectory = directory;
}

// FUNCTIONS
Json FileJson::getJsonFile(){

    try{
        ifstream ifs(dyrectory);
        Json json;
        ifs >> json;

        ifs.close();
        return json;

    }catch(string err){
        cout<< "[ERRO] - erro ao capturar arquivo (getJsonFile) "<<err<<endl;
        return Json();
    }
}
