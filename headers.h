#pragma once

//p.h includes globals which has all of the necessary includes.
#include "p.h"


struct board
{
public:
	board() : turn{ 0 }, p(), plays_since_pawn(3), full_move_number(3)
	{}
private:
	static constexpr int width = 8;
	static constexpr int height = 8;
	typedef bool castlingOptions;
public:
	enum class asciiPieces { PAWN = 0, ROOK = 82, KNIGHT = 78, BISHOP = 66, QUEEN = 81, KING = 75 };
	enum class castleRights { BQC=0, BKC, WQC, WKC };
public:
	
	std::array<enum pieces, width* height>board_array = { pieces::BR,pieces::BK,pieces::BB,pieces::BQ,pieces::BKING,pieces::BB,pieces::BK,pieces::BR,
												pieces::BP, pieces::BP, pieces::BP, pieces::BP, pieces::BP, pieces::BP, pieces::BP, pieces::BP,
												pieces::NA,pieces::NA, pieces::NA, pieces::NA,pieces::NA,pieces::NA,pieces::NA, pieces::NA,
												pieces::NA,pieces::NA, pieces::NA, pieces::NA, pieces::NA, pieces::NA, pieces::NA, pieces::NA,
												pieces::NA,pieces::NA, pieces::NA, pieces::NA, pieces::NA, pieces::NA, pieces::NA, pieces::NA,
												pieces::NA,pieces::NA, pieces::NA, pieces::NA, pieces::NA, pieces::NA, pieces::NA, pieces::NA,
												pieces::WP, pieces::WP, pieces::WP,pieces::WP,pieces::WP, pieces::WP, pieces::WP, pieces::WP,
												pieces::WR, pieces::WK,pieces::WB,pieces::WQ,pieces::WKING,pieces::WB,pieces::WK,pieces::WR };

private:
	
	piece_to_move p;
public:
	int turn;
	castlingOptions castle_array[4] { false };
	std::vector<char>plays_since_pawn; //I assume the max number of digits in each of these vecs is going to be 3.
	std::vector<char>full_move_number;
	bool game_on = true;
	bool switch_sides = false;
public:
	//All of these will be changing p I assume - so no member function const.
	pieces return_corresponding_enum_to_piece(const char a) const ;
	piece_to_move::moveStatus determineMove(); 
	void setCurrentMove(const char* input);
	void parseMove();
	bool check_if_impeded_by_ally_piece(int current_index) const;
	bool check_if_we_can_move_to_destination(const int current_index) ;
	void Move();
	void drawBoard();
	void readFEN(const char* fenstring);
};
