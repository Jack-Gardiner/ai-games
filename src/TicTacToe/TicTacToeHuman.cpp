#include <TicTacToeHuman.h>
TTTHuman::TTTHuman(int num): TTTPlayer(num){
};
string TTTHuman::introduce(){
    return "Hello, I'm playing from the console! My player number is ";
}

string TTTHuman::get_move(){
    string ret;
    cout << "What move do you want to play?\n";
    getline(cin, ret);
    return ret;
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
};