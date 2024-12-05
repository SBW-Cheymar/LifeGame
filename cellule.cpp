#include <chrono>
#include <thread>
#include "class.h"
using namespace std;


Cellule::Cellule(std::vector<std::vector<bool>>& matrice_ref) : matrice(matrice_ref) {}


vector<vector<bool>>& Cellule ::get_matrice_cell()
 { return matrice;}

void Cellule::set_iterations_max() {
 Settings s;
 iterations_cell = s.get_iterations();
}


void Cellule :: afficherMatrice ()
{
      for (const auto& lignes : matrice )
    {
        for (int j : lignes)
        {
            cout << j << " ";
        }
        cout << endl;
   }
   cout << endl;
}

void Cellule ::simulerMatrice ()
{
     for (int t = 0; t < 20; t++)
   {
     system("CLS"); 
     afficherMatrice();
     changerEtat();
    this_thread::sleep_for(chrono::milliseconds(1000));
   }

}


///////////////////////////////////////////////////////////////////////////

Cellule_movible::Cellule_movible(std::vector<std::vector<bool>>& matrice_ref) : Cellule(matrice_ref) {}


void  Cellule_movible :: definirEtat(int x, int y, bool etat)
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
   int voisinVivvants = 0;

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
     if (matrice[tempX][tempY]) voisinVivvants++;
    }
   }

   // Appliquez les règles du jeu
   if (matrice[x][y] == 1) {
    // Cellule vivante : survit si 2 ou 3 voisins
    temp[x][y] = (voisinVivvants == 2 || voisinVivvants == 3);
   } else {
    // Cellule morte : naît si exactement 3 voisins
    temp[x][y] = (voisinVivvants == 3);
   }
  }
 }

 // Remplacez la matrice par le nouvel état
 matrice = temp;
}

/////////////////////////////////////////////////////////////////////////

Cellule_Obstacle::Cellule_Obstacle(std::vector<std::vector<bool>>& matrice_ref) : Cellule(matrice_ref) {}

void  Cellule_Obstacle :: definirEtat(int x, int y, bool etat)
{
    int lignes = matrice.size();
    int colonnes = matrice[0].size();
    
    if(x >= 0 && x < lignes  && y >= 0  && y < colonnes )
    {
            matrice[x][y] = etat;
    }

}


void Cellule_Obstacle :: changerEtat()
{
   int lignes = matrice.size();
    int colonnes = matrice[0].size();

    vector<vector<bool>> temp(lignes, vector<bool>(colonnes, false));
    
    for(int x = 0; x < lignes ; x++)
    {
        for (int y = 0; y < colonnes; y++)
        {
           
         if (matrice[x][y] == 0 )
         {
            temp[x][y] = 0 ; 
         } else if (matrice[x][y] == 1){
              temp[x][y] = 1 ; 
         }
      

        }

    }

 matrice = temp;
}
 






