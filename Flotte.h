#ifndef FLOTTE_H
#define FLOTTE_H
#include <vector>
#include <map>
#include <stdlib.h>
#include <time.h>
#include "Coordonnees.h"
#include "Navire.h"

class Joueur;
class Navire;
class Grille;

class Flotte
{
  private:
    std::vector<Navire*> flotte;
    Joueur*              joueur;

  public:
    Flotte();
    Flotte(const std::vector<Navire*>, Joueur*);
    Flotte(const Flotte&);
    ~Flotte();

    std::vector<Navire*> getFlotte();
    void                 setFlotte(const std::vector<Navire*>);
    void                 genererAleatoirement(Grille*);
    void                 associerFlotteJoueur(Joueur*);
};

#endif