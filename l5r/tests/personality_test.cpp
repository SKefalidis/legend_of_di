#ifdef TESTS
#include "catch.hpp"
#include "../Personalities/personalities.h"
#include "../Followers/followers.h"
#include "../Items/items.h"

TEST_CASE("Adding followers till the max count. 3 is the max count of followers", "[test]"){
    Attacker p("P");
    Archer a("A");

    REQUIRE(p.AddFollower(&a) == 0);
    REQUIRE(p.AddFollower(&a) == 0);
    REQUIRE(p.AddFollower(&a) == 0);
    REQUIRE(p.AddFollower(&a) == -1); //not enough space
}

TEST_CASE("Adding follower with too high honour should get rejected"){
    Attacker p("P");
    Bushido b("B");

    REQUIRE(p.AddFollower(&b) == -1); //not enough honor
}

TEST_CASE("Adding items till the max count. 3 is the max count of followers", "[test]"){
    Attacker p("P");
    Bow a("A");
    Katana b("B");

    REQUIRE(p.AddItem(&a) == 0);
    REQUIRE(p.AddItem(&a) == 0);
    REQUIRE(p.AddItem(&a) == 0);
    REQUIRE(p.AddItem(&a) == -1); //not enough space
}

TEST_CASE("Adding item with too high honour should get rejected"){
    Attacker p("P");
    Ninjato b("B");

    REQUIRE(p.AddItem(&b) == -1); //not enough honor
}

TEST_CASE("Detaching one item at the given index.", "[test]"){
    Attacker p("P");
    Bow a("A");
    Bow b("B");

    REQUIRE(p.AddItem(&a) == 0);
    REQUIRE(p.AddItem(&b) == 0);
    REQUIRE(p.getItems().at(0) == &a);
    p.DetachItem(0);
    REQUIRE(p.getItems().at(0) == &b);
}

TEST_CASE("Detaching one follower at the given index.", "[test]"){
    Attacker p("P");
    Archer a("A");
    Archer b("B");

    REQUIRE(p.AddFollower(&a) == 0);
    REQUIRE(p.AddFollower(&b) == 0);
    REQUIRE(p.getFollowers().at(0) == &a);
    p.DetachFollower(0);
    REQUIRE(p.getFollowers().at(0) == &b);
}

TEST_CASE("Marking items/followers as dead/destroyed should remove them from my vectors.", "[test]"){
    Attacker p("P");
    Archer a("A");
    Archer b("B");
    Bow c("C");
    Bow d("D");

    REQUIRE(p.AddFollower(&a) == 0);
    REQUIRE(p.AddFollower(&b) == 0);
    REQUIRE(p.AddItem(&c) == 0);
    REQUIRE(p.AddItem(&d) == 0);

    REQUIRE(p.getFollowers().size() == 2);
    a.Kill();
    p.CleanCasualties();
    REQUIRE(p.getFollowers().size() == 1);

    REQUIRE(p.getItems().size() == 2);
    for(int i = 0, j = c.getDurability(); i < j; i++){
        c.Use();
    }
    p.CleanCasualties();
    REQUIRE(p.getItems().size() == 1);
}
#endif
