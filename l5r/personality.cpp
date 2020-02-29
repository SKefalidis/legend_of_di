#include <iostream>
#include <iomanip>
#include "personality.h"
#include "follower.h"
#include "item.h"
#include "printer.h"
#include "terminal_colours.h"

using namespace std;

Personality::Personality(string iName) : BlackCard(iName)
{
    attack = -1;
    defence = -1;
    honour = -1;
    isDead = false;
}

void Personality::Kill()
{
    cout << name << " died in battle!" << endl;
    isDead = true;
}

void Personality::PerformSeppuku()
{
    cout << name << " commited seppuku!" << endl;
    isDead = true;
}

void Personality::PrintCard() const
{
    BlackCard::PrintCard();
    if(isRevealed)
    {
        cout << "|" << setw(CARD_WIDTH - 2) << "Attack: " + to_string(attack) << "|" << endl;
        cout << "|" << setw(CARD_WIDTH - 2) << "Defence: " + to_string(defence) << "|" << endl;
        cout << "|" << setw(CARD_WIDTH - 2) << "Honour: " + to_string(honour) << "|" << endl;
        PrintHorizontalBorder();
    }
    COLOUR_REGION_END; //Started in BlackCard::PrintCard();
}

void Personality::AddToPrintBuffer() const
{
    BlackCard::AddToPrintBuffer();
    string s = "";
    if(isRevealed)
    {
        s = "Attack: " + to_string(attack) + " |";
        Printer::AddStringToBuffer(s);
        s = "Defence: " + to_string(defence) + " |";
        Printer::AddStringToBuffer(s);
        s = "Honour: " + to_string(honour) + " |";
        Printer::AddStringToBuffer(s);
    }else
    {
        s = "NOT REVEALED |";
        Printer::AddStringToBuffer(s);
        Printer::AddStringToBuffer(s);
        Printer::AddStringToBuffer(s);
    }
    AddHorizontalBorderToPrintBuffer();
}

int Personality::AddFollower(Follower *follower)
{
    if(honour >= follower->getMinimumHonour() && followers.size() < MAX_FOLLOWER_COUNT)
    {
        attack += follower->getAttackBonus();
        defence += follower->getDefenceBonus();
        followers.push_back(follower);
        return 0;
    }
    else
    {
        cout << "Not enough honour or space." << endl;
        return -1;
    }
}

int Personality::AddItem(Item *item)
{
    if(honour >= item->getMinimumHonour() && items.size() < MAX_ITEM_COUNT)
    {
        attack += item->getAttackBonus();
        defence += item->getDefenceBonus();
        items.push_back(item);
        return 0;
    }
    else
    {
        cout << "Not enough honour or space." << endl;
        return -1;
    }
}

void Personality::DetachItem(int i)
{
    items.erase(items.begin() + i);
}

void Personality::DetachFollower(int i)
{
    followers.erase(followers.begin() + i);
}

void Personality::CleanCasualties()
{
    for(int i = 0; i < items.size(); i++)
    {
        if(items.at(i)->getIsDestroyed() == true)
        {
            DetachItem(i);
        }
    }
    for(int i = 0; i < followers.size(); i++)
    {
        if(followers.at(i)->getIsDead() == true)
        {
            DetachFollower(i);
        }
    }
}

#ifdef GUI_SUPPORT
void Personality::PrintGUICard() const
{
    if(isRevealed)
    {
        ofstream inputFile;
        inputFile.open(INPUT_PATH, ios::out | ios::app);
        inputFile << id << /*" Name: " << name <<*/ " Cost: " << cost << " Attack: " << attack << " Defence: " << defence << " Honour: " << honour << " END" << endl;
        inputFile.close();
    }else
    {
        BlackCard::PrintGUICard();
    }
}
#endif

int Personality::getAttack() const
{
    return attack;
}

int Personality::getDefence() const
{
    return defence;
}

int Personality::getType() const
{
    return CardType::personality;
}

vector<Item *> Personality::getItems() const
{
    return items;
}

bool Personality::getIsDead() const
{
    return isDead;
}

vector<Follower *> Personality::getFollowers() const
{
    return followers;
}

int Personality::getHonour() const
{
    return honour;
}

void Personality::IncrementHonour(int i)
{
    honour += i;
}

void Personality::DecrementHonour(int i)
{
    honour -= i;
}
