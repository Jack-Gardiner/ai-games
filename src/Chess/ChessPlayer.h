#include "../Player.h"
#include "ChessIncludes.h"
class ChessPlayer : Player{
    
    public: 
        ChessPlayer(int player_num);
        virtual void game_start(int player_count, int* turn_order, void* args);
        virtual string get_move();
        virtual void inform_move(int from_player, string move);
    private:
        vector<Piece> board;
    
}