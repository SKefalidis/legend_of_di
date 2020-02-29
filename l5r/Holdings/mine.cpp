#include "mine.h"
#include "goldmine.h"
#include <assert.h>

Mine::Mine(string iName) : Holding(iName)
{
    cost = 5;
    harvestValue = M_VALUE;
    holdingType = HOLDING_TYPE_MINE;
    upperHoldingType = HOLDING_TYPE_GMINE;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::mine;
#endif
}

void Mine::SetUpperHolding(Holding *other)
{
    Holding::SetUpperHolding(other);
    harvestValue += M_UPPER_CONNECTION_VALUE;
}

void Mine::SetSubHolding(Holding *other)
{
    assert(false);  //there is no subholding
}
