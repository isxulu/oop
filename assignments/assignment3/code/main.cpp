#include <iostream>
#include <string>
#include "room.h"

int main() {
    Game game;
    game.initialize();
    string whetherQuit;
    while ( 1 ) {
        cout << "Get ready. The rescue operation is about to begin!" << endl;
        game.run();
        cout << endl << "Enter 'c' to continue or 'q' to exit: ";
        cin >> whetherQuit;
        if ( whetherQuit == "q" ) break;
        else {
            cout << endl;
            continue;
        }
    }
    return 0;
}