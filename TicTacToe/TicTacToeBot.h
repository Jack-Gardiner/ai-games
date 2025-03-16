#pragma once
#include "../Player.h"
class TTTBot : public Player{
    public: 
        TTTBot(int num){
            playerNum = num;
        };
        void game_start(int player_count, int* turn_order){
            
        };
        
        string get_move(){
            return string("NO MOVE");
        };
        void inform_move(int from_player,string move){

        };
};