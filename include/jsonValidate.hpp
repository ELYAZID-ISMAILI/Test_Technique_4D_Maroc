#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

class JsonValidate
{
    public :
        // Construteur par défaut
        JsonValidate() =  default;

        // Constructeur avec chemin vers le fichier json
        JsonValidate(const std::string& pathToJson);

        // Valide récursivement une valeur JSON
        // Types simples (string, number, bool, null) : validation directe
        // Types complexes (object, array) : appel récursif sur chaque sous-valeur
        bool isValidValue(const std::string& value);

        // Fonction qui retourne l'etat de validité du json
        bool isValid(); 

        // Fonction qui retourne l'etat de validité des accolades
        bool checkAccoladeValidaty() const;

        // Fonction qui retourne l'etat de validité des brackets
        bool checkBracketsValidaty() const;

        // Decomposer le json et le remplir dans keyValues_
        void decomposeJson();

        // Lit le fichier JSON ligne par ligne et concatène dans allText_
        void readAllTextFromJson();

    private : 
        std::unordered_map<std::string, std::string>  keyValues_; // Contient les key Values de tous les mots
        std::vector<std::string> wordsSplited_; // Vector des mots splité
        std::string allText_; // Contenu brut du fichier JSON
        std::ifstream jsonFile_; // Reader de Fichier json
};
