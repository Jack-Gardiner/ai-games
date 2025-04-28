#pragma once
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std; 
class Player{
    public: 
        Player(int player_num){
            playerNum = player_num;
        }
        int getPlayerNum(){
            return playerNum;
        }
        virtual void game_start(int player_count, int* turn_order, void* args) = 0;
        virtual string get_move() = 0;
        virtual void inform_move(int from_player, string move) = 0;
    private:
        int playerNum = -1;
};