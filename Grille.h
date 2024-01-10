#ifndef GRILLE_H
#define GRILLE_H

#include <vector>

#define DEBUG_GRILLE

#ifndef COULEUR
#define COULEUR
#define ROSE       "\033[1;38;5;200m"
#define BLEU       "\033[48;5;33m  "
#define CYAN       "\033[48;5;75m  "
#define ROUGE      "\033[48;5;196m  "
#define GRIS       "\033[48;5;236m  "
#define BLEU_REGLE "\033[38;5;153m"
#define VERT       "\033[1;38;5;46m"
#define DEFAUT     "\033[0;5;0m"
#endif

#define NB_LIGNE   10
#define NB_COLONNE 10

class Joueur;

class Grille
{
  private:
    std::vector<std::vector<std::string> > grille;
    Joueur*                                joueur;

  public:
    Grille(Joueur* joueur);
    ~Grille();
    Grille(const Grille&);
    std::vector<std::vector<std::string> > getGrille() const;
};

#endif