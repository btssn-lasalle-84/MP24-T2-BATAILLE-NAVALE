#ifndef NAVIRE_H
#define NAVIRE_H
#include <algorithm>
#include <iostream>
#include <vector>
#include "Grille.h"
#include "Coordonnees.h"
#include "Flotte.h"

#define CASE_MORTE_COL 0
#define CASE_MORTE_LIG 'X'

class Grille;

enum orientation
{
    HORIZONTAL = 0,
    VERTICAL   = 1
};

class Navire
{
  private:
    std::string              nom;
    int                      orientation;
    std::vector<Coordonnees> coordonnees;
    unsigned int             degats;
    bool                     etat;

  public:
    Navire(std::string, int, std::vector<Coordonnees>);
    Navire();
    Navire(const Navire& n);
    ~Navire();

    std::vector<Coordonnees> getCoordonnes() const;
    std::string              getNom() const;
    bool                     ajouterDegat(Coordonnees);
    bool                     estMort() const;
    bool                     estNavireValide(Grille*, Flotte*, Navire*);
};
#endif