#include <iostream>
#include <iomanip>
#include "stronghold.h"

using namespace std;

int Stronghold::getHonour() const
{
    return honour;
}

int Stronghold::getInitialDefence() const
{
    return initialDefence;
}

Stronghold::Stronghold(string iName) : Holding(iName)
{
    holdingType = HOLDING_TYPE_STRONGHOLD;
}

void Stronghold::PrintCard() const
{
    cout << "\033[1;31m";
    PrintHorizontalBorder();
    cout << "|" << setw(CARD_WIDTH - 2) << "Name: " + name << "|" << endl;
    cout << "|" << setw(CARD_WIDTH - 2) << "Honour: " + to_string(honour) << "|" << endl;
    cout << "|" << setw(CARD_WIDTH - 2) << "Harvest Value (money): " + to_string(harvestValue) << "|" << endl;
    cout << "|" << setw(CARD_WIDTH - 2) << "Defence: " + to_string(initialDefence) << "|" << endl;
    PrintHorizontalBorder();
    cout << "\033[0m\n";
}

#ifdef GUI_SUPPORT
void Stronghold::PrintGUICard() const
{
    ofstream inputFile;
    inputFile.open(INPUT_PATH, ios::out | ios::app);
    inputFile << id << /*" Name: " << name <<*/ " Honour: " << honour <<  " Value: " << harvestValue << " Defence: " << initialDefence << " END" << endl;
    inputFile.close();
}
#endif

GreatCity::GreatCity(string iName) : Stronghold(iName)
{
    honour = 5;
    harvestValue = 8;
    initialDefence = 4;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::great_city;
#endif
}

GreatCastle::GreatCastle(string iName) : Stronghold(iName)
{
    honour = 4;
    harvestValue = 6;
    initialDefence = 8;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::great_castle;
#endif
}

GreatPort::GreatPort(string iName) : Stronghold(iName)
{
    honour = 3;
    harvestValue = 10;
    initialDefence = 6;
}
