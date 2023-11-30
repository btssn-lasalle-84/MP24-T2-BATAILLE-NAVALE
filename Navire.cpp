#include "Navire.h"
#include <algorithm>

using namespace std;

Navire::Navire() : nom(" "), orientation(), coordonnees(), degats(), etat()
{
    cout << "Interdit !!!\n";
}

Navire::Navire(string nomNavire, int orientationNavire, vector<Coordonnees> coordonneesNavire) :
    nom(nomNavire), orientation(orientationNavire), coordonnees(coordonneesNavire), degats(0),
    etat(1){};

Navire::Navire(Navire& n) :
    nom(n.nom), orientation(n.orientation), coordonnees(n.coordonnees), degats(n.degats),
    etat(n.etat){};

Navire::~Navire(){};

std::string Navire::getNom() const
{
    return nom;
}

bool Navire::ajouterDegat(Coordonnees coordonnee)
{
    vector<Coordonnees>::iterator it = find(coordonnees.begin(), coordonnees.end(), coordonnee);
    if(it != coordonnees.end())
    {
        coordonnees.erase(it);
        degats += 1;
        return true;
    }

    return false;
}