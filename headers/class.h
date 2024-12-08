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
 * @brief La classe Settings permet de lire et définir les paramètres globaux de l'automate.
 * Elle permet également de sauvegarder les paramètres dans un fichier et de configurer ces derniers.
 */
class Settings {
private:
    std::string URL;                        ///< URL du fichier de configuration.
    int iterations_max;                     ///< Nombre maximal d'itérations.
    int modes;                              ///< Mode de fonctionnement actuel.
    int ligne;                              ///< Nombre de lignes de la matrice.
    int colonne;                            ///< Nombre de colonnes de la matrice.
    std::vector<std::vector<bool>> matrice; ///< Matrice représentant l'état des cellules.

public:
    /**
     * @brief Lit les paramètres à partir d'un fichier de configuration.
     */
    void lire_fichier();

    /**
     * @brief Retourne le nombre maximal d'itérations.
     * @return Nombre d'itérations.
     */
    int get_iterations();

    /**
     * @brief Permet de choisir un mode de fonctionnement.
     * @return Le mode choisi.
     */
    int choix_modes();

    /**
     * @brief Définit un comportement par défaut si le fichier de configuration est absent.
     */
    void non_config_file();

    /**
     * @brief Sauvegarde les paramètres actuels dans un fichier.
     */
    void save_fichier();

    /**
     * @brief Retourne le chemin du fichier de configuration.
     * @return Chemin du fichier.
     */
    std::string config_path();

    /**
     * @brief Retourne une référence à la matrice.
     * @return Référence à la matrice.
     */
    std::vector<std::vector<bool>>& get_matrice();

    /**
     * @brief Retourne le mode actuel.
     * @return Mode actuel.
     */
    int get_modes();

    /**
     * @brief Retourne le nombre de lignes de la matrice.
     * @return Nombre de lignes.
     */
    int get_ligne();

    /**
     * @brief Retourne le nombre de colonnes de la matrice.
     * @return Nombre de colonnes.
     */
    int get_colonne();
};

/**
 * @brief Classe représentant une cellule de l'automate.
 */
class Cellule {
protected:
    std::vector<std::vector<bool>>& matrice;   ///< Référence à la matrice de Settings.
    int iterations_cell;                       ///< Nombre d'itérations pour la cellule.
    int mode;                                  ///< Mode actuel de la cellule.
    int ligne;                                 ///< Nombre de lignes dans la matrice.
    int colonne;                               ///< Nombre de colonnes dans la matrice.

public:
    /**
     * @brief Constructeur de la classe Cellule.
     * @param matrice_ref Référence à la matrice.
     */
    Cellule(std::vector<std::vector<bool>>& matrice_ref);

    /**
     * @brief Définit l'état d'une cellule à une position donnée.
     * @param x Coordonnée en X.
     * @param y Coordonnée en Y.
     * @param etat État de la cellule (true ou false).
     */
    virtual void definirEtat(int x, int y, bool etat) = 0;

    /**
     * @brief Change l'état de la cellule selon certaines règles.
     */
    virtual void changerEtat() = 0;

    void set_iterations_cell(int iteration);
    void set_modes(int mode_settings);
    void set_ligne(int ligne_settings);
    void set_colonne(int colonne_settings);

    /**
     * @brief Affiche l'état actuel de la matrice dans la console.
     */
    void afficherMatrice();

    /**
     * @brief Simule les transitions de la matrice pour plusieurs itérations.
     */
    void simulerMatrice();

    /**
     * @brief Sauvegarde l'état actuel de la matrice dans un fichier.
     */
    void save_fichier();

    /**
     * @brief Retourne une référence à la matrice.
     * @return Référence à la matrice.
     */
    std::vector<std::vector<bool>>& get_matrice_cell();

    void set_iterations_max();
};

/**
 * @brief Classe dérivée de Cellule avec des fonctionnalités supplémentaires pour des cellules "mobiles".
 */
class Cellule_movible : public Cellule {
public:
    Cellule_movible(std::vector<std::vector<bool>>& matrice_ref);
    void definirEtat(int x, int y, bool etat) override;
    void changerEtat() override;
    std::vector<std::vector<bool>>& get_matrice_cell();
};

/**
 * @brief Classe de base pour l'interface homme-machine (IHM) permettant d'afficher la matrice.
 */
class IHM {
protected:
    std::vector<std::vector<bool>>& matrice_ref;   ///< Référence à la matrice.
    int iteration_max;                             ///< Nombre maximum d'itérations.

public:
    /**
     * @brief Constructeur de la classe IHM.
     * @param matrice Référence à la matrice.
     */
    IHM(std::vector<std::vector<bool>>& matrice) : matrice_ref(matrice) {}

    /**
     * @brief Méthode virtuelle pour afficher la matrice graphiquement.
     */
    virtual void Aff_graphique() = 0;

    void set_iteration_max(int it_max);
};

/**
 * @brief Classe pour une IHM permettant de surveiller les cellules.
 */
class IHM_Moniteur : public IHM {
private:
    Cellule_movible& celluleMovible; ///< Référence à une cellule mobile.

public:
    IHM_Moniteur(std::vector<std::vector<bool>>& matrice_ref, Cellule_movible& cellule);

    /**
     * @brief Affichage de la matrice en console par appel de la procédure de Cellule_movible
     */
    void Aff_graphique() override;
};

/**
 * @brief Classe pour une IHM graphique utilisant SFML.
 */
class IHM_Graphique : public IHM {
private:
    const int cellSize = 3;           ///< Taille de chaque cellule.
    int Width = 860;                  ///< Largeur de la fenêtre.
    int Height = 540;                 ///< Hauteur de la fenêtre.
    int mode;                         ///< Mode de jeu.
    sf::RenderWindow window;          ///< Fenêtre SFML.
    sf::Font font;                    ///< Police principale pour le texte.
    sf::Font font2;                   ///< Deuxième police pour le texte.
    sf::Text playText;                ///< Texte pour l'option "JOUER".
    sf::Text quitText;                ///< Texte pour l'option "QUITTER".
    sf::Text endText;                 ///< Texte pour l'option "End".
    int iterationCount;               ///< Compteur d'itérations.
    Cellule_movible& celluleMovible;  ///< Référence à une cellule mobile.

    /**
     * @brief Dessine la grille de la matrice.
     */
    void drawGrid();

    /**
     * @brief Met à jour la matrice affichée.
     */
    void updateMatrice();

public:
    IHM_Graphique(std::vector<std::vector<bool>>& matrice_ref, Cellule_movible& cellule);

    /**
     * @brief Affichage de la grille dans l'Interface graphique générée. Puis appel de méthodes privées.
     */
    void Aff_graphique() override;
};

#endif // CLASS_H
