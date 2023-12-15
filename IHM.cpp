#include "IHM.h"
#include "Flotte.h"
#include <iostream>
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
    return !(coordonnee.ligne < 'A' || coordonnee.ligne > 'J' || coordonnee.colonne < 1 ||
             coordonnee.colonne > NB_COLONNE);
}

Coordonnees IHM::saisirCoup(Grille* grille)
{
    char        delimiteur = '\0';
    Coordonnees coordonnee;
    cin >> coordonnee.ligne >> delimiteur >> coordonnee.colonne;
    while(!estCoupValide(coordonnee, grille))
    {
        cout << "Cette case n'est pas dans la grille !\n";
        cout << "(Les cases vont de A1 à J10)" << endl;
        cout << "Saisissez une case valide : ";
        cin >> coordonnee.ligne >> delimiteur >> coordonnee.colonne;
    }

    return coordonnee;
}

void IHM::saisirDisposition(Grille* grille, Flotte* flotte)
{
    vector<Navire*> navires;
    vector<string>  nomBateaux     = { "Porte-Avion",
                                  "Croiseur",
                                  "Contre-torpilleur",
                                  "Sous-marin",
                                  "Torpilleur" };
    vector<int>     valeursBateaux = { 5, 4, 3, 3, 2 };

    for(int i = 0; i < (int)nomBateaux.size(); i++)
    {
        cout << i << endl;
        string nom    = nomBateaux[i];
        int    valeur = valeursBateaux[i];

        cout << "Saisissez l'orientation de votre " << nom << " (" << valeur << " cases)\n"
             << "Horizontal 0 / Vertical 1 : ";
        int orientation;
        cin >> orientation;

        cout << "Saisissez la case de proue de votre " << nom
             << " sous cette forme : A:1 :" << endl;
        Coordonnees proue = saisirCoup(grille);

        vector<pair<Coordonnees, bool> > coordonnees;
        Navire                           navire(nom, orientation, coordonnees);

        coordonnees.clear();

        bool navireInvalide = true;
        while(navireInvalide)
        {
            coordonnees.clear();

            if(orientation == HORIZONTAL)
            {
                for(int j = 0; j < valeur; ++j)
                {
                    pair<Coordonnees, bool> coordonnee;
                    coordonnee.first.colonne = proue.colonne + j;
                    coordonnee.first.ligne   = proue.ligne;
                    coordonnee.second        = true;
                    coordonnees.push_back(coordonnee);
                }
            }
            else
            {
                for(int j = 0; j < valeur; ++j)
                {
                    pair<Coordonnees, bool> coordonnee;
                    coordonnee.first.colonne = proue.colonne;
                    coordonnee.first.ligne   = proue.ligne + j;
                    coordonnee.second        = true;
                    coordonnees.push_back(coordonnee);
                }
            }

            navire.setCoordonnees(coordonnees);

            if(navire.estNavireValide(grille, navires, navire))
            {
                navireInvalide = false;
                navires.push_back(new Navire(navire)); // Copie le navire dans le vecteur
                cout << "Navire ajouté" << endl;
            }
            else
            {
                cout << "Navire invalide, veuillez le replacer." << endl;
                Coordonnees proue = saisirCoup(grille);
            }
        }
    }

    cout << "Tous les bateaux sont définis" << endl;

    flotte->setFlotte(navires);
}

void IHM::associerInterfaceBataille(BatailleNavale* batailleInterface)
{
    bataille = batailleInterface;
}

void IHM::afficherGrille(Joueur* joueur)
{
    vector<vector<string> > matrice(joueur->getGrille()->getNbLignes(),
                                    vector<string>(joueur->getGrille()->getNbColonnes(), ""));
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

    for(int i = 0; i < joueur->getGrille()->getNbLignes(); ++i)

    {
        for(int j = 0; j < joueur->getGrille()->getNbColonnes(); ++j)
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