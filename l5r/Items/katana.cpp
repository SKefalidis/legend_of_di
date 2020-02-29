#include "katana.h"

Katana::Katana(string iName) : Item(iName)
{
    cost = 0;
    attackBonus = 2;
    defenceBonus = 0;
    minimumHonour = 1;
    effectBonus = 1;
    effectCost = 2;
    durability = 3;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::katana;
#endif
}
