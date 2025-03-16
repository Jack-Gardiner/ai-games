#include "State.h"
State::State(int playercount){
    playerCount = playercount;
    currentTurn = 0;
}
int State::game_result(){
    for(int i = 0; i < playerCount; i++){
        if(has_won(i)){
            return i;
        }
    }
    return -2;
}