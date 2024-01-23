#include "Grille.h"
#include "Joueur.h"
#include "Flotte.h"
#include "debug.h"

using namespace std;

Grille::Grille(Joueur* joueur) :
    grille(vector<vector<string> >(NB_LIGNE, vector<string>(NB_COLONNE, ""))), joueur(joueur)
{
    for(int i = 0; i < NB_LIGNE; ++i)
    {
        for(int j = 0; j < NB_COLONNE; ++j)
        {
            if((j + i) % 2 == 0)
            {
                grille[i][j] = BLEU;
            }
            else
            {
                grille[i][j] = CYAN;
            }
        }
    }
#ifdef DEBUG_GRILLE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] this = " << this << " "
              << " joueur = " << joueur;
    std::cout << std::endl;
#endif
}

Grille::Grille() :
    grille(vector<vector<string> >(NB_LIGNE, vector<string>(NB_COLONNE, ""))), joueur()
{
    for(int i = 0; i < NB_LIGNE; ++i)
    {
        for(int j = 0; j < NB_COLONNE; ++j)
        {
            if((j + i) % 2 == 0)
            {
                grille[i][j] = BLEU;
            }
            else
            {
                grille[i][j] = CYAN;
            }
        }
    }
#ifdef DEBUG_GRILLE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] this = " << this << " "
              << " joueur = " << joueur;
    std::cout << std::endl;
#endif
}

Grille::~Grille()
{
#ifdef DEBUG_GRILLE
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

Joueur* Grille::getJoueur() const
{
    return joueur;
}

void Grille::appliquerFlotteSurGrille()
{
    for(Navire* navire: joueur->getFlotte()->getFlotte())
    {
        for(pair<Coordonnees, bool> coordonnee: navire->getCoordonnes())
        {
            if(coordonnee.second)
            {
                grille[coordonnee.first.ligne - 'A'][coordonnee.first.colonne - 1] = GRIS;
            }
            else
            {
                grille[coordonnee.first.ligne - 'A'][coordonnee.first.colonne - 1] = ROUGE;
            }
        }
    }
}

void Grille::ajouterCoup(Coordonnees coordonnee, string couleur)
{
    grille[coordonnee.ligne - 'A'][coordonnee.colonne - 1] = couleur;
}
