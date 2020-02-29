#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include "../holding.h"

#define HOLDING_TYPE_STRONGHOLD "STRONGHOLD"

//TODO money different from harvest value?
class Stronghold : public Holding
{
protected:
    int honour;
    int initialDefence;
public:
    Stronghold(string iName);
    void PrintCard() const override;
    int getHonour() const;
    int getInitialDefence() const;

#ifdef GUI_SUPPORT
    void PrintGUICard() const override;
#endif
};

class GreatCity : public Stronghold
{
public:
    GreatCity(string iName);
};

class GreatCastle : public Stronghold
{
public:
    GreatCastle(string iName);
};

class GreatPort : public Stronghold
{
public:
    GreatPort(string iName);
};

#endif // STRONGHOLD_H
