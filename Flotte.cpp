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
    vector<string> nomsBateaux    = { "Porte-Avion",
                                      "Croiseur",
                                      "Contre-torpilleur",
                                      "Sous-marin",
                                      "Torpilleur" };
    vector<int>    valeursBateaux = { 5, 4, 3, 3, 2 };

    this->genererNaviresAleatoirement(nomsBateaux, valeursBateaux);
}

void Flotte::genererNaviresAleatoirement(vector<string> nomsBateaux, vector<int> valeursBateaux)
{
    for(int i = 0; i < (int)nomsBateaux.size(); ++i)
    {
        int                              orientation = HORIZONTAL;
        string                           nom         = nomsBateaux[i];
        vector<pair<Coordonnees, bool> > coordonnees;
        Navire                           navire(nom, orientation, coordonnees);
        navire.gererCreationAleatoire(valeursBateaux[i], this);
    }

#ifdef DEBUG_FLOTTE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] "
              << "orientation = " << orientation << " - proue = " << proue.ligne << ":"
              << proue.colonne;
    std::cout << std::endl;
    for(int j = 0; j < (int)coordonnees.size(); ++j)
    {
        std::cout << coordonnees[j].first.ligne << ":" << coordonnees[j].first.colonne << " ";
    }
    std::cout << std::endl;
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

Joueur* Flotte::getJoueur() const
{
    return joueur;
}

void Flotte::ajouterNavire(Navire* navire)
{
    navires.push_back(navire);
}

void Flotte::genererNavires(std::vector<std::string> nomsBateaux,
                            std::vector<int>         valeursBateaux,
                            IHM*                     interface)
{
    for(int i = 0; i < (int)nomsBateaux.size(); i++)
    {
        int         orientation = interface->saisirOrientation(nomsBateaux[i], valeursBateaux[i]);
        Coordonnees proue       = interface->saisirProue(nomsBateaux[i]);
        vector<pair<Coordonnees, bool> > coordonnees;
        Navire                           navire(nomsBateaux[i], orientation, coordonnees);

        navire.gererCreation(valeursBateaux[i], proue, interface, this);
    }

    cout << "Tous les bateaux sont définis" << endl;
}

vector<Navire*> Flotte::getFlotte() const
{
    return navires;
}

void Flotte::setFlotte(vector<Navire*> const navires)
{
    this->navires = navires;
}