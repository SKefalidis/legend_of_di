#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>

using std::vector;

enum class GamePhase
{
    StartingPhase, //setup
    EquipPhase, //buy green cards and equip your army
    BattlePhase, //send attacking units
    BattlePhase2, //react to incoming attacks
    EconomyPhase, //buy holdings and personalities
    EndPhase //discard cards
};

class Player;

/* Static class. Only one game can be played at a time.
 * Controls the flow of the game. main.cpp gives control to this very quickly.
 * Contains information about players, checks whether somebody won, manages the turns,
 * prints information that has to do with more than one player (that type of information is printed
 * by the player class).
 */
class GameManager
{
public:
    GameManager();
    ~GameManager();
    static void InitializeGameBoard(int numberOfPlayers);   //sets the game up
    static void GamePlay(); //start game
    static void Next(); //called by a player when his turn has ended
    static void PrintArena(); //prints basic player stats
    static void PrintOtherPlayers(Player* exceptThis);
#ifdef GUI_SUPPORT
    static void PrintGUIEnemies(Player* exceptThis);
#endif
    static int getPlayerCount();
    static vector<Player *> getPlayers();
private:
    static GamePhase currentPhase;
    static vector<Player*> players;
    static int currentPlayerIndex;
    static int playerCount;
    static int CheckWinningCondition();
    static void PrintGameStatistics();
    static void NextPhase();
    static void SortByHonour();
};

#endif // GAMEMANAGER_H
