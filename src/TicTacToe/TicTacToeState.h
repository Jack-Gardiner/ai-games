#pragma once
#include "../common_includes.h"
class TicTacToeState : public State{
    
    public:
        TicTacToeState(int playercount, int board_size);
        vector<vector<int>> board;
        int boardSize = 0;
        virtual bool has_won(int playerNum);
        // Returns the number of the player that has won, returns -1 for a draw, and -2 for an ongoing game.
        virtual int game_result();
        bool apply_move(string move);
        void* get_board();
        string display();
        TicTacToeState *clone();
    protected:
    //virtual vector<string> get_possible_moves() = 0;
        virtual bool is_valid_move(string move);
};