
cmake_minimum_required(VERSION 3.5)

project(untitled LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( project_sources
   main.cpp
   DeckBuilder.cpp
   DeckBuilder.hpp
   TypeConverter.cpp
   TypeConverter.hpp
   card.cpp
   card.h
   green_card.cpp
   green_card.h
   black_card.cpp
   black_card.h
   follower.cpp
   follower.h
   item.cpp
   item.h
   holding.cpp
   holding.h
   personality.cpp
   personality.h
   Items/items.h
   Items/katana.cpp
   Items/katana.h
   Items/spear.cpp
   Items/spear.h
   Items/bow.cpp
   Items/bow.h
   Items/ninjato.cpp
   Items/ninjato.h
   Items/wakizashi.cpp
   Items/wakizashi.h
   Followers/footsoldier.cpp
   Followers/footsoldier.h
   Followers/archer.cpp
   Followers/archer.h
   Followers/cavalry.cpp
   Followers/cavalry.h
   Followers/bushido.cpp
   Followers/bushido.h
   Followers/sieger.cpp
   Followers/sieger.h
   Followers/atakebune.cpp
   Followers/atakebune.h
   Followers/followers.h
   Personalities/attacker.cpp
   Personalities/attacker.h
   Personalities/defender.cpp
   Personalities/defender.h
   Personalities/champion.cpp
   Personalities/champion.h
   Personalities/chancellor.cpp
   Personalities/chancellor.h
   Personalities/shogun.cpp
   Personalities/shogun.h
   Personalities/personalities.h
   Holdings/plain.cpp
   Holdings/plain.h
   Holdings/mine.cpp
   Holdings/mine.h
   Holdings/goldmine.cpp
   Holdings/goldmine.h
   Holdings/crystalmine.cpp
   Holdings/crystalmine.h
   Holdings/farmland.cpp
   Holdings/farmland.h
   Holdings/giftsandfavour.cpp
   Holdings/giftsandfavour.h
   Holdings/stronghold.cpp
   Holdings/stronghold.h
   Holdings/holdings.h
   game_manager.cpp
   game_manager.h
   player.cpp
   player.h
   terminal_colours.h
   printer.cpp
   printer.h
   province.cpp
   province.h
   ../image_files_enum.h

   #tests
   tests/tests_setup.cpp
   tests/catch.hpp
   tests/player_test.cpp
   tests/game_manager_test.cpp
   tests/item_test.cpp
   tests/personality_test.cpp
   tests/province_test.cpp
)

add_definitions(-DLINUX)
add_definitions(-DGUI_SUPPORT)
#add_definitions(-DTESTS)

add_executable(l5r ${project_sources})
