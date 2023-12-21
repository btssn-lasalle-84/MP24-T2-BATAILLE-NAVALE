#include "IHM.h"
#include "Flotte.h"
#include <iostream>
#include <map>
#include <iomanip>
#include <limits>

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
    return !(coordonnee.ligne < 'A' || coordonnee.colonne < 1 ||
             coordonnee.ligne > (NB_LIGNE + 'A' - 1) || coordonnee.colonne > NB_COLONNE);
}

Coordonnees IHM::saisirCoup(Grille* grille)
{
    string saisie;
    getline(cin, saisie);
    Coordonnees coordonnee;
    if(saisie.size() == 3)
    {
        coordonnee.ligne   = char(saisie[0]);
        coordonnee.colonne = int(char(saisie[2]) - '0');
    }
    else if(saisie.size() == 4)
    {
        coordonnee.ligne   = char(saisie[0]);
        coordonnee.colonne = int(char(saisie[2]) - '0');
        coordonnee.colonne = coordonnee.colonne * 10 + int(char(saisie[3]) - '0');
    }
    else
    {
        cout << "Saisie invalide, veuillez réessayer :\n";
        return saisirCoup(grille);
    }

    if(coordonnee.ligne < 'A' || coordonnee.colonne < 1 || coordonnee.ligne > 'A' + NB_LIGNE - 1 ||
       coordonnee.colonne > NB_LIGNE)
    {
        cout << "Cette case est hors de la grille !" << endl
             << "Les cases vont de A:1 à " << char('A' - 1 + NB_LIGNE) << ':' << NB_COLONNE << endl;
        cout << "Saisie invalide, veuillez réessayer :\n";
        return saisirCoup(grille);
    }

    return coordonnee;
}

Coordonnees IHM::saisirProue(Grille* grille, string nom)
{
    cout << "Saisissez la case de proue de votre " << nom << " (ex : A:1) :\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Coordonnees proue = saisirCoup(grille);
    return proue;
}

