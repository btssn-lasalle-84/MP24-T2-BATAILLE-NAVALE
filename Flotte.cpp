#include "Flotte.h"
#include "Joueur.h"
#include "Navire.h"
#include "Grille.h"
#include "Bateaux.h"
#include "debug.h"
#include <string>
#include <cstdlib>
#include <ctime>

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

void Flotte::genererAleatoirement()
{
    vector<string> nomsBateaux    = LISTE_NOMS_BATEAUX;
    vector<int>    valeursBateaux = LISTE_CASES_BATEAUX;

    this->genererNaviresAleatoirement(nomsBateaux, valeursBateaux);
}

int Flotte::calculerNaviresRestants()
{
    int compte = 0;
    for(Navire* navire: navires)
    {
        compte += navire->estVivant();
    }
    return compte;
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
}

int Flotte::tirer(Coordonnees coordonnee)
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
                if(!navire->estVivant())
                {
                    return 2;
                }
                return 1;
            }
        }
    }

    return 0;
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
}

vector<Navire*> Flotte::getFlotte() const
{
    return navires;
}

void Flotte::setFlotte(vector<Navire*> const navires)
{
    this->navires = navires;
}