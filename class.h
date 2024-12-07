#pragma once

#ifndef CLASS_H
#define CLASS_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>


/**
 * @brief La classe Settings permet de lire et définir les paramètres globaux de l'automate, sauvegarder le fichier, configurer un fichier etc.
 */
class Settings {
private :
    std::string URL;
    int iterations_max;
    int modes;

    //Partie ajoutée
    int ligne, colonne;
    std::vector<std::vector<bool>> matrice;

public:
    void lire_fichier();
    //void set_interactions(); SUPPRIME
    int get_iterations();   // MODIFER car get_interactions
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
class Grille {
private:
    int lignes;
    int colonnes;
    bool torique;
    std::vector<std::vector<bool>> etatGrille;

public:
    Grille(int l, int c, bool t) : lignes(l), colonnes(c), torique(t) {}
    void init();
    void afficher();
    void MAJ();
    bool estTorique();
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

class Cellule_Obstacle : public Cellule {
public:
    Cellule_Obstacle(std::vector<std::vector<bool>>& matrice_ref);
    void definirEtat(int x, int y, bool etat) override;
    void changerEtat() override;
};



class IHM {
protected:
    Settings* settings;
    Grille* grille;
    Cellule* cellule;
    sf::RenderWindow* window;
    int cellSize = 0;

public:
    IHM(Settings* s, Grille* g, Cellule* c);
    virtual void Aff_graphique(sf::RenderWindow& win) = 0;
    virtual void Event_Settings() = 0;
};

class IHM_Moniteur : public IHM {
public:
    IHM_Moniteur(Settings* s, Grille* g, Cellule* c);
    void Aff_graphique(sf::RenderWindow& win) override;
    void Event_Settings() override;
};

class IHM_Graphique : public IHM {
public:
    IHM_Graphique(Settings* s, Grille* g, Cellule* c);
    void Aff_graphique(sf::RenderWindow& win) override;
    void Event_Settings() override;
};



#endif //CLASS_H