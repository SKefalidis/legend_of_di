#ifndef MINE_H
#define MINE_H

#include "../holding.h"

#define HOLDING_TYPE_MINE "MINE"
#define M_VALUE 3;
#define M_UPPER_CONNECTION_VALUE 2

class Mine : public Holding
{
public:
    Mine(string iName);
    void SetUpperHolding(Holding *other) override;
    void SetSubHolding(Holding *other) override;
};

#endif // MINE_H
