#include "Flotte.h"
#include "Joueur.h"
#include "Navire.h"
#include "Grille.h"

#include <string>
#include <cstdlib>
#include <ctime>

#ifdef DEBUG_FLOTTE
#include <iostream>
#endif

using namespace std;

Flotte::Flotte(Joueur* joueur) : navires(), joueur(joueur)
{
#ifdef DEBUG_FLOTTE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] this = " << this << " "
              << "nb navires = " << navires.size() << " - joueur = " << joueur;
    std::cout << std::endl;
#endif
}

Flotte::Flotte(vector<Navire*> const flotteNavires, Joueur* flotteJoueur) :
    navires(flotteNavires), joueur(flotteJoueur)
{
}

Flotte::Flotte(const Flotte& f) : navires(f.navires), joueur(f.joueur)
{
}

Flotte::~Flotte()
{
#ifdef DEBUG_FLOTTE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]" << std::endl;
#endif
}

void Flotte::genererAleatoirement(Grille* grille)
{
    srand(time(NULL));
    vector<Navire*> navires;
    vector<string>  nomBateaux     = { "Porte-Avion",
                                  "Croiseur",
                                  "Contre-torpilleur",
                                  "Sous-marin",
                                  "Torpilleur" };
    vector<int>     valeursBateaux = { 5, 4, 3, 3, 2 };

    for(size_t i = 0; i < nomBateaux.size(); ++i)
    {
        int          orientation = HORIZONTAL;
        string       nom         = nomBateaux[i];
        unsigned int nbCases     = valeursBateaux[i];

        Coordonnees                      proue;
        vector<pair<Coordonnees, bool> > coordonnees;
        Navire                           navire(nom, orientation, coordonnees);

        bool navireInvalide = true;
        while(navireInvalide)
        {
            int orientation = rand() % 2;
            navire.setOrientation(orientation);
            coordonnees.clear();

            if(orientation == HORIZONTAL)
            {
                proue.colonne = rand() % (grille->getNbColonnes() - nbCases + 1) + 1;
                proue.ligne   = rand() % (grille->getNbLignes()) + 'A';
            }
            else
            {
                proue.colonne = rand() % (grille->getNbColonnes()) + 1;
                proue.ligne   = rand() % (grille->getNbLignes() - nbCases + 1) + 'A';
            }

            for(unsigned int j = 0; j < nbCases; ++j)
            {
                pair<Coordonnees, bool> coordonnee;
                coordonnee.first.colonne = proue.colonne + (j * (1 - orientation));
                coordonnee.first.ligne   = proue.ligne + (j * orientation);
                coordonnee.second        = true;
                coordonnees.push_back(coordonnee);
            }

            navire.setCoordonnees(coordonnees);

#ifdef DEBUG_FLOTTE
            std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] "
                      << "orientation = " << orientation << " - proue = " << proue.ligne << ":"
                      << proue.colonne;
            std::cout << std::endl;
            for(int j = 0; j < (int)coordonnees.size(); ++j)
            {
                std::cout << coordonnees[j].first.ligne << ":" << coordonnees[j].first.colonne
                          << " ";
            }
            std::cout << std::endl;
#endif

            if(navire.estNavireValide(grille, navires))
            {
                navireInvalide = false;
                navires.push_back(new Navire(navire)); // Copie le navire dans le vecteur
            }
        }
    }

#ifdef DEBUG_FLOTTE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] "
              << "nb navires = " << navires.size() << std::endl;

#endif

    this->setFlotte(navires);
}

bool Flotte::tirer(Coordonnees coordonnee)
{
    for(Navire* navire: navires)
    {
        for(unsigned int i = 0; i < navire->getCoordonnes().size(); ++i)
        {
            if(coordonnee.colonne == navire->getCoordonnes()[i].first.colonne &&
               coordonnee.ligne == navire->getCoordonnes()[i].first.ligne &&
               navire->getCoordonnes()[i].second == true)
            {
                navire->ajouterDegat(coordonnee);
                return true;
            }
        }
    }

    return false;
}

vector<Navire*> Flotte::getFlotte() const
{
    return navires;
}

void Flotte::setFlotte(vector<Navire*> const navires)
{
    this->navires = navires;
}