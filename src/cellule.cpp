#include "../headers/class.h"
using namespace std;

Cellule::Cellule(std::vector<std::vector<bool>>& matrice_ref) : matrice(matrice_ref) {}


void Cellule :: afficherMatrice () {
 if (mode == 1){
  for (const auto& row : matrice) {
   for (const auto& cell : row) {
    std::cout << cell << " "; // Affiche 1 ou 0
   }
   std::cout << std::endl;
  }
  cout << "\n" << endl;
 }
 else {}
}

void Cellule::save_fichier(){
 string file_name = "OUTPUT_out/output.txt";

 if (mode == 1) {

  std::ofstream out(file_name, std::ios::out | std::ios::app);

  if (out) {
   out << colonne << " " << ligne << std::endl;

   for (int i = 0; i < ligne; ++i) {
    for (int j = 0; j < colonne; ++j) {
     out << matrice[i][j];
     if (j < colonne - 1) out << ", "; // Pas de virgule après le dernier élément
    }
    if (i < ligne - 1) out << ","; // Pas de virgule après la dernière ligne
    out << "\n";
   }
   out << "\n" << std::endl;
  }
  else {
   std::cerr << "Impossible de realiser les sauvegardes" <<std::endl;
  }

  out.close();
 }
}

void Cellule ::simulerMatrice ()
{
     for (int t = 1; t < iterations_cell; t++)
   {
     afficherMatrice();
      save_fichier();
     changerEtat();
      Sleep(1000);
   }
}

void Cellule::set_iterations_cell(int iterations) {
 iterations_cell = iterations;
}

void Cellule::set_modes(int mode_settings) {
 mode = mode_settings;
}

void Cellule::set_ligne(int ligne_settings) {
 ligne = ligne_settings;
}

void Cellule::set_colonne(int colonne_settings) {
 colonne = colonne_settings;
}

vector<vector<bool>>& Cellule ::get_matrice_cell()
{ return matrice;}


/**
 * @brief Classe Cellule_movible héritière de Cellule
 */
Cellule_movible::Cellule_movible(std::vector<std::vector<bool>>& matrice_ref) : Cellule(matrice_ref) {}

void Cellule_movible::definirEtat(int x, int y, bool etat)
{
    int lignes = matrice.size();
    int colonnes = matrice[0].size();

    if(x >= 0 && x < lignes  && y >= 0  && y < colonnes )
    {
            matrice[x][y] = etat;
    }

}

void Cellule_movible::changerEtat()
{
 int lignes = matrice.size();
 int colonnes = matrice[0].size();
 // Créez une matrice temporaire pour stocker les nouveaux états
 vector<vector<bool>> temp(lignes, vector<bool>(colonnes, false));

 for (int x = 0; x < lignes; x++) {
  for (int y = 0; y < colonnes; y++) {
   int voisinVivants = 0;

   // Parcourez les 8 voisins
   for (int k = 0; k < 8; k++) {
    int tempX = x, tempY = y;

    switch (k) {
     case 0: tempX = x - 1; tempY = y - 1; break;
     case 1: tempX = x - 1; tempY = y;     break;
     case 2: tempX = x - 1; tempY = y + 1; break;
     case 3: tempX = x;     tempY = y - 1; break;
     case 4: tempX = x;     tempY = y + 1; break;
     case 5: tempX = x + 1; tempY = y - 1; break;
     case 6: tempX = x + 1; tempY = y;     break;
     case 7: tempX = x + 1; tempY = y + 1; break;
    }

    // Vérifiez que les coordonnées sont dans les limites
    if (tempX >= 0 && tempY >= 0 && tempX < lignes && tempY < colonnes) {
     if (matrice[tempX][tempY]) voisinVivants++;
    }
   }

   // Appliquez les règles du jeu
   if (matrice[x][y] == 1) {
    // Cellule vivante : survit si 2 ou 3 voisins
    temp[x][y] = (voisinVivants == 2 || voisinVivants == 3);
   } else {
    // Cellule morte : naît si exactement 3 voisins
    temp[x][y] = (voisinVivants == 3);
   }
  }
 }

 // Remplacez la matrice par le nouvel état
 matrice = temp;
}

