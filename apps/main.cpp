#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <string.h>

using namespace std;

std::string readJsonFile(const std::string& pathFile);
void removeCharsFromString( string &str, char* charsToRemove );

// bool checkValidity(const std::string& text);

int main(int argc, char* argv[])
{

    if(argc != 2)
    {
        std::cerr << "Pass l'excecutable avec le path vers le json :"   
                << "./CheckValidity /cheminVersJson " << std::endl;
        return -1;
    }

    std::string allText = readJsonFile(argv[1]);
    int size = allText.size();

    std::cout << "Premier Element : " << allText[0] << std::endl;
    std::cout << "Dernier Element : " << allText[size - 1] << std::endl;

    if(allText[0] != allText[size - 1])
    {
        std::cerr << "Fichier non valide." << std::endl;
        return -1;
    }

    return 0;
}

void removeCharsFromString( string &str, char* charsToRemove ) {
   for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
      str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
   }
}

std::string readJsonFile(const std::string& pathFile)
{
    string allText;
    // Open the file "abc.txt" for reading
    ifstream inputFile(pathFile.c_str());

    // Variable to store each line from the file
    string line;

    // Read each line from the file and print it
    while (getline(inputFile, line)) {
        // Process each line as needed
        allText = allText.append(line);
    }

    // int size = allText.size();

    // Remove all occurrences of 3 from vector v
    char chars[] = " ";
    removeCharsFromString( allText, chars);
    std::cout << allText << std::endl;

    // Always close the file when done
    inputFile.close();

    return allText;
}

// bool checkValidity(const std::string& text)
// {
//     int size = text.size();
//     if(size == 0)
//         return false;

//     std::unordered_map<std::string, int> brackTocompteur; // Pour stocker chaque ouvertur fermeture de { et }
//     for(int i = 0;  i < size, ++i)
//     {
//         switch(text[i])
//         {
//             case '[':
//                 brackTocompteur["["]++;
//                 break;
//             case '{':
//                 brackTocompteur["{"]++;
//                 break; 
//             case ']':
//                 brackTocompteur["]"]++;
//                 break;
//             case '}':
//                 brackTocompteur["}"]++;
//                 break; 
//             default :
//                 break;

//         }
//     }

//     return true;
// }
