#ifndef PERSONALITY_H
#define PERSONALITY_H

#include <vector>
#include "black_card.h"

#define MAX_ITEM_COUNT 3
#define MAX_FOLLOWER_COUNT 3

using std::vector;

class Follower;
class Item;

class Personality : public BlackCard
{
protected:
    int attack;
    int defence;
    int honour;
    bool isDead;
    vector<Item*> items;
    vector<Follower*> followers;
public:
    Personality(string iName);
    void Kill();
    void PerformSeppuku();
    void PrintCard() const override;
    void AddToPrintBuffer() const override;
    int AddFollower(Follower* follower);//Create a system where attackers from different clans cooperate.
    int AddItem(Item* item);//Create a system where defenders from different clans cooperate.
    void DetachItem(int i);
    void DetachFollower(int i);
    void CleanCasualties();

    void IncrementHonour(int i);
    void DecrementHonour(int i);
    int getHonour() const;
    int getType() const override;
    int getAttack() const;
    int getDefence() const;
    vector<Item *> getItems() const;
    bool getIsDead() const;
    vector<Follower *> getFollowers() const;

#ifdef GUI_SUPPORT
    void PrintGUICard() const override;
#endif
};

#endif // PERSONALITY_H
