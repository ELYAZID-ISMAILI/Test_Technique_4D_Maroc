#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>


class JsonValidate
{
    public :
        JsonValidate() =  default;
        JsonValidate(const std::string& pathToJson);

        bool isValid() const;

        bool checkCommaValidity() const:
        bool checkAccoladeValidaty()const;
        bool checkBracketValidaty() const;


    private : 
        std::vector<std::unordered_map<std::string, std::string>>  keyValues_;
        std::ifstream file_;

}