#pragma once

#ifndef CLASS_H
#define CLASS_H

#include <vector>
#include <fstream>
#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <set>
#include "SFML/Graphics.hpp"



/**
 * @brief La classe Settings permet de lire et définir les paramètres globaux de l'automate, sauvegarder le fichier, configurer un fichier etc.
 */
class Settings {
private :
    std::string URL;
    int iterations_max;
    int modes;
    int ligne, colonne;
    std::vector<std::vector<bool>> matrice;

public:
    void lire_fichier();
    int get_iterations();
    int choix_modes();
    void non_config_file();
    void save_fichier();

    // Partie ajoutée

    std::string config_path();
    std::vector<std::vector<bool>>& get_matrice();  //Getter pour la matrice

    int get_modes();
    int get_ligne();
    int get_colonne();

};

class Cellule {
protected:
    std::vector<std::vector<bool>>& matrice; // Référence à la matrice de Settings
    int iterations_cell;
    int mode;
    int ligne;
    int colonne;

public:
    Cellule(std::vector<std::vector<bool>>& matrice_ref);
    virtual void definirEtat(int x, int y, bool etat) = 0;
    virtual void changerEtat() = 0;

    void set_iterations_cell(int iteration);
    void set_modes(int mode_settings);
    void set_ligne(int ligne_settings);
    void set_colonne(int colonne_settings);

    void afficherMatrice();
    void simulerMatrice();
    void save_fichier();
    std::vector<std::vector<bool>>& get_matrice_cell();

    void set_iterations_max();
};

class Cellule_movible : public Cellule {
public:
    Cellule_movible(std::vector<std::vector<bool>>& matrice_ref);
    void definirEtat(int x, int y, bool etat) override;
    void changerEtat() override;
    std::vector<std::vector<bool>>& get_matrice_cell();
};

class IHM {
protected:
    std::vector<std::vector<bool>>& matrice_ref;
    int iteration_max; // Nombre maximum d'itérations
public:
    IHM(std::vector<std::vector<bool>>& matrice) : matrice_ref(matrice) {}
    virtual void Aff_graphique() = 0;
    void set_iteration_max(int it_max);
};

class IHM_Moniteur : public IHM {
private:
    Cellule_movible& celluleMovible;
public:
    IHM_Moniteur(std::vector<std::vector<bool>>& matrice_ref, Cellule_movible& cellule);
    void Aff_graphique() override;
};

class IHM_Graphique : public IHM {
private:
    const int cellSize = 1; // Taille de chaque cellule
    int Width = 860;
    int Height = 540;
    int mode; // Mode de jeu
    sf::RenderWindow window;
    sf::Font font;
    sf::Font font2;
    sf::Text playText;
    sf::Text quitText;
    sf::Text endText;
    int iterationCount; // Compteur d'itérations
    Cellule_movible& celluleMovible;

    void drawGrid();
    void updateMatrice();

public:
    IHM_Graphique(std::vector<std::vector<bool>>& matrice_ref, Cellule_movible& cellule);
    void Aff_graphique();
};


#endif //CLASS_H