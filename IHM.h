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

#define VERSION         1.1
#define ROSE            "\033[1;38;5;200m"
#define BLEU            "\033[48;5;33m  "
#define CYAN            "\033[48;5;75m  "
#define ROUGE           "\033[48;5;196m  "
#define GRIS            "\033[48;5;236m  "
#define BLEU_REGLE      "\033[38;5;153m"
#define VERT            "\033[1;38;5;46m"
#define DEFAUT          "\033[0;5;0m"
#define NB_LIGNE        10
#define NB_COLONNE      10
#define TAILLE_SAISIE_1 3
#define TAILLE_SAISIE_2 4

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
    Coordonnees saisirCoup();
    Coordonnees saisirProue(std::string);
    int         saisirOrientation(std::string, int);
    bool        estCoupValide(Coordonnees);
    void        afficherGrille(Joueur*);
    void        afficherNavire(Grille*, Flotte*);
    void        associerInterfaceBataille(BatailleNavale*);
    void        afficherGrilleBateau(Grille*, std::vector<Navire*>);
    static void afficherAsciiArt();
    void        afficherRegles();
    std::string afficherGrilleVierge();
    void        afficherVersionLogiciel();
};

#endif