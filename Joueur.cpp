#include "Joueur.h"
#include "Grille.h"
#include "BatailleNavale.h"
#include "Flotte.h"

#ifndef DEBUG_JOUEUR
#include <iostream>
#endif

using namespace std;

Joueur::Joueur() :
    pseudo(" "), grille(new Grille(this)), bataille(nullptr), flotte(new Flotte(this))
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
    delete grille;
    delete flotte;
#ifndef DEBUG_JOUEUR
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]" << std::endl;
#endif
}

Joueur::Joueur(string          pseudoJoueur,
               Grille*         grilleJoueur,
               BatailleNavale* batailleJoueur,
               Flotte*         flotteJoueur) :
    pseudo(pseudoJoueur),
    grille(grilleJoueur), bataille(batailleJoueur), flotte(flotteJoueur)
{
}

Joueur::Joueur(const Joueur& j) :
    pseudo(j.pseudo), grille(j.grille), bataille(j.bataille), flotte(j.flotte)
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

Grille* Joueur::getGrille() const
{
    return grille;
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
