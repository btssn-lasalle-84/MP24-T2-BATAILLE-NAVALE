#ifndef NAVIRE_H
#include <iostream>
#include <vector>

enum orientation
{
    HORIZONTAL = 0,
    VERTICAL   = 1
};

struct Coordonnees
{
    int  colonne;
    char ligne;
};

class Navire
{
  private:
    std::string              nom;
    int                      orientation;
    std::vector<Coordonnees> coordonnees;
    int                      degats;
    bool                     etat;

  public:
    Navire(std::string, int, std::vector<Coordonnees>);
    Navire();
    Navire(const Navire& n);
    ~Navire();
    std::string getNom() const;
    bool        ajouterDegat(Coordonnees);
    bool        estMort() const;
};
#endif