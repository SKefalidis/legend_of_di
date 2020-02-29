#include "province.h"
#include "personality.h"
#include "follower.h"
#include "holding.h"
#include "printer.h"
#include "item.h"
#include "TypeConverter.hpp"

using namespace std;


Province::Province(string iName)
{
    name = iName;
    card = nullptr;
    isDestroyed = false;
}

Province::~Province()
{
    delete card;
}

void Province::AddAttacker(Personality *attacker)
{
    attackers.push_back(attacker);
}

void Province::AddDefender(Personality *defender)
{
    defenders.push_back(defender);
}

/* Combat logic.
 * Returns: -2 if the province is destroyed,
 *          -1 if the defenders lose but the province stays,
 *          0 if the battle is a stalemate,
 *          +1 if the defenders win,
 *          +2 if there is no attack
 */
int Province::SimulateBattle()
{
    int attackPoints = 0, defencePoints = staticDefence, result = 0;    //defence uses the chosen strongholds defence as the starting value

    TypeConverter tc;
    Holding** holdingBought = new Holding*;
    Personality** personalityBought = new Personality*;
    if(card != nullptr) {
        tc.getCorrectType(card, personalityBought, holdingBought);
        if(*personalityBought != nullptr){
            defencePoints += (*personalityBought)->getDefence(); //defence also uses the unbought personality, if such exists
        }
    }

    if(attackers.size() > 0)
    {
        for(auto &x : attackers)
        {
            attackPoints += x->getAttack();
            for(auto &item : x->getItems())
            {
                item->Use();
            }
        }
        for(auto &x : defenders)
        {
            defencePoints += x->getDefence();
        }
        cout << "Attacking Power: " << attackPoints << endl;
        cout << "Defending Power: " << defencePoints << endl;
        if(attackPoints - defencePoints > staticDefence) //if the attackers won by a significant margin
        {
            cout << "Overwhelming victory for the attacking forces!" << endl;
            //all defenders die in battle
            for(auto &x : defenders)
            {
                x->DecrementHonour(1);
                if(x->getHonour() == 0)
                    x->PerformSeppuku();
                x->Kill();
            }
            //the province is destroyed
            this->Destroy();
            result = -2;
        }else if(attackPoints > defencePoints)  //the attackers won, but not by a margin large enough to destroy the province
        {
            cout << "Victory for the attacking forces!" << endl;
            //all defenders die in battle
            for(auto &x : defenders)
            {
                x->DecrementHonour(1);
                if(x->getHonour() == 0)
                    x->PerformSeppuku();
                x->Kill();
            }
            //the attackers lose units of value >= attack - defence
            RandomlyKillUnits(attackers, defencePoints / 2);
            result = -1;
        }else if(attackPoints == defencePoints)
        {
            cout << "Stalemate" << endl;
            //all defenders die in battle
            for(auto &x : defenders)
            {
                x->Kill();
            }
            //all attackers die in battle
            for(auto &x : attackers)
            {
                x->Kill();
            }
            result = 0;
        }else if(attackPoints < defencePoints)
        {
            cout << "Victory for the defending forces!" << endl;
            //the defenders lose units of value >= defence - attack
            if(defenders.size() > 0) //the static defense might win by itself
                RandomlyKillUnits(defenders, attackPoints / 2);
            //all attackers die in battle
            for(auto &x : attackers)
            {
                x->DecrementHonour(1);
                if(x->getHonour() == 0)
                    x->PerformSeppuku();
                x->Kill();
            }
            result = 1;
        }
    }else{
        result = 2;
    }

    attackers.clear();
    defenders.clear();
    delete holdingBought;
    delete personalityBought;
    return result;
}

//srand setup in the main function
int Province::RandomlyKillUnits(vector<Personality *> army, int minValueToKill)
{
    int i = 0, j = 0;
    int valueKilled = 0;
    while(valueKilled < minValueToKill)
    {
        if(army.size() > 0)
        {
            i = rand() % army.size(); //personality to kill (or it's followers)
            if(army.at(i)->getFollowers().size() > 0)
            {
                j = rand() % (1 + army.at(i)->getFollowers().size()); //used to determine whether to kill the personality or a follower
                if(j == army.at(i)->getFollowers().size() && army.at(i)->getIsDead() == false)
                {
                    //kill personality (all followers are lost because they were gathered under that personality)
                    valueKilled += army.at(i)->getCost();
                    for(auto &x : army.at(i)->getFollowers())
                    {
                        valueKilled += x->getCost();
                    }
                    army.at(i)->Kill();
                }
                else
                {
                    //kill follower
                    if(army.at(i)->getFollowers().at(j)->getIsDead() == false)
                    {
                        valueKilled += army.at(i)->getFollowers().at(j)->getCost();
                        army.at(i)->getFollowers().at(j)->Kill();
                    }
                }
            }else if(army.at(i)->getIsDead() == false){ //the personality has no followers, kill the personality
                valueKilled += army.at(i)->getCost();
                army.at(i)->Kill();
            }
        }else
        {
            //if the army has no personalities (should never be called), exit
            break;
        }

        //if all units are dead it's over
        bool allDead = true;
        for(auto& x : army)
        {
            if(x->getIsDead() == false)
            {
                allDead = false;
                break;
            }
        }
        if(allDead)
            break;
    }
    return valueKilled;
}

void Province::Destroy()
{
    cout << name << " has been destroyed." << endl;
    isDestroyed = true;
}

void Province::Print() const
{
    cout << "Province: " << name << endl;
}

void Province::AddToPrintBuffer() const
{
    string s = "";
    s = "Province Name: " + name + " |";
    Printer::AddStringToBuffer(s);
    card->AddToPrintBuffer();
}

bool Province::getIsDestroyed() const
{
    return isDestroyed;
}

void Province::setStaticDefence(int value)
{
    staticDefence = value;
}

vector<Personality *> Province::getAttackers() const
{
    return attackers;
}

vector<Personality *> Province::getDefenders() const
{
    return defenders;
}
