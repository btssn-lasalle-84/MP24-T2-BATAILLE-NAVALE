#include "BatailleNavale.h"
#include "Flotte.h"
#include "Grille.h"
#include "IHM.h"
#include "Joueur.h"
#include "Navire.h"

int main()
{
    BatailleNavale batailleNavale;

    batailleNavale.demarrerPartie();
    batailleNavale.afficherGrilles();

    return 0;
}