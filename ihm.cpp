#include "class.h"

using namespace std;
using namespace sf;



// Implementation de IHM
IHM::IHM(Settings* s, Grille* g, Cellule* c) : settings(s), grille(g), cellule(c) {}

// Implementation de IHM_Moniteur
IHM_Moniteur::IHM_Moniteur(Settings* s, Grille* g, Cellule* c) : IHM(s, g, c) {}

void IHM_Moniteur::Aff_graphique(RenderWindow& win) {
    for (int j = 0; j < settings->get_ligne(); j++) {
        for (int k = 0; k < settings->get_colonne(); k++) {
            if (cellule->get_matrice_cell()[j][k]) {
                cout << "1";
            } else {
                cout << "0";
            }
        }
        cout << endl;
    }
}

void IHM_Moniteur::Event_Settings() {
    RenderWindow window;
    for (int i = 0; i < settings->get_iterations(); i++) {
        Aff_graphique(window);
        cellule -> simulerMatrice();
    }
    cout << "Le jeu est terminé.";
}

// Implementation de IHM_Graphique
IHM_Graphique::IHM_Graphique(Settings* s, Grille* g, Cellule* c) : IHM(s, g, c) {}

void IHM_Graphique::Aff_graphique(RenderWindow& win) {
    while (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                win.close();
        }

        win.clear(sf::Color::White);

        for (int j = 0; j < settings->get_ligne(); j++) {
            for (int k = 0; k < settings->get_colonne(); k++) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(k * cellSize, j * cellSize);

                if (cellule->get_matrice_cell()[j][k]) {
                    cell.setFillColor(sf::Color::White);
                } else {
                    cell.setFillColor(sf::Color::Black);
                }

                win.draw(cell);
            }
        }

        win.display();
    }
}

void IHM_Graphique::Event_Settings() {
    RenderWindow window(VideoMode(800, 600), "Jeu de la vie");
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i < settings->get_iterations(); i++) {
            Aff_graphique(window);
            cellule -> simulerMatrice();;
        }

        cout << "Le jeu est terminé.";
    }
}