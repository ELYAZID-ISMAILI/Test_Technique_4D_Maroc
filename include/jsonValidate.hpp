#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <fstream>

class JsonValidate
{
public:
    // Ouvre le fichier et charge son contenu dans allText_
    JsonValidate(const std::string& pathToFile);

    // Point d'entrée : true si le fichier contient un JSON valide
    bool isValid();

private:
    // Lit le fichier ligne par ligne dans allText_ en gardant les '\n'
    void readAllTextFromJson(std::ifstream& file);

    // Pré-filtre rapide : vérifie l'équilibrage global des { } et des [ ]
    bool checkDelimitersValidity() const;

    // Valide récursivement une valeur JSON (string, nombre, literal, objet, array)
    // rawValue pointe dans allText_, qui ne doit pas être modifié pendant la validation
    bool isValidValue(std::string_view rawValue);

    // Propriétaire du texte, seul état conservé par la classe
    std::string allText_;
};
