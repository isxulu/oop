#ifndef ROOM_H_
#define ROOM_H_
#include <vector>
#include <string>
using namespace std;

enum Direction{north, south, east, west, up, down};

class Room {
private:
    bool monster;
    bool princess;
    int room_type;
    string room_name;
    vector<int> exits;
    vector<string> directions;
public:
    Room(): monster(false), princess(false) {}
    void setType( int t );
    void setMonster();
    void setPrincess();
    bool getMonster();
    bool getPrincess();
    void printExits();
    void printName();
    bool judgeValidation( int x );
};

class Game {
private:
    Room room[11];
    int current_room;
public:
    Game() {}
    void initialize();
    void run();
};

#endif