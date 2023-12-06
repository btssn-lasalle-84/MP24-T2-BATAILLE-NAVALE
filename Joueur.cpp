#include "Joueur.h"

using namespace std;

Joueur::Joueur() : pseudo(" ")
{
}

Joueur::~Joueur()
{
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

void Joueur::associerJoueurGrille(Grille* grilleJoueur)
{
    grille = grilleJoueur;
}

void Joueur::associerJoueurBatailleNavale(BatailleNavale* batailleNavaleJoueur)
{
    bataille = batailleNavaleJoueur;
}

void Joueur::associerJoueurFlotte(Flotte* flotteJoueur)
{
    flotte = flotteJoueur;
}