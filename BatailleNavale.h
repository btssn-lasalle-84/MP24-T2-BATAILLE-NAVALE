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
    BatailleNavale(Joueur*, Joueur*, IHM*);
    BatailleNavale(const BatailleNavale&);
    ~BatailleNavale();
    void demarrerPartie();
    void initialiserIHM();
    void initialiserJoueurs();
    void initialiserGrilles();
    void initialiserFlottes();
    void associerBatailleJoueurs(Joueur*, Joueur*);
    void associerBatailleInterface(IHM*);
};

#endif