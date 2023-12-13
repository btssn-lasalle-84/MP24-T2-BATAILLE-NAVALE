#include "Navire.h"
#include "Flotte.h"

using namespace std;

Navire::Navire() : nom(" "), orientation(), coordonnees(), degats(), etat()
{
    cout << "Interdit !!!\n";
}

Navire::Navire(string nomNavire, int orientationNavire, vector<Coordonnees> coordonneesNavire) :
    nom(nomNavire), orientation(orientationNavire), coordonnees(coordonneesNavire), degats(0),
    etat(1){};

Navire::Navire(const Navire& n) :
    nom(n.nom), orientation(n.orientation), coordonnees(n.coordonnees), degats(n.degats),
    etat(n.etat){};

Navire::~Navire(){};

std::string Navire::getNom() const
{
    return nom;
}

bool Navire::ajouterDegat(Coordonnees coordonnee)
{
    for(unsigned int i = 0; i < coordonnees.size(); ++i)
    {
        if(coordonnee.colonne == coordonnees[i].colonne && coordonnee.ligne == coordonnees[i].ligne)
        {
            degats += 1;
            coordonnees[i].colonne = CASE_MORTE_COL;
            coordonnees[i].ligne   = CASE_MORTE_LIG;
            return true;
        }
    }

    return false;
}

vector<Coordonnees> Navire::getCoordonnes() const
{
    return this->coordonnees;
}

bool Navire::estNavireValide(Grille* grille, Flotte* flotte, Navire* nouveauNavire)
{
    if(this->coordonnees.empty())
    {
        return false;
    }

    for(Navire* navireExistant: flotte->getFlotte())
    {
        for(Coordonnees coordEx: navireExistant->getCoordonnes())
        {
            for(Coordonnees coordNouveau: nouveauNavire->getCoordonnes())
            {
                if(coordNouveau.colonne == coordEx.colonne && coordNouveau.ligne == coordEx.ligne)
                    return false;
            }
        }

        if(this->orientation == HORIZONTAL)
        {
            return (this->coordonnees.back().colonne <= grille->getNbColonne());
        }
        else
        {
            return (this->coordonnees.back().ligne <= ('A' + grille->getNbLigne()));
        }
    }
}