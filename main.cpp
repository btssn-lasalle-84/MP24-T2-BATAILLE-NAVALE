#include "BatailleNavale.h"

int main()
{
    BatailleNavale batailleNavale;

    batailleNavale.demarrerPartie();
    batailleNavale.finirPartie(batailleNavale.jouer());
    return 0;
}