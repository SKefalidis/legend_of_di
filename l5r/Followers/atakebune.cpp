#include "atakebune.h"

Atakebune::Atakebune(string iName) : Follower(iName)
{
    cost = 3;
    attackBonus = 2;
    defenceBonus = 4;
    minimumHonour = 3;
    effectBonus = 3;
    effectCost = 4;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::atakebune;
#endif
}
