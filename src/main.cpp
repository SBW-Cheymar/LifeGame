#include "../headers/class.h"


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

    IHM_Graphique ihm_g(matrice, celluleMovible);
    ihm_g.set_iteration_max(settings.get_iterations());

    IHM_Moniteur ihm_m(matrice, celluleMovible);

    // Indiquer le mode de jeu
    if (settings.get_modes() == 1) {
        std::cout << "Mode de jeu: Simulation de la matrice" << std::endl;
        ihm_m.Aff_graphique();  // Simule sur la matrice partagée
    } else if (settings.get_modes() == 2) {
        std::cout << "Mode de jeu: Affichage graphique" << std::endl;
            ihm_g.Aff_graphique(); // Lancer l'interface graphique
    } else {
        std::cout << "Mode de jeu non reconnu." << std::endl;
    }

    return 0;
}