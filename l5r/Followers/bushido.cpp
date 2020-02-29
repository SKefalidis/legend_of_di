#include "bushido.h"

Bushido::Bushido(string iName) : Follower(iName)
{
    cost = 8;
    attackBonus = 8;
    defenceBonus = 8;
    minimumHonour = 6;
    effectBonus = 3;
    effectCost = 8;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::bushido;
#endif
}
