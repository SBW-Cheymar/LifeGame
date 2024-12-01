#pragma once

#ifndef CLASS_H
#define CLASS_H

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>


/**
 * @brief La classe Settings permet de lire et définir les paramètres globaux de l'automate, sauvegarder le fichier, configurer un fichier etc.
 */
class Settings {
private :
    std::string URL;
    int interactions_max;
    int modes;

public:
    void lire_fichier();
    void save_fichier();
    void set_interactions();
    void get_interactions();
    int choix_modes();
    void non_config_file();
};

class Grille {
private:
    int ligne;
    int colonne;
    bool torique;
    std::vector<std::vector<bool>> etatGrille;

public:
    void init();
    void afficher();
    void MAJ();
    bool estTorique();
};

class IHM {
private:
    int largeur;
    int hauteur;

public:
    virtual void Aff_graphique() = 0;
    virtual void Event_Settings() = 0;
    virtual bool ending() = 0;
};

class IHM_Moniteur : public IHM {
  public:
    void Aff_graphique() override;
    void Event_Settings() override;
    bool ending() override;
};

class IHM_Graphique : public IHM {
public:
    void Aff_graphique() override;
    void Event_Settings() override;
    bool ending() override;
};

#endif //CLASS_H
