#include <TicTacToeBot.h>
TTTBot::TTTBot(int num): TTTPlayer(num){
    cout << "init";
};
string TTTBot::introduce(){
    return "Hello, i'm a TTT bot! My player number is ";
}

string TTTBot::get_move(){
    vector<int> available_squares;
    for(int i = 0; i < board_size*board_size; i++){
        if(board[i] == -1){
            available_squares.push_back(i);
        }
    }  
    if(available_squares.size() > 0){
        return to_string(available_squares[0]);
    } else{
        return "0";
    }
    // do MiniMax
    
};