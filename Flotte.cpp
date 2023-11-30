#include "Flotte.h"

using namespace std;

Flotte::Flotte() : flotte(), joueur()
{
}

Flotte::Flotte(const vector<Navire> flotteNavires, Joueur* flotteJoueur) :
    flotte(flotteNavires), joueur(flotteJoueur)
{
}

Flotte::Flotte(const Flotte& f) : flotte(f.flotte), joueur(f.joueur)
{
}

Flotte::~Flotte()
{
}

void Flotte::associerFlotteJoueur(Joueur* joueurFlotte)
{
    joueur = joueurFlotte;
}