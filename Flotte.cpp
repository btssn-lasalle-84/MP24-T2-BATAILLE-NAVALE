#include "Flotte.h"

using namespace std;

Flotte::Flotte() : flotte(), joueur()
{
}

Flotte::Flotte(vector<Navire*> const flotteNavires, Joueur* flotteJoueur) :
    flotte(flotteNavires), joueur(flotteJoueur)
{
}

Flotte::Flotte(const Flotte& f) : flotte(f.flotte), joueur(f.joueur)
{
}

Flotte::~Flotte()
{
}

void Flotte::genererAleatoirement(Grille* grille)
{
    srand(time(NULL));
    vector<Navire*>           navires;
    map<string, unsigned int> bateaux{ { "Porte-avion", 5 },
                                       { "Croiseur", 4 },
                                       { "Contre-torpilleur", 3 },
                                       { "Sous-marin", 3 },
                                       { "Torpilleur", 2 } };

    for(map<string, unsigned int>::iterator it = bateaux.begin(); it != bateaux.end(); ++it)
    {
        int          orientation = rand() % 2;
        string       nom         = it->first;
        unsigned int nbCases     = it->second;

        Coordonnees                      proue;
        vector<pair<Coordonnees, bool> > coordonnees;
        Navire                           navire(nom, orientation, coordonnees);

        do
        {
            if(orientation == 0)
            {
                proue.colonne = rand() % (grille->getNbColonne() - nbCases) + 1;
                proue.ligne   = rand() % (grille->getNbLigne()) + 1;
            }
            else
            {
                proue.colonne = rand() % (grille->getNbColonne()) + 1;
                proue.ligne   = rand() % (grille->getNbLigne() - nbCases) + 1;
            }

            for(unsigned int i = 0; i < nbCases; ++i)
            {
                pair<Coordonnees, bool> coordonnee;
                coordonnee.first.colonne = proue.colonne + i;
                coordonnee.first.ligne   = proue.ligne + i;
                coordonnee.second        = true;
                coordonnees.push_back(coordonnee);
            }

        } while(!navire.estNavireValide(grille, navires, navire));

        navires.push_back(&navire);
    }

    this->setFlotte(navires);
}

bool Flotte::tirer(Coordonnees coordonnee)
{
    for(Navire* navire: this->getFlotte())
    {
        for(unsigned int i = 0; i < navire->getCoordonnes().size(); ++i)
        {
            if(coordonnee.colonne == navire->getCoordonnes()[i].first.colonne &&
               coordonnee.ligne == navire->getCoordonnes()[i].first.ligne)
            {
                navire->ajouterDegat(navire->getCoordonnes()[i].first);
                navire->getCoordonnes()[i].second = false;
                return true;
            }
        }
    }

    return false;
}

void Flotte::associerFlotteJoueur(Joueur* joueurFlotte)
{
    joueur = joueurFlotte;
}

void Flotte::setFlotte(vector<Navire*> const navires)
{
    flotte = navires;
}