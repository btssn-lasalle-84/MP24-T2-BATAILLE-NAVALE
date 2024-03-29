#ifndef BATAILLENAVALE_H
#define BATAILLENAVALE_H


//#define DEBUG_BATAILLENAVALE // ou l'option -DDEBUG_BATAILLENAVALE dans g++

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

    IHM*    getInterface() const;
    void    demarrerPartie();
    void    finirPartie(Joueur*);
    Joueur* jouer();
    void    initialiserJoueurs();
    void    initialiserFlottes();
};

#endif // BATAILLENAVALE_H