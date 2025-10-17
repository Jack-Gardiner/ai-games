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
};