#include "Game.h"
bool Game::tick(){
    Player* currentPlayer = players[currentState->currentTurn];
    string chosenMove = currentPlayer->get_move();
    std::cout<< "Player " << currentState->currentTurn << " plays move " << chosenMove << "\n";
    bool was_valid_move = currentState->apply_move(chosenMove);
    if (!was_valid_move){
        std::cout << "INVALID MOVE!! " << chosenMove << "\n";
        std::cout << "Player " << currentPlayer->getPlayerNum() << " Loses!\n"; 
        result = (1-currentPlayer->getPlayerNum());
        return false;
    }
    for(int i = 0; i < players.size(); i++){
        players[i]->inform_move(currentPlayer->getPlayerNum(), chosenMove);
    }
    cout << "Current board:" << "\n";
    currentState->print();
    // check for result.
    result = currentState->game_result();
    if(result == -2){
        return true;
    }else{
        cout << "Game Over!\n";
        switch(result){
            case -1:
                cout << "Its a draw!" << "\n";
            break;
            default:
                cout << "Player " << result<< " wins!" << "\n";
            
        }
        return false;
    }
}