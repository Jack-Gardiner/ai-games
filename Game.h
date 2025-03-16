#pragma once
#include "State.h"
#include <vector>
class Game{
    public: 
        std::vector<Player*> players;
        State *currentState;
        virtual void add_player(Player* p){
            players.push_back(p);
        };
        virtual void start_game() = 0;
        
};