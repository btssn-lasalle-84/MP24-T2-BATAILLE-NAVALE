#ifndef IHM_H
#define IHM_H
#include <vector>
#include <iostream>
#include "Flotte.h"
#include "Grille.h"
#include "BatailleNavale.h"

class BatailleNavale;
class Flotte;
class Grille;
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
    Flotte saisirDisposition();
    Coordonnees saisirCoup();
    void afficherGrille(Grille*);
    void associerInterfaceBataille(BatailleNavale*);
};

#endif