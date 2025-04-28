#include "TicTacToeGame.h"
#include "TicTacToePlayer.h"
TTTGame::TTTGame(){
    board_size = 3;
    currentState = new TicTacToeState(2,board_size);
    
}
void TTTGame::start_game(){
    
    int* turnOrder = new int[players.size()];
    
    for(int i = 0; i < players.size(); i++){
        turnOrder[i] = players[i]->getPlayerNum();
    }
    for(int i = 0; i < players.size(); i++){
        std::cout << "=!!" << "\n";
        players[i]->game_start(players.size(), turnOrder, &board_size);
    }
    std::cout << "LETS START SOME TIC TAC TOE!!" << "\n";
    result = -2;

}
