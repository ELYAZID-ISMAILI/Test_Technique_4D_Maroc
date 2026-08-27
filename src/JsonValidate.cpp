#include "JsonValidate.hpp"


JsonValidate::JsonValidate(const std::string& pathToFile)
{
    file_ = std::fstream(pathToFile.c_str());

    
}


