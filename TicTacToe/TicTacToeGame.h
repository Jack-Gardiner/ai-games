#pragma once
#include "../common_includes.h"
#include "TicTacToeState.h"
class TTTGame : public Game{
    public:
        TTTGame(){currentState = new TicTacToeState(2,3);};
        void start_game(){};
};