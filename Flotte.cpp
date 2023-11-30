#include "Flotte.h"

using namespace std;

Flotte::Flotte() : flotte()
{
}

Flotte::Flotte(vector<Navire> flotteNavires) : flotte(flotteNavires)
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