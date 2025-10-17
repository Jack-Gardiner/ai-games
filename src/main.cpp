#include "common_includes.h"
#include "TicTacToe/TicTacToeBot.h"
#include "TicTacToe/TicTacToeGame.h"
#include "TicTacToe/TicTacToeHuman.h"
#include "TicTacToe/TicTacToeMinimax.h"

/// TODO:
/// maybe make some diagrams. (fuck nooo)
/// pull abstract stuff from TTT game.
// put try/catch around bots in referee.
// seperate headers and .cpp

// CHESS:
// write move sets for pieces
// combine into a "get moves" function, taking into account current board
// three types of moves, sliding, jumping and pawns.
// determine check/promotion/enpassant

int main(){
    std::cout << "HI\n";
    std::cout << __cplusplus << "\n";
    Player* B1 = new TTTHuman(0);
    std::cout << "__\n";
    Player* B2 = new TTTMinimaxPlayer(1,9);
    std::cout << "__\n";
    auto current_game = new TTTGame();
    current_game->add_player(B1);
    current_game->add_player(B2);
    // add players B1 and B2
    current_game->start_game();
    
    while(current_game->result == -2){
        cerr << "t\n";
        current_game->tick();
    }
    
}