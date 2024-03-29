#ifndef NAVIRE_H
#define NAVIRE_H

#include <algorithm>
#include <iostream>
#include <vector>
#include "Grille.h"
#include "Coordonnees.h"
#include "Flotte.h"
#include "IHM.h"

#define DEBUG_NAVIRE
#define CASE_MORTE_COL 0
#define CASE_MORTE_LIG 'X'

class Grille;
class IHM;
class Flotte;

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
    void        setOrientation(const int&);
    void        genererCoordonnees(Coordonnees, int);
    void        gererCreation(int, Coordonnees proue, IHM*, Flotte*);
    void        gererCreationAleatoire(int, Flotte*);
    Coordonnees genererInfosAleatoires(int);
    std::string getNom() const;
    int         getOrientation() const;
    bool        ajouterDegat(Coordonnees);
    bool        estVivant();
    int         getEtat() const;
    bool        estNavireValide(const std::vector<Navire*>&);
};

#endif // NAVIRE_H