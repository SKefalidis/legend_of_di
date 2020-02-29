#ifndef CRYSTALMINE_H
#define CRYSTALMINE_H

#include "../holding.h"

#define HOLDING_TYPE_CMINE "CRYSTAL_MINE"
#define CM_VALUE 6
#define CM_SUB_CONNECTION_VALUE (CM_VALUE * 2)
#define COMPLETE_CHAIN_VALUE (CM_VALUE * 3)

class CrystalMine : public Holding
{
public:
    CrystalMine(string iName);
    void SetSubHolding(Holding *other) override;
    void SetUpperHolding(Holding *other) override;
    void CheckCompleteConnection();
};

#endif // CRYSTALMINE_H
