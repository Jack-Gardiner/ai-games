#include "State.h"

State::State(int playercount){
    playerCount = playercount;
}
int State::game_result(){
    std::cout << "Using default game result calculator" << "\n";
    for(int i = 0; i < playerCount; i++){
        if(has_won(i)){
            return i;
        }
    }
    return -2;
}
std::string State::display(){
    return "Undefined State display";
}
void State::print(){
    std::cout << display() << "\n";
}