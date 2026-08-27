#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void readJsonFile(const std::string& pathFile);

int main(int argc, char* argv[])
{

    if(argc != 2)
    {
        std::cerr << "Pass l'excecutable avec le path vers le json :"   
                << "./CheckValidity /cheminVersJson " << std::endl;
        return -1;
    }

    readJsonFile(argv[1]);

    return 0;
}

void readJsonFile(const std::string& pathFile)
{
    // Open the file "abc.txt" for reading
    ifstream inputFile(pathFile.c_str());

    // Variable to store each line from the file
    string line;

    // Read each line from the file and print it
    while (getline(inputFile, line)) {
        // Process each line as needed
        cout << line << endl;

    }

    // Always close the file when done
    inputFile.close();
}
