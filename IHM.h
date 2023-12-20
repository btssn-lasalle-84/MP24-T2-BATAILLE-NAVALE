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

#define BLEU       "\033[48;5;33m  "
#define CYAN       "\033[48;5;75m  "
#define ROUGE      "\033[48;5;196m  "
#define GRIS       "\033[48;5;236m  "
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