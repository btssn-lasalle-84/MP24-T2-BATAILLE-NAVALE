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
    cout << coordonnee.ligne << endl;
    return !(coordonnee.ligne < 'A' || coordonnee.ligne > 'J' || coordonnee.colonne < 1 ||
             coordonnee.colonne > NB_COLONNE);
}

Coordonnees IHM::saisirCoup(Grille* grille)
{
    char        delimiteur = '\0';
    Coordonnees coordonnee;
    cin >> coordonnee.ligne >> delimiteur >> coordonnee.colonne;
    cout << coordonnee.ligne << coordonnee.colonne;
    while(!estCoupValide(coordonnee, grille))
    {
        cout << "Cette case n'est pas dans la grille !\n";
        cout << "(Les cases vont de A1 à J10)" << endl;
        cout << "Saisissez une case valide : ";
        cin >> coordonnee.ligne >> delimiteur >> coordonnee.colonne;
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
        cout << "Saisissez la case de proue de votre " << nom
             << " sous cette forme : A:1 :" << endl;
        proue = saisirCoup(grille);

        vector<pair<Coordonnees, bool> > coordonnees;
        Navire                           navire(nom, orientation, coordonnees);
        cout << "Apres saisir coup" << endl;
        do
        {
            if(orientation == HORIZONTAL)
            {
                for(unsigned int i = 0; i < nbCases; ++i)
                {
                    pair<Coordonnees, bool> coordonnee;
                    cout << "Ajout de " << i << endl;
                    coordonnee.first.ligne   = proue.ligne;
                    coordonnee.first.colonne = proue.colonne + i;
                    coordonnee.second        = true;
                    coordonnees.push_back(coordonnee);
                    cout << coordonnee.first.colonne << coordonnee.first.ligne << endl;
                }
            }
            else
            {
                for(unsigned int i = 0; i < nbCases; ++i)
                {
                    pair<Coordonnees, bool> coordonnee;
                    cout << "Ajout de " << i << endl;
                    coordonnee.first.colonne = proue.colonne;
                    coordonnee.first.ligne   = proue.ligne + i;
                    coordonnee.second        = true;
                    coordonnees.push_back(coordonnee);
                    cout << coordonnee.first.colonne << coordonnee.first.ligne << endl;
                }
            }

        } while(navire.estNavireValide(grille, navires, navire));

        navires.push_back(&navire);
    }
    cout << "Tous les bateau set";

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

    for(int i = 0; i < joueur->getGrille()->getNbLigne(); ++i)

    {
        for(int j = 0; j < joueur->getGrille()->getNbColonne(); ++j)
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

void IHM::afficherAsciiArt()
{
    cout << " ____        _        _ _ _        _   _                  _      " << endl;
    cout << "|  _ \\      | |      (_) | |      | \\ | |                | |     " << endl;
    cout << "| |_) | __ _| |_ __ _ _| | | ___  |  \\| | __ ___   ____ _| | ___ " << endl;
    cout << "|  _ < / _` | __/ _` | | | |/ _ \\ | . ` |/ _` \\ \\ / / _` | |/ _ \\" << endl;
    cout << "| |_) | (_| | || (_| | | | |  __/ | |\\  | (_| |\\ V / (_| | |  __/" << endl;
    cout << "|____/ \\__,_|\\__\\__,_|_|_|_|\\___| |_| \\_|\\__,_| \\_/ \\__,_|_|\\___|" << endl;
}