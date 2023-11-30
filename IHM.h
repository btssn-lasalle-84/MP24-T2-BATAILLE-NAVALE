#ifndef IHM_H
#define IHM_H

class BatailleNavale;

class IHM
{
  private:
    BatailleNavale* bataille;

  public:
    void associerInterfaceBataille(BatailleNavale*);
};

#endif