#include "cavalry.h"

Cavalry::Cavalry(string iName) : Follower(iName)
{
    cost = 3;
    attackBonus = 4;
    defenceBonus = 2;
    minimumHonour = 3;
    effectBonus = 3;
    effectCost = 4;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::cavalry;
#endif
}
