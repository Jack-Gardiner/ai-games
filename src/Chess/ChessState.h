#pragma once
#include "ChessIncludes.h"

class ChessState : public State{
    public:
        ChessState();
        vector<vector<Piece>> board;
        virtual bool has_won(int playerNum);
        int game_result();
        bool apply_move(std::string move);
        void* get_board();
        std::string display();
        void print();
        ChessState* clone();
    protected:
        virtual bool is_valid_move(std::string move) = 0;
};