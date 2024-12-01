Le jeu de la vie désigne un automate cellulaire proposé par le mathématicien John Conway. 
Il décrit l’évolution d’une population de cellules sur un intervalle de temps discret. 

Les cellules placées dans une grille rectangulaire deux dimensionnelle sont caractérisées par deux états ; elles sont soit vivantes, soit mortes. 
A l’exclusion des bordures, le voisinage d’une cellule est formé par 8 autres cellules directement adjacentes. 

Pour passer de l’itération t à l’itération t+1, l’état des cellules dans la grille est actualisé selon les règles suivantes :
- Une cellule morte possédant exactement trois voisines vivantes devient vivante.
- Une cellule vivante possédant deux ou trois voisines vivantes reste vivante, sinon elle meurt.

Nous vous proposerons une implémentation en C++ (en programmation orientée objet) de ce Jeu emblématique.
