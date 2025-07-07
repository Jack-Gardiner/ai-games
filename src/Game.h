#pragma once
#include "State.h"
#include "Player.h"
#include <vector>
enum Level {
  LOW,
  MEDIUM,
  HIGH
}; 
class Game{
    public: 
        std::vector<Player*> players;
        State *currentState;
        bool playing = true;
        int result; // if -1, no winner yet. -2 means a draw.
        virtual void add_player(Player* p){
            players.push_back(p);
        };
        void initialize_players();
        virtual void start_game() = 0;
        virtual bool tick(); // returns true if game is continued.
        
};