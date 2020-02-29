#ifndef ITEM_H
#define ITEM_H

#include "green_card.h"

class Item : public GreenCard
{
protected:
    int durability;
    bool isDestroyed;
public:
    Item(string iName);
    int getType() const override;
    void PrintCard() const override;
    void AddToPrintBuffer() const override;
    void Use();
    bool getIsDestroyed() const;
    int getDurability() const;
};

#endif // ITEM_H
