#include <iostream>
#include <iomanip>
#include <string>
#include "item.h"
#include "printer.h"
#include "assert.h"
#include "terminal_colours.h"

using namespace std;

int Item::getDurability() const
{
    return durability;
}

Item::Item(string iName) : GreenCard(iName)
{
    durability = 1;
    isDestroyed = false;
}

void Item::PrintCard() const
{
    GreenCard::PrintCard();
    cout << "|" << setw(CARD_WIDTH - 2) << "Durability" + to_string(durability) << "|" << endl;
    PrintHorizontalBorder();
    COLOUR_REGION_END; //Started in GreenCard::PrintCard();
}

void Item::AddToPrintBuffer() const
{
    string s;
    GreenCard::AddToPrintBuffer();
    s = "Durability: " + to_string(durability) + " |";
    Printer::AddStringToBuffer(s);
    s = "";
    AddHorizontalBorderToPrintBuffer();
}

void Item::Use()
{
    assert(isDestroyed == false);
    durability--;
    if(durability <= 0)
    {
        isDestroyed = true;
    }
}

bool Item::getIsDestroyed() const
{
    return isDestroyed;
}

int Item::getType() const
{
    return CardType::item;
}
