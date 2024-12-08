#include "../headers/class.h"

void IHM::set_iteration_max(int it_max) {
    iteration_max = it_max;
}

IHM_Moniteur::IHM_Moniteur(std::vector<std::vector<bool>>& matrice_ref, Cellule_movible& cellule)
    : IHM(matrice_ref), celluleMovible(cellule){}

void IHM_Moniteur::Aff_graphique() {
    celluleMovible.simulerMatrice();
}


IHM_Graphique::IHM_Graphique(std::vector<std::vector<bool>>& matrice_ref, Cellule_movible& cellule)
    : IHM(matrice_ref),
      celluleMovible(cellule), // Utilisation de l'objet passé en paramètre
      window(sf::VideoMode(Width, Height), "Jeu de la Vie"), // Création de la fenêtre
      mode(0) // Initialisation du mode
{
    // Chargement de la police
    if (!font.loadFromFile("assets/Mandelio Di Paedre.ttf")) {
        std::cerr << "Erreur de chargement de la police" << std::endl;
    }

    // Configuration du texte "Jouer"

    playText.setScale(1.0f, 1.0f);
    playText.setFont(font);
    playText.setString("Jouer");
    playText.setCharacterSize(70);
    playText.setFillColor(sf::Color::Black);
    playText.setPosition(Width/2.5, Height/1.5);

    // Configuration du texte "Quitter"
    quitText.setScale(1.0f, 1.0f);
    quitText.setFont(font);
    quitText.setString("Quitter");
    quitText.setCharacterSize(70);
    quitText.setFillColor(sf::Color::Black);
    quitText.setPosition(Width/2.8, Height/1.2);
}

void IHM_Graphique::drawGrid() {
    float cellSizeX = (Width*1.05) / matrice_ref[0].size();
    float cellSizeY = (Height*1.05) / matrice_ref.size();

    for (size_t i = 0; i < matrice_ref.size(); ++i) {
        for (size_t j = 0; j < matrice_ref[i].size(); ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSizeX, cellSizeY));
            cell.setPosition(j * cellSizeX, i * cellSizeY);
            cell.setFillColor(matrice_ref[i][j] ? sf::Color::White : sf::Color::Black);
            window.draw(cell);
        }
    }
}

void IHM_Graphique::updateMatrice() {
    // Synchroniser la matrice de l'interface graphique avec celle de Cellule_movible
    // Appeler la méthode changerEtat pour mettre à jour la matrice
        if (mode == 1) {
            celluleMovible.changerEtat();
        }
}

void IHM_Graphique::Aff_graphique() {
    iterationCount = 0; // Initialiser le compteur d'itérations

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2u windowSize = window.getSize();
                    float scaleX = static_cast<float>(windowSize.x) / Width;
                    float scaleY = static_cast<float>(windowSize.y) / Height;

                    float normalizedMouseX = event.mouseButton.x / scaleX;
                    float normalizedMouseY = event.mouseButton.y / scaleY;

                    if (playText.getGlobalBounds().contains(normalizedMouseX, normalizedMouseY)) {
                        mode = 1; // Démarrer le jeu
                    }
                    if (quitText.getGlobalBounds().contains(normalizedMouseX, normalizedMouseY)) {
                        window.close(); // Quitter le jeu
                    }
                }
            }
        }

        window.clear();

        // Setup de l'icon du jeu
        auto icon = sf::Image();
        icon.loadFromFile("assets/gamelifei.png");
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        if (mode == 0) { // Menu d'accueil
            window.setVerticalSyncEnabled(true);
            sf::Texture t;
            t.loadFromFile("assets/gamelife.png");
            sf::Sprite s(t);
            s.setScale(float(Width)/1792, float(Height)/1024);
            window.draw(s);
            window.draw(playText);
            window.draw(quitText);
        } else if (mode == 1) { // Jeu
            window.setVerticalSyncEnabled(true);
            drawGrid();
            updateMatrice(); // Met à jour la matrice
            iterationCount++; // Incrémente le compteur d'itérations

            // Vérifiez si le nombre d'itérations a atteint le maximum
            if (iterationCount >= iteration_max) {
                std::cout << "\n Nombre maximum d'iterations atteint." << std::endl;
                afficherEcranFin(); // Appeler l'écran de fin
                window.close();
                exit(0);
            }
        }
        window.display();

        // Pause pour la mise à jour de la matrice
        if (mode == 1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Ajustez la durée pour la fluidité
        }
    }
}

void IHM_Graphique::afficherEcranFin() {
    // Créer un rectangle noir semi-transparent
    sf::RectangleShape background(sf::Vector2f(Width, Height));
    background.setFillColor(sf::Color(0, 0, 0, 200)); // Fond Noir avec 78% de transparence

    // Afficher le rectangle de fond
    window.draw(background);

    // Afficher le texte de fin
    font2.loadFromFile("assets/pricedown bl.ttf");
    sf::Text endText("WASTED.", font2, 80);
    endText.setFillColor(sf::Color::Red);
    endText.setPosition(Width / 3, Height / 5);
    window.draw(endText);

    // Afficher un message pour quitter
    sf::Text endingText(" Iterations max atteinte | Press Echap pour quitter.", font2, 30);
    endingText.setFillColor(sf::Color::Red);
    endingText.setPosition(Width / 8, Height / 2);
    window.draw(endingText);

    window.display();

    // Attendre que l'utilisateur appuie sur Échap pour quitter
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }
    }
}
