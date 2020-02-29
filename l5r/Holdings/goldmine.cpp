#include "goldmine.h"
#include "mine.h"
#include "crystalmine.h"

GoldMine::GoldMine(string iName) : Holding(iName)
{
    cost = 7;
    harvestValue = GM_VALUE;
    holdingType = HOLDING_TYPE_GMINE;
    upperHoldingType = HOLDING_TYPE_CMINE;
    subHoldingType = HOLDING_TYPE_MINE;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::gold_mine;
#endif
}

void GoldMine::SetSubHolding(Holding *other)
{
    Holding::SetSubHolding(other);
    if(upperHolding == nullptr)
    {
        harvestValue += GM_SUB_CONNECTION_VALUE;
    }else
    {
        harvestValue = GM_COMPLETE_CONNECTION_VALUE;
    }
}

void GoldMine::SetUpperHolding(Holding *other)
{
    Holding::SetUpperHolding(other);
    if(subHolding == nullptr)
    {
        harvestValue += GM_UPPER_CONNECTION_VALUE;
    }else
    {
        harvestValue = GM_COMPLETE_CONNECTION_VALUE;
    }
}
