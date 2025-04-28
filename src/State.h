#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
class State{
    public:
        int playerCount = -1;
        State(int playercount);
        int currentTurn = 0;
        virtual bool has_won(int playerNum) = 0;
        // Returns the number of the player that has won, returns -1 for a draw, and -2 for an ongoing game.
        virtual int game_result();
        virtual bool apply_move(std::string move) = 0;
        virtual void* get_board() = 0;
        virtual std::string display();
        void print();
    protected:
    //virtual vector<string> get_possible_moves() = 0;
        virtual bool is_valid_move(std::string move) = 0;
};