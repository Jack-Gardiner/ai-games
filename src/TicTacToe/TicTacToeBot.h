#pragma once
#include "TicTacToePlayer.h"
#include "../common_includes.h"
class TTTBot : public TTTPlayer{
    public: 
        TTTBot(int num);
        string get_move();
        string introduce();
};