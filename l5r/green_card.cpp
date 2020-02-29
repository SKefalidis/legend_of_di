#include <iostream>
#include <iomanip>
#include <string>
#include "green_card.h"
#include "assert.h"
#include "printer.h"
#include "terminal_colours.h"

using namespace std;

GreenCard::GreenCard(string iName) : Card(iName)
{
    attackBonus = -1;
    defenceBonus = -1;
    minimumHonour = -1;
    effectBonus = -1;
    effectCost = -1;
    cardText = "Placeholder text";
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::green;
    id_back = IMAGE_FILE_ID::green_card_back;
#endif
}

void GreenCard::PrintCard() const
{
    COLOUR_REGION_GREEN;
    Card::PrintCard();
    cout << "|" << setw(CARD_WIDTH - 2) << cardText << "|" << endl;
    cout << "|" << setw(CARD_WIDTH - 2) << "AttackBonus: " + to_string(attackBonus) << "|" << endl;
    cout << "|" << setw(CARD_WIDTH - 2) << "DefenceBonus: " + to_string(defenceBonus) << "|" << endl;
    cout << "|" << setw(CARD_WIDTH - 2) << "MinimumHonour: " + to_string(minimumHonour) << "|" << endl;
    cout << "|" << setw(CARD_WIDTH - 2) << "EffectBonus: " + to_string(effectBonus) << "|" << endl;
    cout << "|" << setw(CARD_WIDTH - 2) << "EffectCost: " + to_string(effectCost) << "|" << endl;
}

void GreenCard::AddToPrintBuffer() const
{
    string s = "";
    Card::AddToPrintBuffer();
    s = cardText + " |";
    Printer::AddStringToBuffer(s);
    s = "AttackBonus: " + to_string(attackBonus) + " |";
    Printer::AddStringToBuffer(s);
    s = "DefenceBonus: " + to_string(defenceBonus) + " |";
    Printer::AddStringToBuffer(s);
    s = "MinimumHonour: " + to_string(minimumHonour) + " |";
    Printer::AddStringToBuffer(s);
    s = "EffectBonus: " + to_string(effectBonus) + " |";
    Printer::AddStringToBuffer(s);
    s = "EffectCost: " + to_string(effectCost) + " |";
    Printer::AddStringToBuffer(s);
}

void GreenCard::Upgrade()
{
    attackBonus += effectBonus;
    defenceBonus += effectBonus;
    cost += effectCost;
}

#ifdef GUI_SUPPORT
void GreenCard::PrintGUICard() const
{
    Card::PrintGUICard();
}
#endif

int GreenCard::getType() const
{
    assert(false);
}

int GreenCard::getAttackBonus() const
{
    return attackBonus;
}

int GreenCard::getDefenceBonus() const
{
    return defenceBonus;
}

int GreenCard::getMinimumHonour() const
{
    return minimumHonour;
}

int GreenCard::getEffectBonus() const
{
    return effectBonus;
}

int GreenCard::getEffectCost() const
{
    return effectCost;
}
