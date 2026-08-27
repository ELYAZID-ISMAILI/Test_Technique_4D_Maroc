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

bool JsonValidate::isValidValue(const std::string& value)
{
    if (value.empty())
        return false;

    char first = value.front();
    char last  = value.back();

    // String
    if (first == '"' && last == '"')
        return true;

    // Nombre
    if (isdigit(first))
    {
        for (char c : value)
            if (!isdigit(c)) return false;
        return true;
    }

    // true ou false ou null
    if (value == "true" || value == "false" || value == "null")
        return true;

    // un json
    if (first == '{' && last == '}')
    {
        std::string inner = value.substr(1, value.size() - 2);
        if (inner.empty()) return true;

        auto pairs = split(inner, ',');
        for (const auto& pair : pairs)
        {
            size_t colon = pair.find(':');
            if (colon == std::string::npos)
                return false;

            std::string key = pair.substr(0, colon);
            std::string val = pair.substr(colon + 1);

            if (key.front() != '"' || key.back() != '"')
                return false;

            if (!isValidValue(val))
                return false;
        }
        return true;
    }

    // Cas de tableau
    if (first == '[' && last == ']')
    {
        std::string inner = value.substr(1, value.size() - 2);
        if (inner.empty()) return true;

        auto elements = split(inner, ',');
        for (const auto& elem : elements)
        {
            if (!isValidValue(elem))
                return false;
        }
        return true;
    }

    return false;
}

bool JsonValidate::isValid()
{
    // Supprimer les espaces hors strings
    std::string cleaned;
    bool inString = false;
    for (size_t i = 0; i < allText_.size(); i++)
    {
        char c = allText_[i];
        if (c == '"' && (i == 0 || allText_[i-1] != '\\'))
            inString = !inString;
        if (inString || (c != ' ' && c != '\n' && c != '\t' && c != '\r'))
            cleaned += c;
    }
    allText_ = cleaned;

    // Vérifications rapides avant la récursion
    if (!checkAccoladeValidaty())
        return false;

    if (!checkBracketsValidaty())
        return false;

    // Validation complète par récursion
    return isValidValue(allText_);
}
