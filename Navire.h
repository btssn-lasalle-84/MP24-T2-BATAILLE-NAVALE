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
    std::string                                nom;
    int                                        orientation;
    std::vector<std::pair<Coordonnees, bool> > coordonnees;
    unsigned int                               degats;
    bool                                       etat;

  public:
    Navire(std::string, int, std::vector<std::pair<Coordonnees, bool> >);
    Navire();
    Navire(const Navire& n);
    ~Navire();

    std::vector<std::pair<Coordonnees, bool> > getCoordonnes() const;
    void        setCoordonnees(const std::vector<std::pair<Coordonnees, bool> >);
    std::string getNom() const;
    int         getOrientation() const;
    void        ajouterDegat(Coordonnees);
    bool        estMort() const;
    bool        estNavireValide(Grille*, const std::vector<Navire*>, const Navire);
};

#endif