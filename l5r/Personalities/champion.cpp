#include "champion.h"

Champion::Champion(string iName)  : Personality(iName)
{
    cost = 30;
    attack = 20;
    defence = 20;
    honour = 12;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::champion;
#endif
}
