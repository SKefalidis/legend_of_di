#ifdef TESTS
#include <iostream>
#include <algorithm>
#include <string>
#include "catch.hpp"
#define private public
#define protected public
#include "../card.h"
#include "../province.h"
#include "../Holdings/holdings.h"
#include "../Personalities/personalities.h"
#include "../game_manager.h"
#include "../TypeConverter.hpp"
#include "../player.h"
#include "../Followers/followers.h"

TEST_CASE("Setup player.", "[test-memory]"){
    Player a(0);
    a.SetupPlayer();
}

TEST_CASE("Running out of fate cards.", "[test-memory]"){
    Player a(0);
    a.SetupPlayer();
    for(int i = 0; i < 60; i++)
        a.DrawFateCard();
}

TEST_CASE("Cleaning casualties with no casualtie should do nothing.", "[test]"){
    Player a(0);
    a.provinces.push_back(new Province("North"));
    a.provinces.push_back(new Province("South"));
    Attacker aa("A"), ab("B");
    a.BuyPersonality(&aa);
    a.BuyPersonality(&ab);
    Archer fa("Archer");
    a.army.at(1)->AddFollower(&fa);
    a.CleanCasualties();
    REQUIRE(a.provinces.size() == 2);
    REQUIRE(a.army.size() == 2);
    REQUIRE(a.army.at(1)->followers.size() == 1);
}

TEST_CASE("Cleaning casualties for followers.", "[test]"){
    Player a(0);
    a.provinces.push_back(new Province("North"));
    a.provinces.push_back(new Province("South"));
    Attacker aa("A"), ab("B");
    a.BuyPersonality(&aa);
    a.BuyPersonality(&ab);
    Archer fa("Archer");
    a.army.at(1)->AddFollower(&fa);
    a.army.at(1)->followers.at(0)->Kill();
    a.CleanCasualties();
    REQUIRE(a.provinces.size() == 2);
    REQUIRE(a.army.size() == 2);
    REQUIRE(a.army.at(1)->followers.size() == 0);
}

TEST_CASE("Cleaning casualties for personality with follower.", "[test]"){
    Player a(0);
    a.provinces.push_back(new Province("North"));
    a.provinces.push_back(new Province("South"));
    Attacker aa("A"), ab("B");
    a.BuyPersonality(&aa);
    a.BuyPersonality(&ab);
    Archer fa("Archer");
    a.army.at(1)->AddFollower(&fa);
    a.army.at(1)->Kill();
    a.CleanCasualties();
    REQUIRE(a.provinces.size() == 2);
    REQUIRE(a.army.size() == 1);
}

TEST_CASE("Cleaning casualties for provinces.", "[test]"){
    Player a(0);
    a.provinces.push_back(new Province("North"));
    a.provinces.push_back(new Province("South"));
    a.provinces.at(0)->Destroy();
    Attacker aa("A"), ab("B");
    a.BuyPersonality(&aa);
    a.BuyPersonality(&ab);
    Archer fa("Archer");
    a.army.at(1)->AddFollower(&fa);
    a.CleanCasualties();
    REQUIRE(a.provinces.size() == 1);
    REQUIRE(a.army.size() == 2);
}

TEST_CASE("Basic chain optimization.", "[test]"){
    Player a(0);
    Mine ma("M1");
    a.BuyHolding(&ma);
    a.holdings.at(0)->isTapped = false;
    REQUIRE(a.CalculateAvailableMoney() == a.holdings.at(0)->harvestValue);
    GoldMine gma("GM1");
    a.BuyHolding(&gma);
    a.holdings.at(1)->isTapped = false;
    REQUIRE(a.holdings.at(0)->upperHolding == a.holdings.at(1));
    REQUIRE(a.holdings.at(1)->subHolding == a.holdings.at(0));
    REQUIRE(a.CalculateAvailableMoney() == a.holdings.at(0)->harvestValue + a.holdings.at(1)->harvestValue);
}
#endif

