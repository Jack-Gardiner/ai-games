#pragma once
#include <stdlib.h>
using namespace std; 
class Player{
    public: 
        int playerNum = -1;
        virtual void game_start(int player_count, int* turn_order) = 0;
        virtual string get_move() = 0;
        virtual void inform_move(int from_player, string move) = 0;
};