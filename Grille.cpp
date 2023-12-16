#include "Grille.h"
#include "Joueur.h"

#ifdef DEBUG_GRILLE
#include <iostream>
#endif

Grille::Grille(Joueur* joueur) : nbLignes(NB_LIGNE), nbColonnes(NB_COLONNE), joueur(joueur)
{
#ifdef DEBUG_GRILLE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] this = " << this << " "
              << "nbLignes = " << nbLignes << " - nbColonnes = " << nbColonnes
              << " - joueur = " << joueur;
    std::cout << std::endl;
#endif
}

Grille::~Grille()
{
#ifdef DEBUG_GRILLE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]" << std::endl;
#endif
}

Grille::Grille(const Grille& g, Joueur* grilleJoueur) :
    nbLignes(g.nbLignes), nbColonnes(g.nbColonnes), joueur(grilleJoueur)
{
}

int Grille::getNbColonnes() const
{
    return this->nbColonnes;
}

int Grille::getNbLignes() const
{
    return this->nbLignes;
}
