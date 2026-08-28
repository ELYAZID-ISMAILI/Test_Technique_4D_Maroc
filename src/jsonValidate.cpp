#include "jsonValidate.hpp"
#include <cctype>
#include <string_view>

// Retire les espaces autour d'un token, jamais ceux à l'intérieur
static std::string_view trimWhitespace(std::string_view s)
{
    size_t start = 0;
    size_t end   = s.size();

    while (start < end && std::isspace(static_cast<unsigned char>(s[start])))
        start++;
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1])))
        end--;

    return s.substr(start, end - start);
}

// Sépare une string_view par un délimiteur en respectant
// l'imbrication ({}, []) et les strings ("")
static std::vector<std::string_view> split(std::string_view str, const char delimiter)
{
    std::vector<std::string_view> res;
    size_t tokenStart = 0;
    int depth = 0;
    bool inString = false;
    bool escaped  = false;

    for (size_t i = 0; i < str.size(); i++)
    {
        char c = str[i];

        if (inString)
        {
            if (escaped)        escaped = false;
            else if (c == '\\') escaped = true;
            else if (c == '"')  inString = false;
            continue;
        }

        if (c == '"') { inString = true; continue; }

        if (c == '{' || c == '[') depth++;
        else if (c == '}' || c == ']') depth--;

        if (c == delimiter && depth == 0)
        {
            res.push_back(str.substr(tokenStart, i - tokenStart));
            tokenStart = i + 1;
        }
    }
    res.push_back(str.substr(tokenStart));

    return res;
}

static bool isValidString(std::string_view s)
{
    if (s.size() < 2 || s.front() != '"' || s.back() != '"')
        return false;

    const std::string_view body = s.substr(1, s.size() - 2);

    for (size_t i = 0; i < body.size(); i++)
    {
        char c = body[i];

        if (c != '\\')
            continue;

        i++; // On passe au caractère échappé
        if (i >= body.size())
            return false;

        // Les échappements JSON : \" \\ \/ \n \r \t
        if (std::string_view("\"\\/nrt").find(body[i]) != std::string_view::npos)
            continue;;

        for (int k = 0; k < 4; k++)
            if (!std::isxdigit(static_cast<unsigned char>(body[++i])))
                return false;
    }
    return true;
}

// Simplification autorisée par le sujet : un nombre est une suite de chiffres
// décimaux, sans signe, sans partie décimale ni exposant
static bool isValidNumber(std::string_view s)
{
    if (s.empty())
        return false;

    for (char c : s)
        if (!std::isdigit(static_cast<unsigned char>(c)))
            return false;

    return true;
}

void JsonValidate::readAllTextFromJson(std::ifstream& file)
{
    // Variable to store each line from the file
    std::string line;

    // Read each line from the file and print it
    while (getline(file, line))
    {
        // Process each line as needed
        allText_ = allText_.append(line).append("\n");
    }
}

JsonValidate::JsonValidate(const std::string& pathToFile)
{
    std::ifstream file(pathToFile.c_str());
    readAllTextFromJson(file);
}

// Pré-filtre rapide : vérifie l'équilibrage global des { } et des [ ]
// en un seul passage. Ne valide pas la grammaire, sert à rejeter vite
// un fichier manifestement cassé avant de lancer la récursion.
bool JsonValidate::checkDelimitersValidity() const
{
    int accolades = 0;
    int brackets  = 0;
    bool inString = false;
    bool escaped  = false;

    for (auto const& c : allText_)
    {
        if (inString)
        {
            if (escaped)        escaped = false;
            else if (c == '\\') escaped = true;
            else if (c == '"')  inString = false;
            continue;
        }

        if (c == '"')
            inString = true;

        else if (c == '{')
            accolades++;

        else if (c == '}')
        {
            if (accolades <= 0)
                return false;
            accolades--;
        }

        else if (c == '[')
            brackets++;

        else if (c == ']')
        {
            if (brackets <= 0)
                return false;
            brackets--;
        }
    }
    // Chaque ouverture a sa propre fermeture
    return accolades == 0 && brackets == 0;
}

bool JsonValidate::isValidValue(std::string_view rawValue)
{
    const std::string_view value = trimWhitespace(rawValue);

    if (value.empty())
        return false;

    char first = value.front();
    char last  = value.back();

    // String
    if (first == '"')
        return isValidString(value);

    // Nombre
    if (first == '-' || std::isdigit(static_cast<unsigned char>(first)))
        return isValidNumber(value);

    // Literals
    if (value == "true" || value == "false" || value == "null")
        return true;

    // Object qui est un json
    if (first == '{' && last == '}')
    {
        std::string_view inner = trimWhitespace(value.substr(1, value.size() - 2));
        if (inner.empty()) return true;

        auto pairs = split(inner, ',');
        for (const auto& pair : pairs)
        {
            auto kv = split(pair, ':');
            if (kv.size() != 2)
                return false;

            std::string_view key = trimWhitespace(kv[0]);
            std::string_view val = kv[1];

            if (!isValidString(key))
                return false;

            if (!isValidValue(val))
                return false;
        }
        return true;
    }

    // Array
    if (first == '[' && last == ']')
    {
        std::string_view inner = trimWhitespace(value.substr(1, value.size() - 2));
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
    const std::string_view root = trimWhitespace(allText_);

    if (root.empty())
        return false;

    // Pré-filtre rapide : les délimiteurs sont-ils équilibrés ?
    if (!checkDelimitersValidity())
        return false;
    
    // Validation complète par récursion (DFS)
    // Parcourt chaque valeur en profondeur jusqu'aux types simples
    return isValidValue(root);
}
