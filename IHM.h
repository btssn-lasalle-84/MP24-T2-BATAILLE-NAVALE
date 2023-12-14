#ifndef IHM_H
#define IHM_H
#include <vector>
#include <iostream>
#include "Flotte.h"
#include "Grille.h"
#include "BatailleNavale.h"
#include "Coordonnees.h"
#include "Navire.h"
#include "Joueur.h"

#define BLEU       "\033[0;34m ■"
#define CYAN       "\033[1;36m ■"
#define ROUGE      "\033[1;31m ■"
#define GRIS       "\033[1;30m ■"
#define NB_LIGNE   10
#define NB_COLONNE 10

class BatailleNavale;
class Flotte;
class Grille;
class Navire;
class Joueur;
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
    Flotte      saisirDisposition(Grille*);
    Coordonnees saisirCoup(Grille*);
    bool        estCoupValide(Coordonnees, Grille*);
    void        afficherGrille(Joueur*);
    void        afficherNavire(Grille*, Flotte*);
    void        associerInterfaceBataille(BatailleNavale*);
    void        afficherGrilleBateau(Grille*, std::vector<Navire*>);
    static void afficherAsciiArt();
};

#endif