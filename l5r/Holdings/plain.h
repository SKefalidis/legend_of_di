#ifndef PLAIN_H
#define PLAIN_H

#include "../holding.h"

#define HOLDING_TYPE_PLAIN "PLAIN"

class Plain : public Holding
{
public:
    Plain(string iName);
};

#endif // PLAIN_H
