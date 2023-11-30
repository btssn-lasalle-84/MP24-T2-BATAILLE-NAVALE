class Grille
{
  private:
    int nbLigne;
    int nbColonne;

  public:
    Grille();
    ~Grille();
    Grille(const Grille& g);

    int getNbLigne() const;
    int getNbColonne() const;
};