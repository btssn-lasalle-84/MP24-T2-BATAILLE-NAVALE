#ifndef FLOTTE_H
#define FLOTTE_H

#include <vector>
#include "Coordonnees.h"

#define DEBUG_FLOTTE

class Joueur;
class Navire;
class Grille;

class Flotte
{
  private:
    std::vector<Navire*> navires;
    Joueur*              joueur;

  public:
    Flotte(Joueur* joueur);
    Flotte(const std::vector<Navire*>, Joueur*);
    Flotte(const Flotte&);
    ~Flotte();

    std::vector<Navire*> getFlotte() const;
    void                 setFlotte(const std::vector<Navire*>);
    bool                 tirer(Coordonnees coordonnee);
    void                 genererAleatoirement(Grille*);
};

#endif