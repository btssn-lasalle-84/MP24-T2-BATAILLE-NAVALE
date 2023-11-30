#include "Grille.h"

Grille::Grille() : nbLigne(10), nbColonne(10)
{
}

Grille::~Grille()
{
}

Grille::Grille(const Grille& g) : nbLigne(g.nbLigne), nbColonne(g.nbColonne)
{
}

int Grille::getNbColonne() const
{
    return this->nbColonne;
}

int Grille::getNbLigne() const
{
    return this->nbLigne;
}