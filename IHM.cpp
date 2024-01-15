#include "IHM.h"
#include "Flotte.h"
#include "Grille.h"
#include "BatailleNavale.h"
#include "Coordonnees.h"
#include "Navire.h"
#include "Joueur.h"
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

bool IHM::estCoupValide(Coordonnees coordonnee)
{
    return !(coordonnee.ligne < 'A' || coordonnee.colonne < 1 ||
             coordonnee.ligne > (NB_LIGNE + 'A' - 1) || coordonnee.colonne > NB_COLONNE);
}

Coordonnees IHM::saisirCoup()
{
    string saisie;
    getline(cin, saisie);
    Coordonnees coordonnee = formaterSaisie(saisie);

    if(estCoupValide(coordonnee))
    {
        return coordonnee;
    }

    cout << "Cette case est hors de la grille !" << endl << "Les cases vont de A:1 à J:10" << endl;
    cout << "Saisie invalide, veuillez réessayer :\n";
    return saisirCoup();
}

Coordonnees IHM::formaterSaisie(string saisie)
{
    Coordonnees coordonnee;
    if(saisie.size() == TAILLE_SAISIE_1)
    {
        coordonnee.ligne   = char(toupper(char(saisie[0])));
        coordonnee.colonne = int(char(saisie[2]) - '0');
    }
    else if(saisie.size() == TAILLE_SAISIE_2)
    {
        coordonnee.ligne   = char(toupper(char(saisie[0])));
        coordonnee.colonne = int(char(saisie[2]) - '0');
        coordonnee.colonne = coordonnee.colonne * 10 + int(char(saisie[3]) - '0');
    }
    else
    {
        cout << "Saisie invalide, veuillez réessayer :\n";
        return saisirCoup();
    }

    return coordonnee;
}

Coordonnees IHM::saisirProue(string nom)
{
    cout << "Saisissez la case de proue de votre " << nom << " (ex : A:1) :\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Coordonnees proue = saisirCoup();
    return proue;
}

int IHM::saisirOrientation(string nom, int nbCases)
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

void IHM::saisirDisposition(Flotte* flotte)
{
    vector<Navire*> navires;
    vector<string>  nomBateaux     = { "Porte-Avion",
                                  "Croiseur",
                                  "Contre-torpilleur",
                                  "Sous-marin",
                                  "Torpilleur" };
    vector<int>     valeursBateaux = { 5, 4, 3, 3, 2 };

    flotte->genererNavires(nomsBateaux, valeursBateaux, this);

    cout << "Tous les bateaux sont définis" << endl;
}

void IHM::associerInterfaceBataille(BatailleNavale* batailleInterface)
{
    bataille = batailleInterface;
}

void IHM::afficherGrilleVierge()
{
    vector<vector<string> > matrice(NB_LIGNE, vector<string>(NB_COLONNE, ""));
    genererFondGrille(matrice);
    cout << DEFAUT << "X 1 2 3 4 5 6 7 8 9 10" << endl;
    for(size_t i = 0; i < matrice.size(); ++i)
    {
        cout << DEFAUT << char(i + 'A') << ' ';
        afficherLigneGrille(matrice[i]);
        cout << DEFAUT << endl;
    }
}

void IHM::afficherFlotte(Joueur* joueur)
{
    vector<vector<string> > matrice(NB_LIGNE, vector<string>(NB_COLONNE, ""));

    genererFondGrille(matrice);
    ajouterNaviresGrille(joueur, matrice);

    cout << endl << "Grille de : " << joueur->getPseudo() << endl << endl;

    afficherGrilleFlotte(joueur, matrice);
}


void IHM::gestionCoup(bool touche)
{
    if(touche)
    {
        cout << "Touché !" << endl;
    }
    else
    {
        cout << "Plouf !" << endl;
    }
}
void IHM::afficherGrilleFlotte(Joueur* joueur, vector<vector<string> >& matrice)

{
    cout << DEFAUT << "X 1 2 3 4 5 6 7 8 9 10" << endl;
    for(size_t i = 0; i < NB_LIGNE; ++i)
    {
        cout << DEFAUT << char(i + 'A') << ' ';
        afficherLigneGrille(matrice[i]);
        cout << DEFAUT << endl;
    }

    cout << DEFAUT << endl
         << "Navires restants : " << joueur->getFlotte()->getFlotte().size() << endl
         << endl;
}

void IHM::afficherGrille(Joueur* joueur)
{
    cout << DEFAUT << "X 1 2 3 4 5 6 7 8 9 10" << endl;
    for(size_t i = 0; i < NB_LIGNE; ++i)
    {
        cout << DEFAUT << char(i + 'A') << ' ';
        afficherLigneGrille(joueur->getGrille()->getGrille()[i]);
        cout << DEFAUT << endl;
    }

    cout << DEFAUT << endl
         << "Navires restants : " << joueur->getFlotte()->getFlotte().size() << endl
         << endl;
}

void IHM::genererFondGrille(vector<vector<string> >& matrice)
{
    for(int i = 0; i < NB_LIGNE; ++i)
    {
        for(int j = 0; j < NB_COLONNE; ++j)
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
}

void IHM::ajouterNaviresGrille(Joueur* joueur, vector<vector<string> >& matrice)
{
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
}

void IHM::afficherLigneGrille(vector<string>& ligne)
{
    for(string i: ligne)
    {
        cout << i;
    }
}

void IHM::clearTerminal()
{
    system("clear");
}

void IHM::afficherAsciiArt()
{
    clearTerminal();
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

void IHM::afficherVersionLogiciel()
{
    cout << setfill(' ') << setw(95);
    cout << ROSE << "v" << VERSION << endl << endl;
}

void IHM::afficherRegles()
{
    cout << setfill(' ') << setw(75);
    cout << BLEU_REGLE << "Bienvenue dans le jeu Bataille Navale !" << DEFAUT << endl;
    cout << setfill(' ') << setw(45) << " ";
    cout << "Le but est de couler les bateaux adverses avant que les vôtres ne soient détruits."
         << endl;
    cout << setfill(' ') << setw(20) << " ";
    cout << "Pour cela vous devez dans un premier temps placer votre flotte en selectionnant "
            "l'orientation de chaque navire ainsi que la coordonnée de sa proue"
         << endl;
    cout << setfill(' ') << setw(66) << " ";
    cout << "Voici une représentation de la grille :" << endl;
    cout << endl;
    afficherGrilleVierge();
    cout << setfill(' ') << setw(45) << " ";
    cout << "Après avoir placé vos bateaux, la machine placera automatiquement les siens." << endl;
    cout << setfill(' ') << setw(35) << " ";
    cout << "Vous pourrez donc commencer à jouer en tapant la coordonnée à laquelle vous voulez "
            "envoyer votre boulet de canon.";
    cout << endl;
    cout << VERT << "Début du placement de la flotte ! " << DEFAUT << endl;
}

void IHM::jeuJoueur()
{
    cout << "Quel coup jouer ?" << endl;
}

void IHM::jeuMachine()
{
    cout << "La machine à jouer" << endl;
}

Coordonnees IHM::genererCoordonneesAleatoires()
{
    Coordonnees coo;
    srand(time(NULL));

    coo.colonne = rand() % (NB_COLONNE) + 1;
    coo.ligne   = rand() % (NB_LIGNE + 1) + 'A';

    return coo;
}