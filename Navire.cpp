#include "Navire.h"
#include "Flotte.h"

using namespace std;

Navire::Navire() : nom(" "), orientation(), coordonnees(), degats(), etat()
{
    cout << "Interdit !!!\n";
}

Navire::Navire(string                           nomNavire,
               int                              orientationNavire,
               const vector<pair<Coordonnees, bool> > coordonneesNavire) :

    nom(nomNavire),
    orientation(orientationNavire), coordonnees(coordonneesNavire), degats(0), etat(1){};

Navire::Navire(const Navire& n) :
    nom(n.nom), orientation(n.orientation), coordonnees(n.coordonnees), degats(n.degats),
    etat(n.etat){};

Navire::~Navire(){};

string Navire::getNom() const
{
    return nom;
}

vector<pair<Coordonnees, bool> > Navire::getCoordonnes() const
{
    return coordonnees;
}

void Navire::ajouterDegat(Coordonnees coordonnee)
{
    degats += 1;
}

bool Navire::estNavireValide(Grille*               grille,
                             vector<Navire*> const navires,
                             Navire const          nouveauNavire)
{
    if(this->coordonnees.empty())
    {
        return false;
    }

    if(this->orientation == HORIZONTAL)
    {
        if(!(this->coordonnees.back().first.colonne <= grille->getNbColonne()))
        {
            return false;
        }
    }
    else
    {
        if(!(this->coordonnees.back().first.ligne <= ('A' + grille->getNbLigne())))
        {
            return false;
        }
    }

    for(Navire* navireExistant: navires)
    {
        for(pair<Coordonnees, bool> coordEx: navireExistant->getCoordonnes())
        {
            for(pair<Coordonnees, bool> coordNouveau: nouveauNavire.getCoordonnes())
            {
                if(coordNouveau.first.colonne == coordEx.first.colonne &&
                   coordNouveau.first.ligne == coordEx.first.ligne)
                    return false;
            }
        }
    }

    return true;
}

int Navire::getOrientation() const
{
    return this->orientation;
}