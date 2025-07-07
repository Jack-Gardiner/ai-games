#include <TicTacToeMinimax.h>
TicTacToeState* TTTMinimaxPlayer::create_initial_state(int player_count, int* turn_order, void *data){
    TicTacToeState* new_state = new TicTacToeState(player_count,*((int*)data));
    return new_state;
};
// returns a heuristic value of the current state from a certain turn perspective, without considering other players.
float TTTMinimaxPlayer::heuristic(TicTacToeState *state, int turnPerspective){
    int playerPerspective = player_turn_order[turnPerspective];
    return state->has_won(playerPerspective);
};
vector<string> TTTMinimaxPlayer::generate_moves(TicTacToeState *state){
    vector<string> available_moves;
    vector<vector<int>> board = *((vector<vector<int>> *) state->get_board()); // convert from void* to 2d vector, and dereference.
    for(int i = 0; i < state->playerCount; i++){
        if(state->has_won(i)){
            return available_moves;
        }
    }
    for(int i = 0; i < board.size(); i++){
        for(int j = 0; j < board[0].size();j++){

            if(board[i][j] == -1){
                available_moves.push_back(to_string( board.size() * j + i));
            }
        }
    }  
    return available_moves;
};