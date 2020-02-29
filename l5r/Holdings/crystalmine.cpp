#include "crystalmine.h"
#include "goldmine.h"
#include <assert.h>

CrystalMine::CrystalMine(string iName) : Holding(iName)
{
    cost=12;
    harvestValue = CM_VALUE;
    holdingType = HOLDING_TYPE_CMINE;
    subHoldingType = HOLDING_TYPE_GMINE;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::crystal_mine;
#endif
}

void CrystalMine::SetSubHolding(Holding *other)
{
    Holding::SetSubHolding(other);
    harvestValue = CM_SUB_CONNECTION_VALUE;
}

void CrystalMine::SetUpperHolding(Holding *other)
{
    assert(false);
}

void CrystalMine::CheckCompleteConnection()
{
    if(subHolding != nullptr)
    {
        if(subHolding->getSubHolding() != nullptr)
        {
            harvestValue = COMPLETE_CHAIN_VALUE;
        }
    }
}
