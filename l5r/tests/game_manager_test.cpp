#ifdef TESTS
#include <iostream>
#include "catch.hpp"
#define private public
#define protected public
#include "../game_manager.h"
#include "../province.h"
#include "../player.h"

TEST_CASE("CheckWinningCondition returns the index of the player who won.", "[test]"){
    GameManager gm;
    Player a(0);
    Province* a1 = new Province("North");
    a.honour = 3;
    a.provinces.push_back(a1);
    Player b(1);
    b.honour = 5;
    Player c(2);
    c.honour = 2;
    gm.players.push_back(&a);
    gm.players.push_back(&b);
    gm.players.push_back(&c);
    REQUIRE(gm.players.at(0)->getNumberOfProvinces() == 1);
    REQUIRE(gm.players.at(1)->getNumberOfProvinces() == 0);
    REQUIRE(gm.players.at(2)->getNumberOfProvinces() == 0);
    REQUIRE(gm.CheckWinningCondition() == 0);
    gm.SortByHonour();
    REQUIRE(gm.CheckWinningCondition() == 1);
    gm.players.clear(); //gm is static!!!
}

TEST_CASE("CheckWinningCondition mutual destruction, highest honour wins.", "[test]"){
    GameManager gm;
    Player a(0);
    Province* a1 = new Province("North");
    a.honour = 3;
    a.provinces.push_back(a1);
    Player b(1);
    b.honour = 5;
    Player c(2);
    c.honour = 17;
    gm.players.push_back(&a);
    gm.players.push_back(&b);
    gm.players.push_back(&c);
    gm.SortByHonour();
    REQUIRE(gm.CheckWinningCondition() == 2);
    gm.players.clear(); //gm is static!!!
}

TEST_CASE("Testing sorting by honour.", "[test]"){
    GameManager gm;
    Player a(0);
    a.honour = 3;
    Player b(1);
    b.honour = 1;
    Player c(2);
    c.honour = 2;
    gm.players.push_back(&a);
    gm.players.push_back(&b);
    gm.players.push_back(&c);
    REQUIRE(gm.players.at(0) == &a);
    REQUIRE(gm.players.at(1) == &b);
    REQUIRE(gm.players.at(2) == &c);
    gm.SortByHonour();
    REQUIRE(gm.players.at(0) == &a);
    REQUIRE(gm.players.at(1) == &c);
    REQUIRE(gm.players.at(2) == &b);
}
#endif
