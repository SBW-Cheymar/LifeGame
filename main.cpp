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

    if(settings.get_modes() == 1) {
        celluleMovible.afficherMatrice(); // Affiche la matrice partagée
        celluleMovible.simulerMatrice();  // Simule sur la matrice partagée
    } else if(settings.get_modes() == 2) {
        // Créer une instance de la fenêtre graphique
        sf::RenderWindow window(sf::VideoMode(800, 600), "Jeu de la vie");
        IHM_Graphique ihm_graphique(&settings, nullptr, &celluleMovible);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            ihm_graphique.Aff_graphique(window); // Affiche la matrice sur l'interface graphique
            celluleMovible.simulerMatrice(); // Simule sur la matrice partagée
        }
    }

    return 0;
}