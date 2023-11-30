#include "Joueur.h"

Joueur::Joueur() : pseudo(" ")
{
}

Joueur::~Joueur()
{
}

Joueur::Joueur(const Joueur& j) : pseudo(j.pseudo), grille(j.grille), bataille(j.bataille)
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

void Joueur::associerJoueurGrille(Grille* grilleJoueur)
{
    grille = grilleJoueur;
}

void Joueur::associerJoueurBatailleNavale(BatailleNavale* batailleNavaleJoueur)
{
    bataille = batailleNavaleJoueur;
}