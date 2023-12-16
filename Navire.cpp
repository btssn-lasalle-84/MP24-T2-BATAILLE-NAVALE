#include "Navire.h"
#include "Flotte.h"

#ifdef DEBUG_JOUEUR
#include <iostream>
#endif

using namespace std;

Navire::Navire() : nom(" "), orientation(), coordonnees(), degats(), etat()
{
    cout << "Interdit !!!\n";
}

Navire::Navire(string                                 nomNavire,
               int                                    orientationNavire,
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
    return this->coordonnees;
}

void Navire::setCoordonnees(vector<pair<Coordonnees, bool> > coordonneesNavire)
{
    coordonnees = coordonneesNavire;
}

bool Navire::ajouterDegat(Coordonnees coordonnee)
{
    degats += 1;
    for(pair<Coordonnees, bool> coordonneeNavire: coordonnees)
    {
        if(coordonnee.ligne == coordonneeNavire.first.ligne &&
           coordonnee.colonne == coordonneeNavire.first.colonne)
        {
            coordonneeNavire.second = false;
            return true;
            ;
        }
    }
    return false;
}

bool Navire::estNavireValide(Grille* grille, const vector<Navire*>& navires)
{
    if(this->coordonnees.empty())
    {
        return false;
    }

    if(this->orientation == HORIZONTAL)
    {
        if(!(this->coordonnees.back().first.colonne <= grille->getNbColonnes()))
        {
            return false;
        }
    }
    else
    {
        if(!(this->coordonnees.back().first.ligne <= ('A' + grille->getNbLignes())))
        {
            return false;
        }
    }

    for(const Navire* navireExistant: navires)
    {
        for(const pair<Coordonnees, bool>& coordEx: navireExistant->getCoordonnes())
        {
            for(const pair<Coordonnees, bool>& coordNouveau: this->coordonnees)
            {
                if(coordNouveau.first.colonne == coordEx.first.colonne &&
                   coordNouveau.first.ligne == coordEx.first.ligne)
                    return false;
            }
        }
    }

    return true;
}

void Navire::setOrientation(const int& nouvOrientation)
{
    orientation = nouvOrientation;
}

int Navire::getOrientation() const
{
    return orientation;
}