int IHM::saisirOrientation(Grille* grille, string nom, int nbCases)
{
    char orientation;
    cout << "Saisissez l'orientation de votre " << nom << " (" << nbCases << " cases)\n"
         << "Horizontal 0 / Vertical 1 : ";
    cin >> orientation;
    while(int(orientation - '0') != HORIZONTAL && int(orientation - '0') != VERTICAL)
    {
        cout << "Orientation invalide !" << endl;
        cout << "Saisissez l'orientation de votre " << nom << " (" << nbCases << " cases)\n"
             << "Horizontal 0 / Vertical 1 : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> orientation;
    }

    return orientation - '0';
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
        string                           nom         = nomBateaux[i];
        int                              valeur      = valeursBateaux[i];
        int                              orientation = saisirOrientation(grille, nom, valeur);
        Coordonnees                      proue       = saisirProue(grille, nom);
        vector<pair<Coordonnees, bool> > coordonnees;
        Navire                           navire(nom, orientation, coordonnees);

        coordonnees.clear();

        bool navireInvalide = true;
        while(navireInvalide)
        {
            navire.setOrientation(orientation);
            coordonnees.clear();

            for(int j = 0; j < valeur; ++j)
            {
                pair<Coordonnees, bool> coordonnee;
                coordonnee.first.colonne = proue.colonne + (j * (1 - orientation));
                coordonnee.first.ligne   = proue.ligne + (j * orientation);
                coordonnee.second        = true;
                coordonnees.push_back(coordonnee);
            }

            navire.setCoordonnees(coordonnees);

            if(navire.estNavireValide(grille, navires))
            {
                navireInvalide = false;
                cout << endl;
                navires.push_back(new Navire(navire)); // Copie le navire dans le vecteur
                cout << "Navire ajouté" << endl;
            }
            else
            {
                cout << "Navire invalide, veuillez le replacer." << endl;
                orientation = saisirOrientation(grille, nom, valeur);
                proue       = saisirProue(grille, nom);
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

std::string IHM::afficherGrilleVierge()
{
    string grille = "X 1 2 3 4 5 6 7 8 9 10\n";
    for(int i = 0; i < NB_LIGNE; ++i)
    {
        grille += char(i + 'A');
        grille += " ";
        for(int j = 0; j < NB_COLONNE; ++j)
        {
            if((j + i) % 2 == 0)
            {
                grille += BLEU;
            }
            else if((j + i) % 2 == 1)
            {
                grille += CYAN;
            }
            grille += DEFAUT;
        }
        grille += '\n';
    }

    grille += '\n';
    return grille;
}

void IHM::afficherGrille(Joueur* joueur)
{
    vector<vector<string> > matrice(joueur->getGrille()->getNbLignes(),
                                    vector<string>(joueur->getGrille()->getNbColonnes(), ""));

    for(int i = 0; i < joueur->getGrille()->getNbLignes(); ++i)
    {
        for(int j = 0; j < joueur->getGrille()->getNbColonnes(); ++j)
        {
            if((j + i) % 2 == 0)
            {
                matrice[i][j] = BLEU;
            }
            else if((j + i) % 2 == 1)
            {
                matrice[i][j] = CYAN;
            }
        }
    }

    for(Navire* navire: joueur->getFlotte()->getFlotte())
    {
        for(pair<Coordonnees, bool> coordonnee: navire->getCoordonnes())
        {
            if(coordonnee.second)
            {
                matrice[coordonnee.first.ligne - 'A'][coordonnee.first.colonne - 1] = GRIS;
            }
            else
            {
                matrice[coordonnee.first.ligne - 'A'][coordonnee.first.colonne - 1] = ROUGE;
            }
        }
    }

    cout << endl << "Grille de : " << joueur->getPseudo() << endl << endl;

    cout << DEFAUT << "X 1 2 3 4 5 6 7 8 9 10" << endl;
    for(size_t i = 0; i < matrice.size(); ++i)
    {
        cout << DEFAUT << char(i + 'A') << ' ';
        for(string j: matrice[i])
        {
            cout << j;
        }
        cout << DEFAUT << endl;
    }

    cout << DEFAUT << endl
         << "Navires restants : " << joueur->getFlotte()->getFlotte().size() << endl
         << endl;
}

void IHM::afficherAsciiArt()
{
    cout << setfill(' ') << setw(53) << " ";
    cout << " ____        _        _ _ _        _   _                  _      " << endl;
    cout << setfill(' ') << setw(53) << " ";
    cout << "|  _ \\      | |      (_) | |      | \\ | |                | |     " << endl;
    cout << setfill(' ') << setw(53) << " ";
    cout << "| |_) | __ _| |_ __ _ _| | | ___  |  \\| | __ ___   ____ _| | ___ " << endl;
    cout << setfill(' ') << setw(53) << " ";
    cout << "|  _ < / _` | __/ _` | | | |/ _ \\ | . ` |/ _` \\ \\ / / _` | |/ _ \\" << endl;
    cout << setfill(' ') << setw(53) << " ";
    cout << "| |_) | (_| | || (_| | | | |  __/ | |\\  | (_| |\\ V / (_| | |  __/" << endl;
    cout << setfill(' ') << setw(53) << " ";
    cout << "|____/ \\__,_|\\__\\__,_|_|_|_|\\___| |_| \\_|\\__,_| \\_/ \\__,_|_|\\___|" << endl;
    cout << endl;
}

void IHM::afficherRegles()
{
    cout << setfill(' ') << setw(75);
    cout << BLEU_REGLE << "Bienvenue dans le jeu Bataille Navale !" << DEFAUT << endl;
    cout << setfill(' ') << setw(45) << " ";
    cout << "Le but est de détruire les bateaux adverses avant que les vôtre soient repérés."
         << endl;
    cout << setfill(' ') << setw(20) << " ";
    cout << "Pour cela vous devez dans un premier temps placer vos bateaux en selectionnant "
            "l'orientation, puis les coordonnées de la proue du bateau."
         << endl;
    cout << setfill(' ') << setw(66) << " ";
    cout << "Voici un représentation de la grille :" << endl;
    cout << endl;
    cout << setfill(' ') << setw(75) << " " << afficherGrilleVierge() << endl;
    cout << setfill(' ') << setw(45) << " ";
    cout << "Après avoir placé vos bateaux, la machine placera automatiquement les siens." << endl;
    cout << setfill(' ') << setw(35) << " ";
    cout << "Vous pourrez donc commencer à jouer en tapant la coordonnée à laquelle vous voulez "
            "envoyer vôtre boulet de canon.";
    cout << endl;
    cout << VERT << "Début de la partie ! " << DEFAUT << endl;
}