#include "IHM.h"

using namespace std;

IHM::IHM() : bataille()
{};

IHM::IHM(BatailleNavale* batailleInterface) : bataille(batailleInterface)
{};

IHM::IHM(const IHM& ihm) : bataille(ihm.bataille)
{};

IHM::~IHM()
{};

string IHM::saisirJoueur()
{
    string nomJoueur;
    cout << "Saisissez le nom du joueur : ";
    cin >> nomJoueur;
    return nomJoueur;
}

void IHM::associerInterfaceBataille(BatailleNavale* batailleInterface)
{
    bataille = batailleInterface;
}