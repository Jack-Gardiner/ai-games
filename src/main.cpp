#include "common_includes.h"
/*
#include "TicTacToe/TicTacToeBot.h"
#include "TicTacToe/TicTacToeGame.h"
#include "TicTacToe/TicTacToeHuman.h"
#include "TicTacToe/TicTacToeMinimax.h"
*/
#include "Splendor/SplendorGame.h"
#include "Splendor/SplendorPlayer.h"
#include "Splendor/SplendorState.h"
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
    /*
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
    */
    SplendorState *testState = new SplendorState(4);
    cout << testState->display() << endl;
    cout << testState->game_result() << endl;
    // b <shop card coords> <list of gems to use gold instead of> <noble choice>? (buy shop card at coord)
    // r <shop card coords> <list of gems to discard> <noble choice>? (reserve shop card at coord) 
    // br <reserve card coords> <list of gems to use gold instead of> <noble choice>?
    // t <list of gems to take from stockpile> <list of gems to discard> <noble choice>?
    
    string next_move = "t 1,1,1,0,0,0 0,0,0,0,0,0";
    cout << "Applying move!" << endl;
    testState->apply_move(next_move);
    cout << testState->display() << endl;
    cout << testState->game_result() << endl;
    //Currently working on testing apply_move. after this, get_board needs to be written, maybe after player classes.
    
    /*
    SplendorState * cl = testState->clone();
    cout << cl->display() << endl;
    cout << cl->game_result() << endl;
    */
}    