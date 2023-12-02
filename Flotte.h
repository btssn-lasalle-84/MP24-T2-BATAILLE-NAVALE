#ifndef FLOTTE_H
#define FLOTTE_H
#include <vector>

class Joueur;
class Navire;

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

    void ajouterNavire(Navire*);
    void associerFlotteJoueur(Joueur*);
};

#endif