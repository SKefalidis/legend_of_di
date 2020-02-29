#include <iostream>
#include <iomanip>
#include "holding.h"
#include "printer.h"
#include "terminal_colours.h"

using namespace std;

Holding::Holding(string iName) : BlackCard(iName)
{
    harvestValue = -1;
    upperHoldingType = HOLDING_TYPE_NONE;
    upperHolding = nullptr;
    subHoldingType = HOLDING_TYPE_NONE;
    subHolding = nullptr;
}

void Holding::PrintCard() const
{
    BlackCard::PrintCard();
    if(isRevealed)
    {
        cout << "|" << setw(CARD_WIDTH - 2) << "Harvest Value: " + to_string(harvestValue) << "|" << endl;
        if(upperHolding != nullptr)
        {
            cout << "|" << setw(CARD_WIDTH - 2) << "Upper Holding: Connected" << "|" << endl;
        }else
        {
            cout << "|" << setw(CARD_WIDTH - 2) << "Upper Holding: Empty" << "|" << endl;
        }
        if(subHolding != nullptr)
        {
            cout << "|" << setw(CARD_WIDTH - 2) << "Sub-Holding: Connected" << "|" << endl;
        }else
        {
            cout << "|" << setw(CARD_WIDTH - 2) << "Sub-Holding: Empty" << "|" << endl;
        }
        PrintHorizontalBorder();
    }
    COLOUR_REGION_END;//Started in BlackCard::PrintCard();
}

void Holding::AddToPrintBuffer() const
{
    BlackCard::AddToPrintBuffer();
    string s = "";
    if(isRevealed)
    {
        s = "Harvest Value: " + to_string(harvestValue) + " |" ;
        Printer::AddStringToBuffer(s);
        if(upperHolding != nullptr)
        {
            s = "Upper Holding: Connected |";
            Printer::AddStringToBuffer(s);
        }else
        {
            s = "Upper Holding: Empty |";
            Printer::AddStringToBuffer(s);
        }
        if(subHolding != nullptr)
        {
            s = "Sub-Holding: Connected |";
            Printer::AddStringToBuffer(s);
        }else
        {
            s = "Sub-Holding: Empty |";
            Printer::AddStringToBuffer(s);
        }
    }else
    {
        s = "NOT REVEALED |";
        Printer::AddStringToBuffer(s);
        Printer::AddStringToBuffer(s);
        Printer::AddStringToBuffer(s);
    }
    AddHorizontalBorderToPrintBuffer();
}

void Holding::SetUpperHolding(Holding *other)
{
    upperHolding = other;
    if(other->subHolding == nullptr)
    {
        other->subHolding = this;
    }
}

void Holding::SetSubHolding(Holding *other)
{
    subHolding = other;
    if(other->upperHolding == nullptr)
    {
        other->upperHolding = this;
    }
}

#ifdef GUI_SUPPORT
void Holding::PrintGUICard() const
{
    if(isRevealed)
    {
        ofstream inputFile;
        inputFile.open(INPUT_PATH, ios::out | ios::app);
        inputFile << id << /*" Name: " << name <<*/ " Cost: " << cost << " Value: " << harvestValue << " END" << endl;
        inputFile.close();
    }else
    {
        BlackCard::PrintGUICard();
    }
}
#endif

int Holding::getType() const
{
    return CardType::holding;
}

int Holding::getHarvestValue() const
{
    return harvestValue;
}

string Holding::getHoldingType() const
{
    return holdingType;
}

string Holding::getUpperHoldingType() const
{
    return upperHoldingType;
}

string Holding::getSubHoldingType() const
{
    return subHoldingType;
}

Holding *Holding::getUpperHolding() const
{
    return upperHolding;
}

Holding *Holding::getSubHolding() const
{
    return subHolding;
}
