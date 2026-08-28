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

    // Fonction qui retourne l'etat de validité des accolades
    bool checkAccoladeValidaty() const;

    // Fonction qui retourne l'etat de validité des brackets
    bool checkBracketsValidaty() const;

    // Valide récursivement une valeur JSON (string, nombre, literal, objet, array)
    // rawValue pointe dans allText_, qui ne doit pas être modifié pendant la validation
    bool isValidValue(std::string_view rawValue);

    // Propriétaire du texte, seul état conservé par la classe
    std::string allText_;
};
