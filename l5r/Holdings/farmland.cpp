#include "farmland.h"

Farmland::Farmland(string iName) : Holding(iName)
{
    cost = 3;
    harvestValue = 4;
    holdingType = HOLDING_TYPE_FARMLAND;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::farmland;
#endif
}
