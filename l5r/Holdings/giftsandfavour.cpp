#include "giftsandfavour.h"

GiftsandFavour::GiftsandFavour(string iName) : Holding(iName)
{
    cost = 2;
    harvestValue = 2;
    holdingType = HOLDING_TYPE_GANDF;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::giftsandfavour;
#endif
}
