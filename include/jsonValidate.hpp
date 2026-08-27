#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

class JsonValidate
{
    public :
        // Construteur par défaut
        JsonValidate() =  default;

        // Constructeur de Copie
        JsonValidate(const std::string& pathToJson);

        // Fonction qui retourne l'etat de validité du json
        bool isValid() const; 

        // Fonction qui retourne l'etat de validité des virgules
        bool checkCommaValidity() const;

        // Fonction qui retourne l'etat de validité des accolades
        bool checkAccoladeValidaty()const;

        // Fonction qui retourne l'etat de validité des brackets
        bool checkBracketsValidaty() const;

        // Decomposer le json et le remplir dans keyValues_
        void decomposeJson();

        // Lecture de tous le texte
        void readallTextFromJson();

    private : 
        std::unordered_map<std::string, std::string>  keyValues_; // Contient les key Values de tous les mots
        std::vector<std::string> wordsSplited_; // Vector des mots splité
        std::string allText_;
        std::ifstream jsonFile_; // Reader de Fichier json
};
