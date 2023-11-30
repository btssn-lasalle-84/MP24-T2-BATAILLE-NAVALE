#include "Flotte.h"

using namespace std;

Flotte::Flotte() : flotte()
{
}

Flotte::Flotte(const vector<Navire*> flotteNavires, Joueur* flotteJoueur) :
    flotte(flotteNavires), joueur(flotteJoueur)
{
}

Flotte::Flotte(const Flotte& f) : flotte(f.flotte)
{
}

Flotte::~Flotte()
{
}

void Flotte::associerFlotteJoueur(Joueur* joueurFlotte)
{
    joueur = joueurFlotte;
}