#ifndef GRILLE_H
#define GRILLE_H

class Joueur;

class Grille
{
  private:
    int     nbLigne;
    int     nbColonne;
    Joueur* joueur;

  public:
    Grille();
    ~Grille();
    Grille(const Grille&, Joueur*);

    int  getNbLigne() const;
    int  getNbColonne() const;
    void associerGrilleJoueur(Joueur*);
};
#endif