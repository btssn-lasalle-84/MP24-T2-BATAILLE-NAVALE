#include "Joueur.h"

Joueur::Joueur() : pseudo("toto")
{
}

Joueur::~Joueur()
{
}

std::string Joueur::getPseudo() const
{
    return this->pseudo;
}

void Joueur::setPseudo(const std::string nouveauPseudo)
{
    this->pseudo = nouveauPseudo;
}
