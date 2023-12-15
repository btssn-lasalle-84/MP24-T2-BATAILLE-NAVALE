#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>

#define DEBUG_JOUEUR

class Grille;
class BatailleNavale;
class Flotte;

class Joueur
{
  private:
    std::string     pseudo;
    Grille*         grille;
    BatailleNavale* bataille;
    Flotte*         flotte;

  public:
    Joueur();
    Joueur(std::string, Grille*, BatailleNavale*, Flotte*);
    ~Joueur();
    Joueur(const Joueur& j);

    std::string getPseudo() const;
    Grille*     getGrille() const;
    Flotte*     getFlotte() const;
    void        setPseudo(const std::string nouveauPseudo);
    void        associerJoueurBatailleNavale(BatailleNavale*);
};
#endif