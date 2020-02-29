#include "ninjato.h"

Ninjato::Ninjato(string iName) : Item(iName)
{
    cost = 4;
    attackBonus = 3;
    defenceBonus = 3;
    minimumHonour = 3;
    effectBonus = 2;
    effectCost = 2;
    durability = 4;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::ninjato;
#endif
}
