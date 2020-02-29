#ifndef HOLDING_H
#define HOLDING_H

#include "black_card.h"

#define HOLDING_TYPE string
#define HOLDING_TYPE_NONE "NONE"

/* The Holding class has names that are used for chaining holdings.
 */
class Holding : public BlackCard
{
protected:
    int harvestValue;
    string holdingType;
    string upperHoldingType;
    Holding* upperHolding;
    string subHoldingType;
    Holding* subHolding;
public:
    Holding(string iName);
    void PrintCard() const override;
    void AddToPrintBuffer() const override;
    virtual void SetUpperHolding(Holding* other);
    virtual void SetSubHolding(Holding* other);
    int getType() const override;
    int getHarvestValue() const;
    string getHoldingType() const;
    string getUpperHoldingType() const;
    string getSubHoldingType() const;
    Holding *getUpperHolding() const;
    Holding *getSubHolding() const;

#ifdef GUI_SUPPORT
    virtual void PrintGUICard() const override;
#endif
};

#endif // HOLDING_H
