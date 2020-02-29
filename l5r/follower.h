#ifndef FOLLOWER_H
#define FOLLOWER_H

#include "green_card.h"

class Follower : public GreenCard
{
    bool isDead;
public:
    Follower(string iName) : GreenCard(iName){};
    void Kill();
    int getType() const override;
    void PrintCard() const override;
    void AddToPrintBuffer() const override;
    bool getIsDead() const;
};

#endif // FOLLOWER_H
