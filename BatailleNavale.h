#ifndef BATAILLENAVALE_H
#define BATAILLENAVALE_H

class Joueur;
class IHM;

class BatailleNavale
{
  private:
    Joueur* joueur1;
    Joueur* joueur2;
    IHM*    interface;

  public:
    BatailleNavale();
    BatailleNavale(Joueur*, Joueur*);
    BatailleNavale(const BatailleNavale&);
    ~BatailleNavale();
    void associerBatailleJoueurs(Joueur*, Joueur*);
    void associerBatailleInterface(IHM*);
};

#endif