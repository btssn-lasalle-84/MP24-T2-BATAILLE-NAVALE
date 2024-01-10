#include "BatailleNavale.h"
#include "Joueur.h"
#include "Flotte.h"
#include "IHM.h"
#include "Grille.h"

#ifndef DEBUG_BATAILLENAVALE
#include <iostream>
#endif

using namespace std;

BatailleNavale::BatailleNavale() : joueur1(nullptr), joueur2(nullptr), interface(new IHM(this))
{
#ifndef DEBUG_BATAILLENAVALE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] this = " << this << " "
              << "joueur1 = " << joueur1 << " - joueur2 = " << joueur2
              << " - interface = " << interface;
    std::cout << std::endl;
#endif
}

BatailleNavale::BatailleNavale(Joueur* j1, Joueur* j2, IHM* interfaceBataille) :
    joueur1(j1), joueur2(j2), interface(interfaceBataille)
{
}

BatailleNavale::BatailleNavale(const BatailleNavale& bn) :
    joueur1(bn.joueur1), joueur2(bn.joueur2), interface(bn.interface)
{
}

BatailleNavale::~BatailleNavale()
{
    delete joueur1;
    delete joueur2;
    delete interface;
#ifndef DEBUG_BATAILLENAVALE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]" << std::endl;
#endif
}

void BatailleNavale::demarrerPartie()
{
#ifndef DEBUG_BATAILLENAVALE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]" << std::endl;
#endif
    interface->afficherAsciiArt();
    interface->afficherVersionLogiciel();
    interface->afficherRegles();
    this->initialiserJoueurs();
    this->initialiserFlottes();
    this->deroulementPartie();
}

void BatailleNavale::initialiserJoueurs()
{
    joueur1 = new Joueur();
    joueur2 = new Joueur();
    joueur2->setPseudo("Machine");
    joueur1->setPseudo(interface->saisirJoueur());
    joueur1->associerJoueurBatailleNavale(this);
    joueur2->associerJoueurBatailleNavale(this);
#ifndef DEBUG_BATAILLENAVALE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] "
              << "joueur1 = " << joueur1 << " - joueur2 = " << joueur2;
    std::cout << std::endl;
#endif
}

void BatailleNavale::initialiserFlottes()
{
    interface->saisirDisposition(joueur1->getFlotte());
    interface->afficherGrille(joueur1);

    joueur2->getFlotte()->genererAleatoirement(joueur2->getGrille());
#ifndef DEBUG_BATAILLENAVALE
    interface->afficherGrille(joueur2);
#endif
}

void BatailleNavale::deroulementPartie()
{
    bool partieFini = false;
    while(!partieFini)
    {
        interface->jeuJoueur();
        interface->gestionCoup(joueur2->getFlotte()->tirer(interface->saisirCoup()));
        interface->jeuMachine();
        interface->gestionCoup(
          joueur1->getFlotte()->tirer(interface->genererCoordonneesAleatoires()));
    }
}

void BatailleNavale::afficherGrilles()
{
    interface->afficherGrille(joueur1);
    interface->afficherGrille(joueur2);
}
