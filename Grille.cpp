#include "Grille.h"
#define NB_LIGNE   10
#define NB_COLONNE 10

Grille::Grille() : nbLigne(NB_LIGNE), nbColonne(NB_COLONNE)
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