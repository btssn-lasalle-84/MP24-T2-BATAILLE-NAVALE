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
#define VERSION 1.1

#ifndef COULEUR
#define COULEUR
#define ROSE       "\033[1;38;5;200m"
#define BLEU       "\033[48;5;33m  "
#define CYAN       "\033[48;5;75m  "
#define ROUGE      "\033[48;5;196m  "
#define GRIS       "\033[48;5;236m  "
#define BLEU_REGLE "\033[38;5;153m"
#define VERT       "\033[1;38;5;46m"
#define DEFAUT     "\033[0;5;0m"
#endif

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
    void        saisirDisposition(Flotte* flotte);
    Coordonnees saisirCoup();
    Coordonnees saisirProue(std::string);
    Coordonnees formaterSaisie(std::string);
    int         saisirOrientation(std::string, int);
    bool        estCoupValide(Coordonnees);
    void        gestionCoup(bool);
    void        afficherFlotte(Joueur*);
    void        afficherGrilleFlotte(Joueur*, std::vector<std::vector<std::string> >&);
    void        genererFondGrille(std::vector<std::vector<std::string> >&);
    void        ajouterNaviresGrille(Joueur*, std::vector<std::vector<std::string> >&);
    void        afficherLigneGrille(std::vector<std::string>&);
    void        associerInterfaceBataille(BatailleNavale*);
    void        afficherGrille(Joueur*);
    static void afficherAsciiArt();
    void        afficherRegles();
    void        afficherGrilleVierge();
    void        afficherVersionLogiciel();
    static void clearTerminal();
    void        jeuJoueur();
    void        jeuMachine();
    Coordonnees genererCoordonneesAleatoires();
};

#endif