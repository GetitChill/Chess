#pragma once
#include "board.h"

enum pieces return_corresponding_enum_to_piece(char a, board* b);

enum moveStatus determineMove(board* b);

void setCurrentMove(board* b, const char* input);

void parseMove(piece_to_move* p, board* b);
