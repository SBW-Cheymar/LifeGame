#include <iostream>
#include <fstream>
#include "class.h"
#include "SFML/Graphics.hpp"
#include "nlohmann/include/nlohmann/json.hpp" // Inclure la bibliothèque JSON

void Settings::lire_fichier() {
    int dispo;
    std::cout << "Possedez-vous un fichier de configuration ?\n"
              << "1 : Oui || 2 : Non" << std::endl;
    std::cin >> dispo;

    if (dispo == 1) {
        URL = config_path();
        std::ifstream fichier(URL, std::ios::in);

        if (fichier) {
            try {
                // Lire tout le contenu du fichier JSON
                nlohmann::json jsonData;
                fichier >> jsonData;

                // Extraire les valeurs gridWidth et gridHeight
                iterations_max = jsonData["iterations_max"].get<int>();
                ligne = jsonData["gridHeight"].get<int>();
                colonne = jsonData["gridWidth"].get<int>();

                // Vérification des dimensions et de gridData
                if (!jsonData.contains("gridData") || !jsonData["gridData"].is_array()) {
                    throw std::runtime_error("Le champ 'gridData' est manquant ou mal forme !");
                }

                auto gridData = jsonData["gridData"];

                if (gridData.size() != ligne) {
                    throw std::runtime_error("Le nombre de lignes dans 'gridData' ne correspond pas à 'gridHeight' !");
                }

                for (const auto& row : gridData) {
                    if (row.size() != colonne) {
                        throw std::runtime_error("Le nombre de colonnes dans une ligne de 'gridData' ne correspond pas à 'gridWidth' !");
                    }
                }

                //Affichage du nomnbre de lignes et de colonnes
                std::cout << "Grille dimensions : Lignes = " << ligne << ", Colonnes = " << colonne << std::endl;

                // Actualiser la matrice
                matrice.resize(ligne, std::vector<bool>(colonne, false));

                // Remplir la matrice avec les données JSON
                for (int i = 0; i < ligne; ++i) {
                    for (int j = 0; j < colonne; ++j) {
                        matrice[i][j] = gridData[i][j].get<int>() != 0; // Convertir en booléen
                    }
                }

                // Afficher le contenu de la matrice
                std::cout << "Contenu de la grille :" << std::endl;
                for (const auto& row : matrice) {
                    for (const auto& cell : row) {
                        std::cout << cell << " "; // Affiche 1 ou 0
                    }
                    std::cout << std::endl;
                }
            } catch (const std::exception& e) {
                throw std::runtime_error("Erreur d'analyse du fichier JSON : " + std::string(e.what()));
            }
            fichier.close();
        } else {
            throw std::runtime_error("Erreur de la lecture du fichier !");
        }
    } else {
        non_config_file();
    }
}

void Settings::save_fichier(){
    if (modes == 1) {

        std::ofstream out("output.txt", std::ios::out | std::ios::app);

        if (out) {
            for(int k = 0; k < iterations_max; k++) {
                out << " \n Iteration numero : " << k << std::endl;
                out << colonne << " " << ligne << std::endl;

                for (int i = 0; i < ligne; ++i) {
                    for (int j = 0; j < colonne; ++j) {
                        out << matrice[i][j];
                        if (j < colonne - 1) out << ", "; // Pas de virgule après le dernier élément
                    }
                    if (i < ligne - 1) out << ","; // Pas de virgule après la dernière ligne
                    out << "\n";
                }
            }
        }
        else {
            std::cerr << "Impossible de realiser les sauvegardes" <<std::endl;
        }

        out.close();
    }
}

int Settings::get_iterations(){
    return iterations_max;
}

int Settings::get_modes() {
    return modes;
}


std::vector<std::vector<bool>>& Settings::get_matrice() {
    return matrice;
}

int Settings::choix_modes() {
    std::cout << "Choisir votre mode:\n";
    std::cout << "1. Mode Console\n";
    std::cout << "2. Mode Graphique\n" << std::endl;
    std::cin >> modes;

    if (modes == 1) {
        std::cout << "Vous avez choisi le Mode Console \n" << std::endl;
        return 1;
    }
    else if (modes == 2) {
        std::cout << "Vous avez choisi le Mode Graphique \n" << std::endl;
        return 2;
    } else {
        throw std::invalid_argument("Le numero que vous avez saisi est associe a aucun modes.");
        return 0;
    }
}

void Settings::non_config_file() {

    // Initialiser le générateur de nombres aléatoires
    std::srand(std::time(0));

    std::ofstream fichier_nc("non_config.json", std::ios::out | std::ios::trunc);
    if (fichier_nc) {
        // Demande à l'utilisateur
        std::cout << "Veuillez entrer le nombre d'iterations maximum : ";
        std::cin >> iterations_max;
        std::cout << "Veuillez entrer le nombre de lignes : ";
        std::cin >> ligne;
        std::cout << "Veuillez entrer le nombre de colonnes : ";
        std::cin >> colonne;

        // Initialisation de la matrice avec des valeurs aléatoires
        matrice.resize(ligne, std::vector<bool>(colonne, false));
        for (int i = 0; i < ligne; ++i) {
            for (int j = 0; j < colonne; ++j) {
                matrice[i][j] = std::rand() % 2; // Génère true (1) ou false (0)
            }
        }

        // Écriture dans le fichier JSON
        fichier_nc << "{\n";
        fichier_nc << "  \"iterations_max\": " << iterations_max << ",\n";
        fichier_nc << "  \"gridWidth\": " << ligne << ",\n";
        fichier_nc << "  \"gridHeight\": " << colonne << ",\n";
        fichier_nc << "  \"gridData\": [\n";

        for (int i = 0; i < ligne; ++i) {
            fichier_nc << "    [";
            for (int j = 0; j < colonne; ++j) {
                fichier_nc << matrice[i][j];
                if (j < colonne - 1) fichier_nc << ", "; // Pas de virgule après le dernier élément
            }
            fichier_nc << "]";
            if (i < ligne - 1) fichier_nc << ","; // Pas de virgule après la dernière ligne
            fichier_nc << "\n";
        }

        fichier_nc << "  ]\n";
        fichier_nc << "}";

        fichier_nc.close();
        std::cout << "Fichier 'non_config.json' cree avec succes avec une grille de donnees aleatoires.\n";
    } else {
        std::cerr << "Erreur : impossible d'ouvrir le fichier pour ecrire.\n";
    }
}


//Partie ajoutée
std::string Settings::config_path() {
    std::cout << "Veuillez saisir le chemin de votre fichier:\n";
    std::cout << "Exemple : config.json \n";
    std::cin >> URL;
    URL.erase(std::remove_if(URL.begin(), URL.end(), ::isspace), URL.end());

    return URL;
}



int main() {
    Settings settings;
    settings.lire_fichier(); // Charge la matrice
    settings.choix_modes();

    std::vector<std::vector<bool>>& matrice = settings.get_matrice();


    Cellule_movible celluleMovible(matrice);
    //Cellule_Obstacle celluleObstacle(matrice);

    celluleMovible.afficherMatrice(); // Affiche la matrice partagée
    celluleMovible.simulerMatrice();  // Simule sur la matrice partagée
    settings.save_fichier();          //Sauvegarde les résultats
}

