#ifndef PROVINCE_H
#define PROVINCE_H
#include <iostream>
#include <vector>

using std::string;
using std::vector;

class BlackCard;
class Personality;

class Province
{
private:
    string name;
    bool isDestroyed;
    int staticDefence;//stronghold defence

    vector<Personality*> attackers;
    vector<Personality*> defenders;
public:
    BlackCard* card; //move to private? It's very convenient to leave this public.
    Province(string iName);
    ~Province();
    void AddAttacker(Personality* attacker);//Create a system where attackers from different clans cooperate.
    void AddDefender(Personality* defender);//Create a system where defenders from different clans cooperate.
    int SimulateBattle();
    int RandomlyKillUnits(vector<Personality*> army, int minValueToKill);
    void Destroy();
    void Print() const;
    void AddToPrintBuffer() const;
    bool getIsDestroyed() const;
    void setStaticDefence(int value);
    vector<Personality *> getAttackers() const;
    vector<Personality *> getDefenders() const;
};

#endif // PROVINCE_H
