
#include "../common_includes.h"
#include <set>
#include <algorithm>
#define Move int

enum Piece {
  EMPTY,
  WHITE_KING,
  WHITE_QUEEN,
  WHITE_BISHOP,
  WHITE_KNIGHT,
  WHITE_ROOK,
  WHITE_PAWN,
  BLACK_KING,
  BLACK_QUEEN,
  BLACK_BISHOP,
  BLACK_KNIGHT,
  BLACK_ROOK,
  BLACK_PAWN
}; 
vector<Piece> get_initial_board();
set<Move> get_possible_moves(vector<Piece>board , int square);
