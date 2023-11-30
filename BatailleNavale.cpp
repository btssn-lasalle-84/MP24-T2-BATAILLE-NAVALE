#include "BatailleNavale.h"

using namespace std;

BatailleNavale::BatailleNavale() : joueur1(), joueur2()
{
}

BatailleNavale::BatailleNavale(Joueur* j1, Joueur* j2) : joueur1(j1), joueur2(j2)
{
}

BatailleNavale::BatailleNavale(const BatailleNavale& bn) : joueur1(bn.joueur1), joueur2(bn.joueur2)
{
}

BatailleNavale::~BatailleNavale()
{
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