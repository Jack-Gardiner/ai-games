#pragma once
#include "constants.h"
class SplendorState : public State{
    public:
        SplendorState(int playerCount);
        vector<vector<devCard>> shopCards;
        vector<noble> unclaimedNobles;
        vector<vector<devCard>> playerAssets;
        vector<vector<devCard>> playerReserves;
        vector<vector<noble>> playerNobles;
        vector<vector<int>> playerBalance;
        vector<vector<int>> playerDiscounts;
        vector<int> shopGems;
        vector<int> playerPoints;
        vector<vector<devCard>> deckCards;
        virtual bool has_won(int playerNum);
        int game_result();
        bool apply_move(std::string move);
        void* get_board();
        std::string display();
        void print();
        SplendorState* clone();
    protected:
        virtual bool is_valid_move(std::string move) = 0;
};
