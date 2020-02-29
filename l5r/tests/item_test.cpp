#ifdef TESTS
#include "catch.hpp"
#include "../Items/items.h"

TEST_CASE("When durability reaches 0, the item should be marked as destroyed.", "[test]"){
    Bow a("A");
    REQUIRE(a.getIsDestroyed() == false);
    for(int i = 0, j = a.getDurability(); i < j; i++){
        a.Use();
    }
    REQUIRE(a.getIsDestroyed() == true);
}
#endif
