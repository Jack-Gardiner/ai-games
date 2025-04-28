#pragma once
#include "../Player.h"
#include "../common_includes.h"
class TTTPlayer : public Player{
    public: 
        TTTPlayer(int player_num);
        virtual void game_start(int player_count, int* turn_order, void *board_size);
        virtual void inform_move(int from_player,string move);
        virtual string introduce();
    protected:
    int board_size;
    int* board;
};