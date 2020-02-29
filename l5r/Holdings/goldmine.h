#ifndef GOLDMINE_H
#define GOLDMINE_H

#include "../holding.h"

#define HOLDING_TYPE_GMINE "GOLD_MINE"
#define GM_VALUE 5
#define GM_COMPLETE_CONNECTION_VALUE (GM_VALUE*2)
#define GM_UPPER_CONNECTION_VALUE 5
#define GM_SUB_CONNECTION_VALUE 4

class GoldMine : public Holding
{
public:
    GoldMine(string iName);
    void SetSubHolding(Holding *other) override;
    void SetUpperHolding(Holding *other) override;
};

#endif // GOLDMINE_H
