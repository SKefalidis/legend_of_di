#ifdef TESTS
#include "catch.hpp"
#define private public
#define protected public
#include "../province.h"
#include "../Personalities/personalities.h"

TEST_CASE("Adding an attacker should increase the size of the attackers vector by 1.", "[test]"){
    Province myProv("Province");
    Personality* p = new Attacker("Sergios");

    REQUIRE(myProv.getAttackers().size() == 0);
    myProv.AddAttacker(p);
    REQUIRE(myProv.getAttackers().size() == 1);
    delete(p);
}

TEST_CASE("Adding a defender should increase the size of the defenders vector by 1.", "[test]"){
    Province myProv("Province");
    Personality* p = new Defender("Sergios");

    REQUIRE(myProv.getDefenders().size() == 0);
    myProv.AddDefender(p);
    REQUIRE(myProv.getDefenders().size() == 1);
    delete(p);
}

TEST_CASE("Simulating a battle with no attackers does nothing.", "[test]"){
    Province myProv("Province");
    myProv.setStaticDefence(0);
    REQUIRE(myProv.SimulateBattle() == 2);
}

TEST_CASE("Simulating a battle with a static defence stronger than the attackers.", "[test]"){
    Province myProv("Province");
    Attacker a("S");
    myProv.AddAttacker(&a);
    myProv.setStaticDefence(a.getAttack() + 1);
    REQUIRE(myProv.SimulateBattle() == 1);
}

TEST_CASE("Simulating a battle with the defenders stronger than the attackers.", "[test]"){
    Province myProv("Province");
    Attacker a("S");
    Defender d("D");
    myProv.AddAttacker(&a);
    myProv.AddDefender(&d);
    myProv.setStaticDefence(a.getAttack());
    REQUIRE(myProv.SimulateBattle() == 1);
}

TEST_CASE("Simulating a stalemate.", "[test]"){
    Province myProv("Province");
    Attacker a("S");
    Defender d("D");
    myProv.AddAttacker(&a);
    myProv.AddDefender(&d);
    myProv.setStaticDefence(0);
    REQUIRE(myProv.SimulateBattle() == 0);
}

TEST_CASE("Simulating a defender loss.", "[test]"){
    Province myProv("Province");
    Attacker a("S1");
    Attacker b("S2");
    Defender d("D");
    myProv.AddAttacker(&a);
    myProv.AddAttacker(&b);
    myProv.AddDefender(&d);
    myProv.setStaticDefence(a.getAttack() - 1);
    REQUIRE(myProv.SimulateBattle() == -1);
}

TEST_CASE("Simulating an overwhelming defender loss. Province destruction", "[test]"){
    Province myProv("Province");
    Attacker a("S1");
    Attacker b("S2");
    Attacker c("S3");
    Attacker d("S4");
    Defender e("D");
    myProv.AddAttacker(&a);
    myProv.AddAttacker(&b);
    myProv.AddAttacker(&c);
    myProv.AddAttacker(&d);
    myProv.AddDefender(&e);
    myProv.setStaticDefence(a.getAttack() - 1);
    REQUIRE(myProv.SimulateBattle() == -2);
}

TEST_CASE("Randomly kill units with 0 value *should not kill anybody.", "[test]"){
    srand(0);
    Province myProv("Province");
    Attacker a("S1");
    Attacker b("S2");
    Attacker c("S3");
    Attacker d("S4");
    myProv.AddAttacker(&a);
    myProv.AddAttacker(&b);
    myProv.AddAttacker(&c);
    myProv.AddAttacker(&d);
    REQUIRE(myProv.RandomlyKillUnits(myProv.attackers, 0) == 0);
}

TEST_CASE("Randomly kill units with 1 value should only kill 1 unit.", "[test]"){
    srand(0);
    Province myProv("Province");
    Attacker a("S1");
    Attacker b("S2");
    Attacker c("S3");
    Attacker d("S4");
    myProv.AddAttacker(&a);
    myProv.AddAttacker(&b);
    myProv.AddAttacker(&c);
    myProv.AddAttacker(&d);
    myProv.RandomlyKillUnits(myProv.attackers, 1);
}

TEST_CASE("Randomly kill units with max value should kill all units.", "[test]"){
    srand(0);
    Province myProv("Province");
    Attacker a("S1");
    Attacker b("S2");
    Attacker c("S3");
    Attacker d("S4");
    myProv.AddAttacker(&a);
    myProv.AddAttacker(&b);
    myProv.AddAttacker(&c);
    myProv.AddAttacker(&d);
    REQUIRE(myProv.RandomlyKillUnits(myProv.attackers, a.getCost() * 4) == a.getCost() * 4);
}

TEST_CASE("Randomly kill units with max value larger than their value, should kill all units.", "[test]"){
    srand(0);
    Province myProv("Province");
    Attacker a("S1");
    Attacker b("S2");
    Attacker c("S3");
    Attacker d("S4");
    myProv.AddAttacker(&a);
    myProv.AddAttacker(&b);
    myProv.AddAttacker(&c);
    myProv.AddAttacker(&d);
    REQUIRE(myProv.RandomlyKillUnits(myProv.attackers, a.getCost() * 20) == a.getCost() * 4);
}
#endif
