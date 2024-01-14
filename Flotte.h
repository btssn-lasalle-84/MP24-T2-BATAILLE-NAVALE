#ifndef FLOTTE_H
#define FLOTTE_H

#include <vector>
#include "Coordonnees.h"
#include "IHM.h"

#define DEBUG_FLOTTE

class Joueur;
class Navire;
class Grille;
class IHM;

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
    Joueur*              getJoueur() const;
    void                 ajouterNavire(Navire*);
    void                 genererNavires(std::vector<std::string>, std::vector<int>, IHM*);
    void                 genererNaviresAleatoirement(std::vector<std::string>, std::vector<int>);
    int                  tirer(Coordonnees coordonnee);
    void                 genererAleatoirement();
};

#endif