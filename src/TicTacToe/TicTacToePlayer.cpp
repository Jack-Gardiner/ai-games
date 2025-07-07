#include <TicTacToePlayer.h>
TTTPlayer::TTTPlayer(int player_num): Player(player_num){
};
string TTTPlayer::introduce(){
    return "Hello, I'm some sort of TTT player! Player Number: ";
}
void TTTPlayer::game_start(int player_count, int* turn_order, void* board_s){
    cout << introduce() << getPlayerNum() << "\n";
    board_size = *(int*)board_s;
    board = new int[board_size * board_size];
    
    for(int i = 0; i < board_size*board_size; i++){
        board[i] = -1;
    }
};
void TTTPlayer::inform_move(int from_player,string move){
    board[atoi(move.c_str())] = from_player;
};