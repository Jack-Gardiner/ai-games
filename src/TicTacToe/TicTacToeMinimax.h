#pragma once
#include "../Player.h"
#include "../common_includes.h"
#include "../BotTemplates/MinimaxPlayer.h"
#include "TicTacToeState.h"
class TTTMinimaxPlayer : public MinimaxPlayer<TicTacToeState>{
    public: 
        TTTMinimaxPlayer(int player_num, int minimax_depth) : MinimaxPlayer(player_num,minimax_depth){
        };
    protected:
        TicTacToeState* create_initial_state(int player_count, int* turn_order, void *data);
        // returns a heuristic value of the current state from a certain turn perspective, without considering other players.
        virtual float heuristic(TicTacToeState *state, int turnPerspective);
        virtual vector<string> generate_moves(TicTacToeState *state);
};
