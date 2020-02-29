#include "sieger.h"

Sieger::Sieger(string iName) : Follower(iName)
{
    cost = 5;
    attackBonus = 3;
    defenceBonus = 3;
    minimumHonour = 2;
    effectBonus = 2;
    effectCost = 3;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::sieger;
#endif
}
