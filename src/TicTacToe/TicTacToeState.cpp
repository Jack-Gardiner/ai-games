#include "TicTacToeState.h"
TicTacToeState::TicTacToeState(int playercount, int board_size): State(playercount){
    board = vector<vector<int>>(board_size, vector<int>(board_size,-1));
    boardSize = board_size;
    currentTurn = 0;
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
    // check vertical
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
        for(int j = 0; j < board[i].size();j++){
            if(board[i][j] == -1){
                return -2;
            }
        }
    }
    cerr << "test" << "\n";
    return -1;
};
bool TicTacToeState::apply_move(string move){
    if (!is_valid_move(move)){
        return false;
    }
    int move_square = stoi(move);

    board[move_square%boardSize][move_square/boardSize] = currentTurn;

    currentTurn = (currentTurn + 1)%playerCount;
    return true;
};
void* TicTacToeState::get_board(){
    return &board;
};
bool TicTacToeState::is_valid_move(string move){
    char* p;
    // check if the move is an integer.
    long move_square = strtol(move.c_str(), &p, 10);
    if (*p) {
        return false;
    }
    // check if square is in board.
    if(move_square > boardSize * boardSize || move_square < 0){
        return false;
    }
    // check if square is empty.
    return (board[move_square%boardSize][move_square/boardSize] == -1);
};
string TicTacToeState::display(){
    string ret = "";
    ret.append("-------");
    ret.append("\n");
    for(int i = 0; i < boardSize; i++){
        ret.append("|");
        for(int j = 0; j < boardSize; j++){
            
            switch (board[i][j])
            {
            case 1:
                ret.append("O");
                break;
            case 0:
                ret.append("X");
                break;
            case -1:
                ret.append(" ");
                break;
            default:
                break;
            }
            ret.append("|");
        }
        ret.append("\n");
        ret.append("-------");
        ret.append("\n");
    }
    return ret;
}
TicTacToeState * TicTacToeState::clone(){
    TicTacToeState *new_state = new TicTacToeState(playerCount,boardSize);
    new_state->currentTurn = currentTurn;
    for(int i = 0; i < board.size(); i++){
        for(int j = 0; j < board[0].size();j++){
            new_state->board[i][j] = board[i][j];
            
        }
    }  
    return new_state;
}