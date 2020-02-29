#include "shogun.h"

Shogun::Shogun(string iName)  : Personality(iName)
{
    cost = 15;
    attack = 10;
    defence = 5;
    honour = 8;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::shogun;
#endif
}
