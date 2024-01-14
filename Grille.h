#ifndef GRILLE_H
#define GRILLE_H

#include <vector>
#include <string>

#define DEBUG_GRILLE

#include "Couleurs.h"
#include "Coordonnees.h"

#define NB_LIGNE   10
#define NB_COLONNE 10

class Joueur;
class Navire;
class Flotte;

class Grille
{
  private:
    std::vector<std::vector<std::string> > grille;
    Joueur*                                joueur;

  public:
    Grille(Joueur* joueur);
    Grille();
    ~Grille();
    Grille(const Grille&);
    std::vector<std::vector<std::string> > getGrille() const;
    Joueur*                                getJoueur() const;
    void                                   appliquerFlotteSurGrille();
    void                                   ajouterCoup(Coordonnees, std::string);
};

#endif