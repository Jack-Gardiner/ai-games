#include "TicTacToeState.h"
TicTacToeState::TicTacToeState(int playercount, int board_size): State(playerCount){
    board = vector<vector<int>>(board_size, vector<int>(board_size,-1));
}
bool TicTacToeState::has_won(int playerNum){
    // CHECK HORIZONTAL
    for(int i = 0; i < board.size();i++){
        bool all_full = true;
        for(int j = 0; j < board[i].size();j++){
            if(board[i][j] != playerNum){
                all_full = false;
                break;
            }
        }
        if(all_full){
            return true;
        }
    }
    // check verticle
    for(int j = 0; j < board[0].size();j++){
        bool all_full = true;
        for(int i = 0; i < board.size();i++){
            if(board[i][j] != playerNum){
                all_full = false;
                break;
            }
        }
        if(all_full){
            return true;
        }
    }
    // check diagonals
    int size = board.size();
    bool all_full = true;
    for(int i = 0; i < size;i++){
        if(board[i][i] != playerNum){
            all_full = false;
            break;
        }
    }
    if(all_full){
        return true;
    }

    all_full = true;
    for(int i = 0; i < size ;i++){
        if(board[i][size-i-1] != playerNum){
            all_full = false;
            break;
        }
    }
    if(all_full){
        return true;
    }
    
    return false;
}
int TicTacToeState::game_result(){
    for(int i = 0; i < playerCount; i++){
        if(has_won(i)){
            return i;
        }
    }
    // check for draw:
    for(int i = 0; i < board.size();i++){
        for(int j = 0; j < board[i].size();i++){
            if(board[i][j] == -1){
                return -2;
            }
        }
    }
    return -1;
};
bool TicTacToeState::apply_move(string move){
};
void* TicTacToeState::get_board(){
    return &board;
};
bool TicTacToeState::is_valid_move(string move){
};