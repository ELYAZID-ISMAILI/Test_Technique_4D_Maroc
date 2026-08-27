#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <bits/stdc++.h>
#include <sstream>    

using namespace std;


static vector<string> split(string str, char delimiter)
{
  // Using str in a string stream
    stringstream ss(str);
    vector<string> res;
    string token;
    while (getline(ss, token, delimiter)) {
        res.push_back(token);
    }
    return res;
}

std::string readJsonFile(const std::string& pathFile);

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

    // std::cout << "Premier Element : " << allText[0] << std::endl;
    // std::cout << "Dernier Element : " << allText[size - 1] << std::endl;

    if(allText[0] != allText[size - 1])
    {
        std::cerr << "Fichier non valide." << std::endl;
        return -1;
    }

    return 0;
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

    // Remove all occurrences of ' ' in text
    allText.erase( remove(allText.begin(), allText.end(), ' '), allText.end() );

    // Split Text by ','
    std::vector<std::string> textSplited = split(allText, ',');
    
    for(auto const& keyValue : textSplited)
        std::cout << keyValue << std::endl;

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
