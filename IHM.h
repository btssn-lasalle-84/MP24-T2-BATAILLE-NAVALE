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
#include "Couleurs.h"

#define VERSION 2.0

#define NB_LIGNE           10
#define NB_COLONNE         10
#define TAILLE_SAISIE_1    3
#define TAILLE_SAISIE_2    4
#define LIGNES_A_CONSERVER 32

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
    void        saisirDisposition(Flotte* flotte);
    Coordonnees saisirCoup();
    void        inviterASaisir();
    Coordonnees saisirProue(std::string);
    Coordonnees formaterSaisie(std::string);
    int         saisirOrientation(std::string, int);
    bool        estCoupValide(Coordonnees);
    bool        gererCoup(Joueur*, Coordonnees, Joueur*);
    void        afficherLigneGrille(std::vector<std::string>&);
    void        associerInterfaceBataille(BatailleNavale*);
    void        afficherGrille(Grille*);
    void        afficherNaviresRestants(Joueur*);
    void        afficherSeparateur();
    void        afficherJeu(Joueur*, Joueur*);
    static void afficherAsciiArt();
    void        afficherRegles();
    void        afficherGrilleVierge();
    void        afficherVersionLogiciel();
    void        afficherVainqueur(Joueur*);
    static void effacerTerminal();
    void        dormir(int);
};

#endif // IHM_H