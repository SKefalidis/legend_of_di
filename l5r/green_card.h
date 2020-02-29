#ifndef GREENCARD_H
#define GREENCARD_H

#include "card.h"

class GreenCard : public Card
{
protected:
    int attackBonus;
    int defenceBonus;
    int minimumHonour;
    int effectBonus;
    int effectCost;
    string cardText;
public:
    GreenCard(string iName);
    virtual int getType() const override;
    virtual void PrintCard() const override;
    virtual void AddToPrintBuffer() const override;
    void Upgrade();
    int getAttackBonus() const;
    int getDefenceBonus() const;
    int getMinimumHonour() const;
    int getEffectBonus() const;
    int getEffectCost() const;

#ifdef GUI_SUPPORT
    virtual void PrintGUICard() const override;
#endif
};

#endif // GREENCARD_H
