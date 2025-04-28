#pragma once
#include "../common_includes.h"
#include "TicTacToeState.h"

class TTTGame : public Game{
    public:
        int board_size;
        TTTGame();
        void start_game();
};