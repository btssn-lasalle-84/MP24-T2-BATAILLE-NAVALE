#ifndef JOUEUR_H
#define JOUEUR_H
#include <iostream>

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
    ~Joueur();
    Joueur(const Joueur& j);

    std::string getPseudo() const;
    void        setPseudo(std::string nouveauPseudo);
    void        associerJoueurGrille(Grille*);
    void        associerJoueurBatailleNavale(BatailleNavale*);
    void        associerJoueurFlotte(Flotte*);
};
#endif