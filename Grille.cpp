#include "Grille.h"
#include "Joueur.h"

#ifndef DEBUG_GRILLE
#include <iostream>
#endif

using namespace std;

Grille::Grille(Joueur* joueur) : grille(), joueur(joueur)
{
    for(int i = 0; i < NB_LIGNE; ++i)
    {
        for(int j = 0; j < NB_COLONNE; ++j)
        {
            if((j + i) % 2 == 0)
            {
                grille[i][j] = BLEU;
            }
            else if((j + i) % 2 == 1)
            {
                grille[i][j] = CYAN;
            }
        }
    }
#ifndef DEBUG_GRILLE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] this = " << this << " "
              << " joueur = " << joueur;
    std::cout << std::endl;
#endif
}

Grille::~Grille()
{
#ifndef DEBUG_GRILLE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]" << std::endl;
#endif
}

Grille::Grille(const Grille& grilleCopiee) :
    grille(grilleCopiee.grille), joueur(grilleCopiee.joueur)
{
}

std::vector<std::vector<std::string> > Grille::getGrille() const
{
    return grille;
}
