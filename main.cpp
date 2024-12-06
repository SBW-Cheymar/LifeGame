#include "class.h"

int main() {
    Settings settings;
    settings.lire_fichier(); // Charge la matrice
    settings.get_iterations();
    settings.choix_modes();

    std::vector<std::vector<bool>>& matrice = settings.get_matrice();

    Cellule_movible celluleMovible(matrice);

    celluleMovible.set_iterations_cell(settings.get_iterations());
    celluleMovible.set_modes(settings.get_modes());
    celluleMovible.set_ligne(settings.get_ligne());
    celluleMovible.set_colonne(settings.get_colonne());

    celluleMovible.afficherMatrice(); // Affiche la matrice partagée
    celluleMovible.simulerMatrice();  // Simule sur la matrice partagée
}