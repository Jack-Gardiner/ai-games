
#pragma once
#include "../Player.h"
#include "../common_includes.h"
#include "../State.h"
#include <tuple>
#include <cmath>
template <typename T>
class MinimaxPlayer : public Player{
    public: 
        MinimaxPlayer(int player_num, int minimax_depth) : Player(player_num){
            searchDepth = minimax_depth;
            cout << "init MiniMax #" << player_num << "\n";
        };
        virtual void game_start(int player_count, int* turn_order, void *data){

            player_turn_order = turn_order;
            currentState = create_initial_state(player_count, turn_order, data);
            cout << "Hello, i'm running MINIMAX!" << "\n";
        }
        virtual void inform_move(int from_player,string move){
            currentState->apply_move(move);
        }
        virtual string introduce(){
            return "I'm a minimax bot!";
        }

        virtual string get_move(){
            auto [best_move, eval_vec] = get_best_move(currentState, searchDepth,0);
            cout << best_move << "\n";
            for(int i = 0; i < eval_vec.size(); i++){
                cout << eval_vec[i] << " ";

            }
            cout << "\n";
            return best_move;
        }
    protected:
        
        int* player_turn_order;
        int searchDepth;
        T *currentState;
        virtual T *create_initial_state(int player_count, int* turn_order, void *data) = 0;
        // returns a heuristic value of the current state from a certain turn perspective, without considering other players.
        virtual float heuristic(T* state, int turnPerspective) = 0;
        virtual vector<string> generate_moves(T* state) = 0;
        // returns the best move from the current state, and the resulting evaluation tuple, up to a certain depth.
        std::tuple<string, vector<float>> get_best_move(T *state, int depth, int ddown){
            // current state has whos turn it is.
            int currTurn = state->currentTurn;
            int playerCount = state->playerCount;
            if(depth == 0){
                vector<float> ret_eval_vec;
                for(int i = 0; i < playerCount; i++){
                    ret_eval_vec.push_back(heuristic(state, i));
                }
                return {"NO MOVE", ret_eval_vec};
            }
            vector<string> possible_moves = generate_moves(state);
            string best_move = "NO MOVE!";
            float best_eval = -std::numeric_limits<double>::infinity();
            vector<float> best_eval_vec;
            for(int i = 0; i < possible_moves.size(); i++){
                string m = possible_moves[i];
                
                T *nextState = state->clone();
                nextState->apply_move(m); 
                
                auto [move_after, eval_vec] = get_best_move(nextState, depth-1,ddown + 1);
                
                float eval = combine_evals(eval_vec, currTurn);
                if(ddown == 0){
                    //cout << "Move: " << m << "\n";
                    //cout << "Next Board:\n" << nextState->display();
                    //cout << move_after << "\n";
                    for(int i = 0; i < eval_vec.size(); i++){
                        //cout << eval_vec[i] << " ";

                    }
                    //cout << "\n";
                    //cout << eval << "\n";
                }
                if(eval > best_eval){
                    best_eval = eval;
                    best_move = m;
                    best_eval_vec = eval_vec;
                }
                
            }
            if (possible_moves.size() == 0){
                vector<float> ret_eval_vec;
                for(int i = 0; i < playerCount; i++){
                    ret_eval_vec.push_back(heuristic(state, i));
                }
                return {"NO MOVE", ret_eval_vec};
            }
            return {best_move, best_eval_vec};
        }
        virtual float combine_evals(vector<float> eval_vec, int turnPerspective){
            // by default, use root mean squares, aka l2 norm normalized by sqrt player count.
            float our_eval = -1;
            float enemy_eval = 0;
            for(int i = 0; i < eval_vec.size();i++){
                if (i == turnPerspective){
                    our_eval = eval_vec[i];
                }else{
                    enemy_eval += eval_vec[i] * eval_vec[i];
                }
            }
            enemy_eval = sqrt(enemy_eval);
            if(eval_vec.size() < 2){
                return our_eval;
            }
            return our_eval - enemy_eval/sqrt(eval_vec.size() - 1);
        }
        
};