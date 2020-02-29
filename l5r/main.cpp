#include <iostream>
#include "game_manager.h"
#include "player.h"
#include "printer.h"

using namespace std;
#ifndef TESTS
int main(int argc, char** argv)
{
    GameManager gm;

    if(argc > 2){
        cout << "Incorrect amount of arguments, the correct way to start the program is: l5r <player_count>" << endl;
        return -2;
    }

    srand(unsigned(time(nullptr))); //used by the DeckBuilder of each player.
#ifdef GUI_SUPPORT
    //Starts the GUI application
    int a = system("../build-qt_l5r-Desktop_Qt_5_14_1_GCC_64bit-Debug/qt_l5r &");//the & in the end says "run in the background"
    int b = system("../qt_l5r/qt_l5r &");//the & in the end says "run in the background"
#endif
    if(argc == 1)
        gm.InitializeGameBoard(2);
    else
        gm.InitializeGameBoard(stoi(argv[1]));
    gm.GamePlay();
    return 0;
}
#endif
//IMPORTANT: If a player has won, he needs end his turn to end the game.
