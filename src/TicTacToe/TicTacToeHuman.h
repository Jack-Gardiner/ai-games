#pragma once
#include "TicTacToePlayer.h"
#include "../common_includes.h"
class TTTHuman : public TTTPlayer{
    public: 
        TTTHuman(int num);
        string get_move();
        string introduce();
};