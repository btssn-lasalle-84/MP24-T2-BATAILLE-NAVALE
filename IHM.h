#ifndef IHM_H
#define IHM_H
#include <vector>
#include <iostream>
#include "Flotte.h"
#include "Grille.h"
#include "BatailleNavale.h"
#include "Coordonnees.h"
#include "Navire.h"

class BatailleNavale;
class Flotte;
class Grille;
class Navire;
struct Coordonnees;

class IHM
{
  private:
    BatailleNavale* bataille;

  public:
    IHM();
    IHM(BatailleNavale*);
    IHM(const IHM&);
    ~IHM();

    std::string saisirJoueur();
    Flotte      saisirDisposition(Grille*, Joueur*);
    Coordonnees saisirCoup(Grille*);
    bool        estCoupValide(Coordonnees, Grille*);
    void        afficherGrille(Grille*);
    void        associerInterfaceBataille(BatailleNavale*);
};

#endif