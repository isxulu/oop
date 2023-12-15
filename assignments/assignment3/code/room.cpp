#include <iostream>
#include"room.h"

void Room::setType( int t ) {
    room_type = t;
    switch ( t ) {
    case 1:                     // the top level room
        room_name = "tower";
        exits.push_back(down);  directions.push_back("down");
        break;
    case 2:                     // the stairs between two level
        room_name = "stairs";
        exits.push_back(up);    directions.push_back("up");
        exits.push_back(down);  directions.push_back("down");
        exits.push_back(east);  directions.push_back("east");
        exits.push_back(south); directions.push_back("south");
        break;
    case 3:                     // the first garden
        room_name = "garden";
        exits.push_back(west);  directions.push_back("west");
        exits.push_back(south); directions.push_back("south");
        break;
    case 4:                     // the second garden
        room_name = "garden";
        exits.push_back(down);  directions.push_back("down");
        exits.push_back(east);  directions.push_back("east");
        exits.push_back(north); directions.push_back("north");
        break;
    case 5:                     // the boardroom
        room_name = "boardroom";
        exits.push_back(west);  directions.push_back("west");
        exits.push_back(north); directions.push_back("north");
        break;
    case 6:                     // the second stairs between two level
        room_name = "stairs";
        exits.push_back(up);    directions.push_back("up");
        exits.push_back(east);  directions.push_back("east");
        exits.push_back(south); directions.push_back("south");
        break;
    case 7:                     // the kitchen
        room_name = "kitchen";
        exits.push_back(west);  directions.push_back("west");
        break;
    case 8:                     // the play room
        room_name = "playroom";
        exits.push_back(up);    directions.push_back("up");
        exits.push_back(east);  directions.push_back("east");
        exits.push_back(north); directions.push_back("north");
        break;
    case 9:                     // the corridor
        room_name = "corridor";
        exits.push_back(west);  directions.push_back("west");
        exits.push_back(east);  directions.push_back("east");
        break;
    case 10:                    // the lobby
        room_name = "lobby";
        exits.push_back(west);  directions.push_back("west");
        break;
    }
}

void Room::setMonster() {
    monster = true;
}

void Room::setPrincess() {
    princess = true;
}

bool Room::getMonster() {
    return monster;
}

bool Room::getPrincess() {
    return princess;
}

void Room::printName() {
    cout << "This is " << room_name << ". ";
}

void Room::printExits() {
    int num = directions.size();
    cout << "There are " << num << " exits: ";
    for ( int i = 0; i < num; i++ ) {
        if ( i == 0 ) cout << directions[i];
        else if ( i != num-1 ) cout << ", " << directions[i];
        else cout << " and " << directions[i];
    }
    cout << "." << endl;
}

bool Room::judgeValidation( int x ) {
    bool ret = false;
    for ( int i = 0; i < exits.size(); i++ ) {
        if ( x != exits[i] ) continue;
        else {
            ret = true;
            break;
        }
    }
    return ret;
}