#include "plain.h"

Plain::Plain(string iName) : Holding(iName)
{
    cost = 2;
    harvestValue = 2;
    holdingType = HOLDING_TYPE_PLAIN;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::plain;
#endif
}
