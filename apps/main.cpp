#include "jsonValidate.hpp"

#include <iostream>
 

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cerr << "Pass l'excecutable avec le path vers le json :"   
                << "./CheckValidity /cheminVersJson " << std::endl;
        return -1;
    }

    JsonValidate jsonVali = JsonValidate(argv[2]);
    std::cout << jsonVali.isValid() << std::endl;

    return 0;
}
