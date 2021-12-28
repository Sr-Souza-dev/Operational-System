#ifndef _FILE_HPP
#define _FILE_HPP


#include <fstream>
#include <iostream>
#include <string>

#include "../../../lib/json.hpp"
using Json = nlohmann::json;

using namespace std;

class FileJson
{
    private:
        string dyrectory;
    public:
        FileJson(string dyrectory);
        Json getJsonFile();
};
#endif