#include "Navire.h"
#include "Flotte.h"
#include "debug.h"

using namespace std;

Navire::Navire() : nom(" "), orientation(), coordonnees(), degats(), etat()
{
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
    for(pair<Coordonnees, bool> coordonneeNavire: coordonnees)
    {
        if(coordonnee.ligne == coordonneeNavire.first.ligne &&
           coordonnee.colonne == coordonneeNavire.first.colonne)
        {
            coordonneeNavire.second = false;
            degats += 1;
            return true;
        }
    }
    return false;
}

bool Navire::estVivant()
{
    if(degats == coordonnees.size())
    {
        etat = false;
        return false;
    }

    etat = true;
    return true;
}

int Navire::getEtat() const
{
    return (int)etat;
}

void Navire::genererCoordonnees(Coordonnees proue, int nbCases)
{
    for(int i = 0; i < nbCases; ++i)
    {
        pair<Coordonnees, bool> coordonnee;
        coordonnee.first.colonne = proue.colonne + (i * (1 - orientation));
        coordonnee.first.ligne   = proue.ligne + (i * orientation);
        coordonnee.second        = true;
        coordonnees.push_back(coordonnee);
    }

    this->setCoordonnees(coordonnees);
}

void Navire::gererCreation(int valeur, Coordonnees proue, IHM* interface, Flotte* flotte)
{
    bool navireInvalide = true;
    while(navireInvalide)
    {
        this->setOrientation(orientation);
        coordonnees.clear();
        this->genererCoordonnees(proue, valeur);

        if(this->estNavireValide(flotte->getFlotte()))
        {
            navireInvalide = false;
            cout << endl;
            flotte->ajouterNavire(new Navire(*this));
            cout << "Navire ajouté" << endl;
            flotte->getJoueur()->getGrillePrivee()->appliquerFlotteSurGrille();
            interface->afficherGrille(flotte->getJoueur()->getGrillePrivee());
        }
        else
        {
            cout << "Navire invalide, veuillez le replacer." << endl;
            orientation = interface->saisirOrientation(this->nom, valeur);
            proue       = interface->saisirProue(this->nom);
        }
    }
}

void Navire::gererCreationAleatoire(int nbCases, Flotte* flotte)
{
    bool navireInvalide = true;
    while(navireInvalide)
    {
        Coordonnees proue = this->genererInfosAleatoires(nbCases);
        this->genererCoordonnees(proue, nbCases);

        if(this->estNavireValide(flotte->getFlotte()))
        {
            navireInvalide = false;
            cout << endl;
            flotte->ajouterNavire(new Navire(*this)); // Copie le navire dans le vecteur
        }
    }
}

Coordonnees Navire::genererInfosAleatoires(int nbCases)
{
    Coordonnees proue;
    srand(time(NULL));
    int orientation = rand() % 2;
    this->setOrientation(orientation);
    coordonnees.clear();

    if(orientation == HORIZONTAL)
    {
        proue.colonne = rand() % (NB_COLONNE - nbCases + 1) + 1;
        proue.ligne   = rand() % (NB_LIGNE) + 'A';
    }
    else
    {
        proue.colonne = rand() % (NB_COLONNE) + 1;
        proue.ligne   = rand() % (NB_LIGNE - nbCases + 1) + 'A';
    }

    return proue;
}

bool Navire::estNavireValide(const vector<Navire*>& navires)
{
    if(this->coordonnees.empty())
    {
        return false;
    }

    if(this->orientation == HORIZONTAL)
    {
        if(!(this->coordonnees.back().first.colonne <= NB_COLONNE))
        {
            return false;
        }
    }
    else
    {
        if(!(this->coordonnees.back().first.ligne <= ('A' - 1 + NB_LIGNE)))
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