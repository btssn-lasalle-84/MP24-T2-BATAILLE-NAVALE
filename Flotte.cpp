#include "Flotte.h"

using namespace std;

Flotte::Flotte() : flotte(), joueur()
{
}

Flotte::Flotte(const vector<Navire*> flotteNavires, Joueur* flotteJoueur) :
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
    vector<Navire>            navires;
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

        Coordonnees         proue;
        vector<Coordonnees> coordonnees;
        Navire              navire(nom, orientation, coordonnees);

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
                Coordonnees coordonnee;
                coordonnee.colonne = proue.colonne + i;
                coordonnee.ligne   = proue.ligne + i;
                coordonnees.push_back(coordonnee);
            }

        } while(!navire.estNavireValide(grille));

        this->ajouterNavire(&navire);
    }
}

void Flotte::ajouterNavire(Navire* navire)
{
    this->flotte.push_back(navire);
}

void Flotte::associerFlotteJoueur(Joueur* joueurFlotte)
{
    joueur = joueurFlotte;
}