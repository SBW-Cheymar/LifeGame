# Jeu de la Vie

Ce projet implémente le célèbre "Jeu de la Vie" de John Conway. Il s'agit d'une simulation où des cellules vivantes et mortes évoluent selon des règles spécifiques basées sur leur état et celui de leurs voisines.
Les cellules placées dans une grille rectangulaire deux dimensionnelle sont caractérisées par deux états ; elles sont soit vivantes, soit mortes. 
A l’exclusion des bordures, le voisinage d’une cellule est formé par 8 autres cellules directement adjacentes. 

Pour passer de l’itération t à l’itération t+1, l’état des cellules dans la grille est actualisé selon les règles suivantes :
- Une cellule morte possédant exactement trois voisines vivantes devient vivante.
- Une cellule vivante possédant deux ou trois voisines vivantes reste vivante, sinon elle meurt.

Nous vous proposerons une implémentation en C++ (en programmation orientée objet) de ce Jeu emblématique.

## Table des matières

- [Fonctionnalités](#fonctionnalités)
- [Prérequis](#prérequis)
- [Installation](#installation)
- [Utilisation](#utilisation)
- [Structure du projet](#structure-du-projet)
- [Contributions](#contributions)
- [Licence](#licence)

## Fonctionnalités

- Chargement de la configuration à partir d'un fichier JSON.
- Modes de jeu : Console et Graphique.
- Simulation de l'évolution des cellules selon les règles du Jeu de la Vie.
- Interface graphique utilisant SFML.

## Prérequis

Avant de commencer, assurez-vous d'avoir installé les éléments suivants :

- Un compilateur C++ (g++ ou clang++)
- CMake (pour la gestion de projet)
- [SFML](https://www.sfml-dev.org/) (pour l'interface graphique)
- [nlohmann/json](https://github.com/nlohmann/json) (pour la gestion des fichiers JSON)

## Installation

1. **Clonez le dépôt :**

   ```bash
   git clone https://github.com/votre-utilisateur/jeu-de-la-vie.git
   cd jeu-de-la-vie

2. **Installer SFML :**

   - Linux : sudo apt-get install libsfml-dev
   - macOS : brew install sfml
   - Widnows : https://www.sfml-dev.org/download/sfml/2.6.2/index-fr.php

3. **Installer la bibliothèque nlohmann/json :**
   - Avec vcpkg : vcpkg install nlohmann-json
   - Depuis le dépôt GitHUB et placez-le dans le dossier 'libs/nlohmann/include/'.

4. Construisez le projet :
  mkdir build
  cd build
  cmake ..
  make

## Utilisation
1. **Lancez le programme :**
   ./jeu_de_la_vie

2. **Choisissez votre mode de jeu :
    1) Mode Console : Affiche la simulation dans la console
    2) Mode Graphique : Affiche une interface graphique pour interagir avec le jeu

3. **Configuration : **
   - Avec un fichier de configuration JSON pour définir la taile de la grille et l'état intial des cellules. Comme le modèle suivant :
   ```json
{
  "iterations_max": 420,
  "gridWidth": 5,
  "gridHeight": 4,
  "gridData": [
    [0, 1, 0, 1, 0],
    [1, 0, 1, 0, 1],
    [0, 1, 0, 1, 0],
    [1, 0, 1, 0, 1]
  ]
}

   - Sans fichier de configuration, le système vous propose d'en créer un de manière très rapide, en saisissant simplement les informations.
  

  ## Structure du Projet 

.
├── src
│   ├── cellule.cpp
│   ├── game.cpp
│   ├── ihm.cpp
│   └── main.cpp
│  
├── headers
│   └── class.h
├── libs
│   └── nlohmann
│       └── include
│           └── nlohmann
│               └── json.hpp
└── assets
    ├── Mandelio Di Paedre.ttf
    ├── gamelife.png
    └── gamelifei.png

  ## Contributions 
Les contributions sont les bienvenues ! N'hésitez à soumettre de pull requests ou à signaler les problèmes.


 ## Licence
Ce projet est réalisé dans le cadre du bloc programmation orientée objet au CESI, il est donc une propriété intellectuelle du CESI, ainsi que des développeurs de ce programme eux-même.
