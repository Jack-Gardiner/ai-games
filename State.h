#pragma once
#include <stdlib.h>
#include <vector>
#include <string>
class State{
    public:
        int playerCount = -1;
        int currentTurn = 0;
        State(int playercount);
        virtual bool has_won(int playerNum) = 0;
        // Returns the number of the player that has won, returns -1 for a draw, and -2 for an ongoing game.
        virtual int game_result();
        virtual bool apply_move(std::string move) = 0;
        virtual void* get_board() = 0;
    protected:
    //virtual vector<string> get_possible_moves() = 0;
    virtual bool is_valid_move(std::string move) = 0;
};