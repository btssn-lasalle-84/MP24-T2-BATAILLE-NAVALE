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

#define BLEU       "\033[1;34;46m  "
#define CYAN       "\033[1;36;44m  "
#define ROUGE      "\033[1;41;33m  "
#define GRIS       "\033[1;40;39m  "
#define DEFAUT     "\033[0;39;49m"
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
    void        saisirDisposition(Grille*, Flotte* flotte);
    Coordonnees saisirCoup(Grille*);
    Coordonnees saisirProue(Grille*, std::string);
    int         saisirOrientation(Grille*, std::string, int);
    bool        estCoupValide(Coordonnees, Grille*);
    void        afficherGrille(Joueur*);
    void        afficherNavire(Grille*, Flotte*);
    void        associerInterfaceBataille(BatailleNavale*);
    void        afficherGrilleBateau(Grille*, std::vector<Navire*>);
    static void afficherAsciiArt();
};

#endif