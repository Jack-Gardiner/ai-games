#include "common_includes.h"
#include "TicTacToe/TicTacToeBot.h"
#include "TicTacToe/TicTacToeGame.h"
int main(){
    std::cout << "HI";
    
    Player* B1 = new TTTBot(0);
    Player* B2 = new TTTBot(1);
    auto current_game = new TTTGame();
    current_game->add_player(B1);
    current_game->add_player(B2);
    // add players B1 and B2

    printf("%d\n", B1->playerNum);
    printf("%d\n", B2->playerNum);
    printf("%s\n", typeid(current_game -> currentState).name());
    printf("%d\n", __cplusplus);
    printf("hiii");
}