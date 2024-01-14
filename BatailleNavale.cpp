#include "BatailleNavale.h"
#include "Joueur.h"
#include "Flotte.h"
#include "IHM.h"
#include "Grille.h"

#ifdef DEBUG_BATAILLENAVALE
#include <iostream>
#define DEBUG_GRILLE
#define DEBUG_FLOTTE
#define DEBUG_JOUEUR
#endif

using namespace std;

BatailleNavale::BatailleNavale() : joueur1(nullptr), joueur2(nullptr), interface(new IHM(this))
{
#ifdef DEBUG_BATAILLENAVALE
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
#ifdef DEBUG_BATAILLENAVALE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]" << std::endl;
#endif
}

IHM* BatailleNavale::getInterface() const
{
    return interface;
}

void BatailleNavale::demarrerPartie()
{
#ifdef DEBUG_BATAILLENAVALE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]" << std::endl;
#endif
    interface->afficherAsciiArt();
    interface->afficherVersionLogiciel();
    interface->afficherRegles();
    this->initialiserJoueurs();
    this->initialiserFlottes();
}

void BatailleNavale::initialiserJoueurs()
{
    joueur1 = new Joueur();
    joueur2 = new Joueur();
    joueur2->setPseudo("Machine");
    joueur1->setPseudo(interface->saisirJoueur());
    joueur1->associerJoueurBatailleNavale(this);
    joueur2->associerJoueurBatailleNavale(this);
#ifdef DEBUG_BATAILLENAVALE
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] "
              << "joueur1 = " << joueur1 << " - joueur2 = " << joueur2;
    std::cout << std::endl;
#endif
}

void BatailleNavale::initialiserFlottes()
{
    interface->saisirDisposition(joueur1->getFlotte());
    interface->afficherGrille(joueur1->getGrillePrivee());

    joueur2->getFlotte()->genererAleatoirement();
#ifndef DEBUG_BATAILLENAVALE
    interface->afficherGrille(joueur2->getGrillePrivee());
#endif
}

Joueur* BatailleNavale::jouer()
{
    while(true)
    {
        interface->afficherJeu(joueur1, joueur2);
        interface->inviterASaisir();
        interface->gestionCoup(joueur1, interface->saisirCoup(), joueur2);
        interface->gestionCoup(joueur2, joueur2->genererCoordonneeAleatoire(), joueur1);
        interface->dormir(3);
    }
}
