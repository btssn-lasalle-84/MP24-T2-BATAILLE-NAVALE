#include "IHM.h"
#include <map>

using namespace std;

IHM::IHM() : bataille(){};

IHM::IHM(BatailleNavale* batailleInterface) : bataille(batailleInterface){};

IHM::IHM(const IHM& ihm) : bataille(ihm.bataille){};

IHM::~IHM(){};

string IHM::saisirJoueur()
{
    string nomJoueur;
    cout << "Saisissez le nom du joueur : ";
    cin >> nomJoueur;
    return nomJoueur;
}

bool IHM::estCoupValide(Coordonnees coordonnee, Grille* grille)
{
    return !(coordonnee.ligne < 'A' || coordonnee.ligne > (grille->getNbLigne() - 1) + 'A' ||
             coordonnee.colonne < 1 || coordonnee.colonne > grille->getNbColonne());
}

Coordonnees IHM::saisirCoup(Grille* grille)
{
    Coordonnees coordonnee;
    cin >> coordonnee.ligne >> coordonnee.colonne;
    while(!estCoupValide(coordonnee, grille))
    {
        cout << "Cette case n'est pas dans la grille !\n";
        cout << "(Les cases vont de A1 à " << (('A') + grille->getNbLigne() - 1)
             << grille->getNbColonne() << ")\n";
        cout << "Saisissez une case valide : ";
        cin >> coordonnee.ligne >> coordonnee.colonne;
    }

    return coordonnee;
}

Flotte IHM::saisirDisposition(Grille* grille)
{
    Flotte                    flotte;
    vector<Navire*>           navires;
    map<string, unsigned int> bateaux{ { "Porte-avion", 5 },
                                       { "Croiseur", 4 },
                                       { "Contre-torpilleur", 3 },
                                       { "Sous-marin", 3 },
                                       { "Torpilleur", 2 } };
    int                       orientation;
    Coordonnees               proue;

    for(map<string, unsigned int>::iterator it = bateaux.begin(); it != bateaux.end(); ++it)
    {
        string       nom     = it->first;
        unsigned int nbCases = it->second;

        cout << "Saisiez l'orientation de votre " << nom << " (" << nbCases << " cases)\n"
             << "Horizontal 0 / Vertical 1 : ";
        cin >> orientation;
        cout << "Saisissez la case de proue de votre " << nom << " : ";
        proue = saisirCoup(grille);

        vector<pair<Coordonnees, bool> > coordonnees;
        Navire                           navire(nom, orientation, coordonnees);
        do
        {
            for(unsigned int i = 0; i < nbCases; ++i)
            {
                pair<Coordonnees, bool> coordonnee;
                coordonnee.first.colonne = proue.colonne + i;
                coordonnee.first.ligne   = proue.ligne + i;
                coordonnee.second        = true;
                coordonnees.push_back(coordonnee);
            }

        } while(navire.estNavireValide(grille, navires, navire));

        navires.push_back(&navire);
    }

    flotte.setFlotte(navires);
    return flotte;
}

void IHM::associerInterfaceBataille(BatailleNavale* batailleInterface)
{
    bataille = batailleInterface;
}

void IHM::afficherGrille(Joueur* joueur)
{
    vector<vector<string> > matrice(joueur->getGrille()->getNbLigne(),
                                    vector<string>(joueur->getGrille()->getNbColonne(), ""));
    for(Navire* navire: joueur->getFlotte()->getFlotte())
    {
        for(pair<Coordonnees, bool> coordonnee: navire->getCoordonnes())
        {
            if(coordonnee.second)
            {
                matrice[coordonnee.first.ligne - 'A'][coordonnee.first.colonne] = GRIS;
            }
            else
            {
                matrice[coordonnee.first.ligne - 'A'][coordonnee.first.colonne] = ROUGE;
            }
        }
    }

    for(unsigned int i = 0; i < joueur->getGrille()->getNbLigne(); ++i)
    {
        for(unsigned int j = 0; j < joueur->getGrille()->getNbColonne(); ++j)
        {
            if((j + i) % 2 == 0 && matrice[i][j] == "")
            {
                matrice[i][j] == BLEU;
            }
            else if((j + i) % 2 == 1 && matrice[i][j] == "")
            {
                matrice[i][j] == CYAN;
            }
        }
    }

    for(vector<string> i: matrice)
    {
        for(string j: i)
        {
            cout << j;
        }
        cout << endl;
    }
}
