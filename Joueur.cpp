#include "Joueur.h"
#include "Grille.h"
#include "BatailleNavale.h"
#include "Flotte.h"
#include "Bateaux.h"

#ifndef DEBUG_JOUEUR
#include <iostream>
#endif

using namespace std;

Joueur::Joueur() :
    pseudo(" "), grillePrivee(new Grille(this)), grillePublique(new Grille(this)),
    bataille(nullptr), flotte(new Flotte(this))
{
#ifndef DEBUG_JOUEUR
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] this = " << this << " "
              << "pseudo = " << pseudo << " - grille = " << grille << " - bataille = " << bataille
              << " - flotte = " << flotte;
    std::cout << std::endl;
#endif
}

Joueur::~Joueur()
{
    delete grillePrivee;
    delete grillePublique;
    delete flotte;
#ifndef DEBUG_JOUEUR
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]" << std::endl;
#endif
}

Joueur::Joueur(string          pseudoJoueur,
               Grille*         grillePriveeJoueur,
               Grille*         grillePubliqueJoueur,
               BatailleNavale* batailleJoueur,
               Flotte*         flotteJoueur) :
    pseudo(pseudoJoueur),
    grillePrivee(grillePriveeJoueur), grillePublique(grillePubliqueJoueur),
    bataille(batailleJoueur), flotte(flotteJoueur)
{
}

Joueur::Joueur(const Joueur& j) :
    pseudo(j.pseudo), grillePrivee(j.grillePrivee), grillePublique(j.grillePublique),
    bataille(j.bataille), flotte(j.flotte)
{
}

std::string Joueur::getPseudo() const
{
    return pseudo;
}

void Joueur::setPseudo(const std::string nouveauPseudo)
{
    this->pseudo = nouveauPseudo;
}

Grille* Joueur::getGrillePublique() const
{
    return grillePublique;
}

Grille* Joueur::getGrillePrivee() const
{
    return grillePrivee;
}

Flotte* Joueur::getFlotte() const
{
    return flotte;
}

BatailleNavale* Joueur::getBatailleNavale() const
{
    return bataille;
}

void Joueur::associerJoueurBatailleNavale(BatailleNavale* batailleNavaleJoueur)
{
    bataille = batailleNavaleJoueur;
#ifndef DEBUG_JOUEUR
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] this = " << this << " "
              << "pseudo = " << pseudo << " - grille = " << grille << " - bataille = " << bataille
              << " - flotte = " << flotte;
    std::cout << std::endl;
#endif
}

bool Joueur::aPerdu()
{
    int morts = 0;
    for(Navire* navire: flotte->getFlotte())
    {
        morts += (int)navire->getEtat();
    }
    return (morts == (int)flotte->getFlotte().size());
}

Coordonnees Joueur::genererCoordonneeAleatoire()
{
    Coordonnees coo;
    srand(time(NULL));

    coo.colonne = rand() % (NB_COLONNE) + 1;
    coo.ligne   = rand() % (NB_LIGNE + 1) + 'A';

    return coo;
}
