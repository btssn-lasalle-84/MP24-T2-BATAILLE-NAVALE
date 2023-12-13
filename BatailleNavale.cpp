#include "BatailleNavale.h"
#include "Joueur.h"
#include "Flotte.h"
#include "IHM.h"
#include "Grille.h"

using namespace std;

BatailleNavale::BatailleNavale() : joueur1(), joueur2(), interface()
{
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
}

void BatailleNavale::demarrerPartie()
{
    IHM::afficherAsciiArt();
    this->initialiserIHM();
    this->initialiserJoueurs();
    this->initialiserGrilles();
    this->initialiserFlottes();
}

void BatailleNavale::initialiserIHM()
{
    IHM ihm;
    ihm.associerInterfaceBataille(this);
    this->associerBatailleInterface(&ihm);
}

void BatailleNavale::initialiserJoueurs()
{
    Joueur machine, joueur;
    machine.setPseudo("Machine");
    joueur.setPseudo(interface->saisirJoueur());
    this->associerBatailleJoueurs(&joueur, &machine);
    machine.associerJoueurBatailleNavale(this);
    joueur.associerJoueurBatailleNavale(this);
}

void BatailleNavale::initialiserGrilles()
{
    Grille grilleJoueur, grilleJouee, grilleMachine;
    grilleJoueur.associerGrilleJoueur(joueur1);
    grilleMachine.associerGrilleJoueur(joueur2);
    joueur1->associerJoueurGrille(&grilleJoueur);
    joueur2->associerJoueurGrille(&grilleMachine);
}

void BatailleNavale::initialiserFlottes()
{
    Flotte flotteJoueur, flotteMachine;
    flotteJoueur = interface->saisirDisposition(joueur1->getGrille());
    flotteMachine.genererAleatoirement(joueur2->getGrille());
    flotteJoueur.associerFlotteJoueur(joueur1);
    flotteMachine.associerFlotteJoueur(joueur2);
    joueur1->associerJoueurFlotte(&flotteJoueur);
    joueur2->associerJoueurFlotte(&flotteMachine);
}

void BatailleNavale::afficherGrilles()
{
    interface->afficherGrille(joueur1);
    interface->afficherGrille(joueur2);
}

void BatailleNavale::associerBatailleJoueurs(Joueur* j1, Joueur* j2)
{
    joueur1 = j1;
    joueur2 = j2;
}

void BatailleNavale::associerBatailleInterface(IHM* interfaceBataille)
{
    interface = interfaceBataille;
}