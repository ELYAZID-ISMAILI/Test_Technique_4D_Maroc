#include "jsonValidate.hpp"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <iostream>   
#include <sstream>    
#include <bits/stdc++.h>

void JsonValidate::readAllTextFromJson()
{
    // Variable to store each line from the file
    std::string line;

    // Read each line from the file and print it
    while (getline(jsonFile_, line)) 
    {
        // Process each line as needed
        allText_ = allText_.append(line);
    }
}

static std::vector<std::string> split(std::string str, char delimiter)
{
  // Using str in a string stream
    std::stringstream ss(str);
    std::vector<std::string> res;
    std::string token;
    while (getline(ss, token, delimiter)) {
        res.push_back(token);
    }
    return res;
}


JsonValidate::JsonValidate(const std::string& pathToFile)
{
    jsonFile_ = std::ifstream(pathToFile.c_str());
    readAllTextFromJson(); // Needs jsonFile_ after
}

void JsonValidate::decomposeJson()
{
    // Remove all occurrences of ' ' in text
    allText_.erase( remove(allText_.begin(), allText_.end(), ' '), allText_.end());

    // Remove the carachter 0 and size - 1
    allText_.erase(allText_.begin(), allText_.begin() + 1);
    allText_.pop_back();

    // Split by comma to have keyValues
    wordsSplited_ = split(allText_, ',');
    
    for(auto const& keyValue : wordsSplited_)
    {        
        std::size_t found = keyValue.find(":");

        if (found == std::string::npos)
            continue;

        keyValues_.insert({keyValue.substr(0,found - 1), keyValue.substr(found + 1)});

    }
}

// Fonction qui retourne l'etat de validité des virgules
bool JsonValidate::checkCommaValidity() const
{
    for(const auto& word : wordsSplited_)
    {
        if(word == "")
        {
            return false;
        }
    }
    return true;
}

// Fonction qui retourne l'etat de validité des accolades
bool JsonValidate::checkAccoladeValidaty() const 
{
    int compt = 0;

    for(auto const& c : allText_)
    {
        if(c == '{')
            compt++;
        
        else if(c == '}')
        {
            if(compt <= 0)
                return false;

            else
                compt--;
        }
    }
    return (compt == 0);
}

// Fonction qui retourne l'etat de validité des brackets
bool JsonValidate::checkBracketsValidaty() const
{
        int compt = 0;

    for(auto const& c : allText_)
    {
        if(c == '[')
            compt++;
        
        else if(c == ']')
        {
            if(compt <= 0)
                return false;

            else
                compt--;
        }
    }
    return (compt == 0);
}

bool JsonValidate::isValid()
{
    // Decomposation de json 
    decomposeJson();

    if(keyValues_.empty())
        return true;

    // Verification d'accolade
    if(!checkAccoladeValidaty())
        return false;

    // Verification des virgules
    if(!checkCommaValidity())
        return false;

    if(!checkBracketsValidaty())
        return false;

    std::queue<std::string> q;
    // Iteration sur les key value
    for(auto keyVal : keyValues_)
    {
        // Ici on itere sur les key value
        // Le json est une structure iterative
        // Pour chaque key, si sa valeur est simple c'est ok
        // Si c'est complexe cad c'est un json on le repasse pour iterer
        // sur lui dans la queue jusqu'a trouver un element simple

        q.push(keyVal.second);
        while (!q.empty())                  // tant qu'il reste des nœuds à traiter
        {
            std::string json = q.front();     // le nœud de devant
            q.pop();                        // on le retire de la file

            // Si c'est simple comme double ou string ou array c'est ok on fait rien
            // Si commence par { et fini } c'est un json et on le met dans keyValues_
            // Si aucun de ces cas, on sort avec false
        }

    }

    return true;

}
