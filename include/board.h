#pragma once

#include "Types.h"

struct piece_to_move
{
	char current_Move[10]; 

	enum pieces piece_to_move_on_board = NA;

	enum moveStatus typeOfMove;

	int index_to_move = 0;
};
struct board
{
	static constexpr int width = 8;
	static constexpr int height = 8;

	enum pieces board_array[width * height] = { BR, BK,BB,BQ,BKING,BB,BK,BR,
												BP, BP, BP, BP, BP, BP, BP, BP,
												NA,NA, NA, NA, NA, NA, NA, NA,
												NA,NA, NA, NA, NA, NA, NA, NA,
												NA,NA, NA, NA, NA, NA, NA, NA,
												NA,NA, NA, NA, NA, NA, NA, NA,
												WP, WP, WP, WP, WP, WP, WP, WP,
												WR, WK,WB,WQ,WKING,WB,WK,WR };


	int turn = 0;

	castlingOptions castle_array[4] = { false };

	char plays_since_pawn[3];

	char full_move_number[3];

	piece_to_move p;

	bool game_on = true;
	bool switch_sides = false;

	int move_list[256];
};
