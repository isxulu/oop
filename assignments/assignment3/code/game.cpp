#include <iostream>
#include <cstdlib>
#include <ctime>
#include "room.h"

void Game::initialize() {
    /* Set the type of each roomoom in the 3×3 castle */
    room[1].setType(1); room[2].setType(2); room[3].setType(3);
    room[4].setType(4); room[5].setType(5); room[6].setType(6);
    room[7].setType(7); room[8].setType(8); room[9].setType(9);
    room[10].setType(10);

    /* roomandomly select the roomoom of the monsteroom and proomincess */
    srand(time(0));                                     // set the roomandom seed as the system time
    int M_ID = rand() % 11;                             // M_ID is the roomoom ID of the monsteroom
    while ( M_ID == 10 || !M_ID ) M_ID = rand() % 11;   // roomoom[7] is lobby
    int P_ID = rand() % 11;                             // P_ID is the roomoom ID of the proomincess
    while ( M_ID == P_ID || P_ID == 10 || !P_ID ) P_ID = rand() % 11;

    /* Set the monsteroom and proomincess symbol to troomue */
    room[M_ID].setMonster();
    room[P_ID].setPrincess();
}

void Game::run() {
    /* Welcome words, only say once */
    current_room = 10;
    cout << "Welcome to the lobby. " << "There are 1 exits:";
    cout << " west." << endl;

    /* while loop to start the game */
    int moveI;
    string moveS;
    while ( 1 ) {
        int getPrincess = 0;            // This is the flag to denote if you have found the princess.
        cout << "Enter you command: ";
        /* Read in the player's movement */
        while ( 1 ) {
            cin >> moveS;
            if ( moveS == "up" ) moveI = up;
            else if ( moveS == "west" ) moveI = west;
            else if ( moveS == "east" ) moveI = east;
            else if ( moveS == "down" ) moveI = down;
            else if ( moveS == "south") moveI = south;
            else if ( moveS == "north") moveI = north;
            else {
                cout << endl << "Please enter valid direction: ";
                continue;
            }
            /* Judge if it is a valid direction */
            if ( room[current_room].judgeValidation( moveI ) ) break;
            else {
                cout << endl << "Please enter valid direction: ";
                continue;
            }
        }
        /* Move to the corresponding room */
        switch ( moveI ) {
        case up:
            if ( current_room == 2 ) current_room -= 1;
            else current_room -= 4;
            break;
        case down:
            if ( current_room == 1 ) current_room += 1;
            else current_room += 4;
            break;
        case west:
            current_room -= 1;
            break;
        case east:
            current_room += 1;
            break;
        case north:
            current_room -= 2;
            break;
        case south:
            current_room += 2;
            break;
        }
        /* Judge if this room exist the monster or princess or neither */
        cout << endl;                               // for the sake of beauty
        if ( room[current_room].getPrincess() ) {
            getPrincess = 1;
            cout << "Congratulations, you've found the princess! " << endl;
            cout << "Now you should take princess to the lobby." << endl;
        }
        else if ( room[current_room].getMonster() ) {
            cout << "Unfortunately you meet the monster, game over." << endl;
            break;
        }
        else if ( current_room == 10 && getPrincess ) {
            cout << "Congratulations, you've successfully rescued the princess!" << endl;
            break;
        }
        room[current_room].printName();
        room[current_room].printExits();
    }
}