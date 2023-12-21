#ifndef GRILLE_H
#define GRILLE_H

#include <vector>

//#define DEBUG_GRILLE

#define NB_LIGNE   10
#define NB_COLONNE 10

class Joueur;

class Grille
{
  private:
    int     nbLignes;
    int     nbColonnes;
    Joueur* joueur;

  public:
    Grille(Joueur* joueur);
    ~Grille();
    Grille(const Grille&, Joueur*);

    int getNbLignes() const;
    int getNbColonnes() const;
};

#endif