#pragma once
#include "globals.h"

struct piece_to_move
{
public: 	
	enum class moveStatus { DUMMY = 0, RATTACK, AATTACK, CASTLEKING, CASTLEQUEEN, CHECK, MATE, RMOVE, AMOVE, RPAWNMOVE, APAWNMOVE, PROMO, EP };

public:
	piece_to_move();
	//In the future make this dynamic or a vector. I have to have it as a char cause I use a lot of c style functions.
	char current_Move[10];
	pieces piece_to_move_on_board;
	piece_to_move::moveStatus typeOfMove;
	int index_to_move;
	//void reset();
};
