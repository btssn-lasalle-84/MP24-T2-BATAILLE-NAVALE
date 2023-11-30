#ifndef JOUEUR_H
#include <iostream>

class Joueur
{
  private:
    std::string pseudo;

  public:
    Joueur();
    ~Joueur();
    Joueur(const Joueur& j);

    std::string getPseudo() const;
    void        setPseudo(std::string nouveauPseudo);
};
#endif