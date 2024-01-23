#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include "Coordonnees.h"

class Grille;
class BatailleNavale;
class Flotte;

class Joueur
{
  private:
    std::string     pseudo;
    Grille*         grillePrivee;
    Grille*         grillePublique;
    BatailleNavale* bataille;
    Flotte*         flotte;

  public:
    Joueur();
    Joueur(std::string, Grille*, Grille*, BatailleNavale*, Flotte*);
    ~Joueur();
    Joueur(const Joueur& j);

    std::string     getPseudo() const;
    Grille*         getGrillePrivee() const;
    Grille*         getGrillePublique() const;
    Flotte*         getFlotte() const;
    BatailleNavale* getBatailleNavale() const;
    void            setPseudo(const std::string nouveauPseudo);
    void            associerJoueurBatailleNavale(BatailleNavale*);
    bool            aPerdu();
    Coordonnees     genererCoordonneeAleatoire();
};

#endif // JOUEUR_H