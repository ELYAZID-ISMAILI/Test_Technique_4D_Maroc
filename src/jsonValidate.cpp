#include "jsonValidate.hpp"
#include <iostream>
#include <sstream>
#include <iostream>
#include <cctype>

// Sépare une string par un délimiteur en respectant
// l'imbrication ({}, []) et les strings ("")
static std::vector<std::string> split(std::string str, char delimiter)
{
    std::vector<std::string> res;
    std::string token;
    int depth = 0;
    bool inString = false;

    for (size_t i = 0; i < str.size(); i++)
    {
        char c = str[i];
        if (c == '"' && (i == 0 || str[i-1] != '\\'))
            inString = !inString;

        if (!inString)
        {
            if (c == '{' || c == '[') depth++;
            else if (c == '}' || c == ']') depth--;
        }

        if (c == delimiter && depth == 0 && !inString)
        {
            res.push_back(token);
            token.clear();
        }
        else
            token += c;
    }
    if (!token.empty())
        res.push_back(token);

    return res;
}

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

JsonValidate::JsonValidate(const std::string& pathToFile)
{
    jsonFile_ = std::ifstream(pathToFile.c_str());
    readAllTextFromJson(); // Needs jsonFile_ after
}

void JsonValidate::decomposeJson()
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

    // Stocker les clé:valeur si c'est un object
    if(!allText_.empty() && allText_.front() == '{' && allText_.back() == '}')
    {
        std::string inner = allText_.substr(1, allText_.size() - 2);
        if (inner.empty()) return;

        wordsSplited_ = split(inner, ',');
        for (const auto& pair : wordsSplited_)
        {
            size_t colon = pair.find(':');
            if (colon == std::string::npos)
                continue;

            std::string key = pair.substr(0, colon);
            std::string val = pair.substr(colon + 1);
            keyValues_.insert({key, val});
        }
    }
}

// Fonction qui retourne l'etat de validité des accolades
bool JsonValidate::checkAccoladeValidaty() const 
{
    int compt = 0;

    // On incremente avec { et on décrementer avec } sauf si compteur > 0
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
    return (compt == 0); // Chaque ouverture de { a sa propre fermeture }.
}

// Fonction qui retourne l'etat de validité des brackets
bool JsonValidate::checkBracketsValidaty() const
{
    int compt = 0;

    // On incremente avec [ et on décrementer avec ] sauf si compteur > 0
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
    return (compt == 0); // Chaque ouverture de [ a sa propre fermeture ].
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
            if (!isdigit(c)) 
                return false;
        
        return true;
    }

    // Literals
    if (value == "true" || value == "false" || value == "null")
        return true;

    // Object qui est un json
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

    // Array
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

    // non reconnu
    return false;
}

bool JsonValidate::isValid()
{
    // Nettoyage du texte et extraction des clé:valeur
    decomposeJson();

    // Vérification rapide : les { } sont-ils équilibrés ?
    if (!checkAccoladeValidaty())
        return false;

    // Vérification rapide : les [ ] sont-ils équilibrés ?
    if (!checkBracketsValidaty())
        return false;

    // Validation complète par récursion (DFS)
    // Parcourt chaque valeur en profondeur jusqu'aux types simples
    return isValidValue(allText_);
}
