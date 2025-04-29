#include "common_includes.h"
#include "TicTacToe/TicTacToeBot.h"
#include "TicTacToe/TicTacToeGame.h"
#include "TicTacToe/TicTacToeHuman.h"


/// TODO:=
/// A* move logic for TTT.
/// human player for TTT.
/// maybe make some diagrams.
/// pull abstract stuff from TTT game.
// put try/catch around bots in referee.
int main(){
    std::cout << "HI\n";
    std::cout << __cplusplus << "\n";
    Player* B1 = new TTTHuman(0);
    Player* B2 = new TTTBot(1);
    auto current_game = new TTTGame();
    current_game->add_player(B1);
    current_game->add_player(B2);
    // add players B1 and B2
    current_game->start_game();
    
    while(current_game->result == -2){
        current_game->tick();
    }
    
}