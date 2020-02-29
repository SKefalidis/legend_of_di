#include <iostream>
#include "follower.h"
#include "printer.h"
#include "terminal_colours.h"

using namespace std;


void Follower::Kill()
{
    cout << name << " died in battle!" << endl;
    isDead = true;
}

void Follower::PrintCard() const
{
    GreenCard::PrintCard();
    PrintHorizontalBorder();
    COLOUR_REGION_END; //Started in GreenCard::PrintCard();
}

void Follower::AddToPrintBuffer() const
{
    string s = "|";
    GreenCard::AddToPrintBuffer();
    Printer::AddStringToBuffer(s);
    AddHorizontalBorderToPrintBuffer();
}

bool Follower::getIsDead() const
{
    return isDead;
}

int Follower::getType() const
{
    return CardType::follower;
}
